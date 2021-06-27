import random
import subprocess
import sys
import argparse
from logger import logger
from client import Client
from objects import Objects
import uuid
import tiles
import config

objects_map = {
    Objects.FOOD: "food",
    Objects.LINEMATE: "linemate",
    Objects.DERAUMERE: "deraumere",
    Objects.SIBUR: "sibur",
    Objects.MENDIANE: "mendiane",
    Objects.PHIRAS: "phiras",
    Objects.THYSTAME: "thystame"
}

incantation_requirements = {
    2: {
        "player": 1,
        "linemate": 1,
        "deraumere": 0,
        "sibur": 0,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    3: {
        "player": 2,
        "linemate": 1,
        "deraumere": 1,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    4: {
        "player": 2,
        "linemate": 2,
        "deraumere": 0,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 2,
        "thystame": 0
    },
    5: {
        "player": 4,
        "linemate": 1,
        "deraumere": 1,
        "sibur": 2,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    6: {
        "player": 4,
        "linemate": 1,
        "deraumere": 2,
        "sibur": 1,
        "mendiane": 3,
        "phiras": 0,
        "thystame": 0
    },
    7: {
        "player": 6,
        "linemate": 1,
        "deraumere": 2,
        "sibur": 3,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    8: {
        "player": 6,
        "linemate": 2,
        "deraumere": 2,
        "sibur": 2,
        "mendiane": 2,
        "phiras": 2,
        "thystame": 1
    }
}

tmp_object_mapping = {
    "food": Objects.FOOD,
    "linemate": Objects.LINEMATE,
    "deraumere": Objects.DERAUMERE,
    "sibur": Objects.SIBUR,
    "mendiane": Objects.MENDIANE,
    "phiras": Objects.PHIRAS,
    "thystame": Objects.THYSTAME
}


class TileNotFoundException(Exception):
    pass


def has_requirements(inventory: dict, lvl: int) -> bool:
    req = incantation_requirements[lvl]
    for key in inventory:
        if key == "food":
            continue
        if inventory[key] < req[key]:
            return False
    return True


def generate_missing_res(inv: dict, req: dict) -> list:
    to_return = []
    for key, value in req.items():
        if key == "player":
            continue
        if value > inv[key]:
            to_return.append(key)
    return to_return


class AI:
    def __init__(self, ip: str, port: int, team: str):
        self.ip = ip
        self.port = port
        self.cli = Client()
        self.team = team
        self.lvl = 1
        self.looking_for_food = True
        self.food_search_threshold = config.FOOD_SEARCH_THRESHOLD[0]
        self.stone_search_threshold = config.FOOD_SEARCH_THRESHOLD[1]
        self.do_fork = True
        self.uuid = str(uuid.uuid4().hex)
        self.messages = []
        self.is_incanting = False
        self.others = {
            1: {},
            2: {},
            3: {},
            4: {},
            5: {},
            6: {},
            7: {}
        }
        self.fork_timing = 0

    # TODO: Refactor
    def set_tiles_coord(self, tile: list):
        i = 0
        for y in range(self.lvl + 1):
            for x in range(-y, y + 1):
                try:
                    tile[i].coord = (x, y)
                except IndexError as e:
                    logger.error(f"{tile}, {x}, {y}, {i}")
                    raise e
                i += 1
        return tile

    def move_to(self, tile: tiles.Tile, to_take: list) -> None:
        try:
            x, y = tile.coord
            for _ in range(y):
                self.forward()
            if x < 0:
                self.left()
            elif x > 0:
                self.right()
            for _ in range(abs(x)):
                self.forward()
            self.get_resources(tile, to_take)
        except TypeError as e:
            logger.error(tile)
            raise e

    def get_resources(self, tile: tiles.Tile, to_take: list):
        for i in to_take:
            if getattr(tile, i):
                self.take(tmp_object_mapping[i])

    def search(self, looked: list, to_search: list) -> None:
        # TODO: Get the closest tiles first
        # TODO: Don't go in a player occupied tile
        def get_tile(looked_inner: list, to_search_inner: list) -> tiles.Tile:
            for i in looked_inner:
                for y in to_search_inner:
                    if getattr(i, y):
                        return i
            raise TileNotFoundException
        try:
            self.move_to(get_tile(self.set_tiles_coord(looked), to_search), to_search)
        except TileNotFoundException:
            hazard = random.randint(0, 2)
            if hazard == 0:
                self.left()
            elif hazard == 1:
                self.right()
            else:
                self.forward()

    def take_everything_from_ground(self, looked: list):
        for key, value in tmp_object_mapping.items():
            for _ in range(getattr(looked[0], key)):
                self.take(value)

    def put_requirements_to_the_ground(self, req: dict) -> None:
        for key, value in req.items():
            if key == "player":
                continue
            for _ in range(value):
                # TODO: Remove this mapping and make it use python correctly
                self.put(tmp_object_mapping[key])

    def host_incantation(self, looked: list) -> None:
        requirements = incantation_requirements[self.lvl + 1]
        missing_players = requirements["player"] - looked[0].player
        if self.lvl != 1:
            self.bc_host()
        if missing_players < 0:
            self.eject()
        elif not missing_players:
            self.take_everything_from_ground(looked)
            self.put_requirements_to_the_ground(requirements)
            if self.incantation():
                self.lvl += 1
                logger.warning(f"Level up to {self.lvl}!")
                self.bc_info()
                pass

    def run(self):
        self.cli.connect(self.ip, self.port)
        self.receive()
        while True:
            self.send(self.team)
            if self.receive() != "ko":
                break
        self.receive()
        logger.debug(f"AI is on the field {self.uuid}")
        if config.USE_INFINITE_FOOD:
            self.send("Cheat_infinite_resources")
            self.receive()
        self.bc_add()
        try:
            while True:
                inv = self.inventory()
                if inv["food"] <= self.food_search_threshold:
                    self.looking_for_food = True
                elif inv["food"] >= self.stone_search_threshold:
                    self.looking_for_food = False
                looked = self.look()
                if self.looking_for_food:
                    self.search(looked, ["food"])
                self.handle_messages()
                if self.is_host() or self.lvl == 1 and not self.looking_for_food:
                    if self.add_new_ally(incantation_requirements[self.lvl + 1]):
                        continue
                    if self.count_current_lvl() < incantation_requirements[self.lvl + 1]["player"] - 1:
                        continue
                    if has_requirements(inv, self.lvl + 1):
                        self.host_incantation(looked)
                    else:
                        self.search(looked, generate_missing_res(inv, incantation_requirements[self.lvl + 1]))
        # TODO: Add custom error for player death
        except:
            logger.error("AI is dead!")
            try:
                self.bc_rem()
            except:
                pass
        logger.debug('End of AI run method')

    def handle_messages(self) -> None:
        went_to_host = False
        for i in self.messages:
            tmp = i[1].split()
            if len(tmp) not in [2, 3]:
                continue
            if tmp[1] == "ADD":
                logger.debug(f"Add new ally {tmp[0]}")
                self.others[1][tmp[0]] = True
                self.bc_info()
            elif tmp[1] == "REM":
                for _, y in self.others.items():
                    if tmp[0] in y:
                        del y[tmp[0]]
            elif tmp[1] == "INFO":
                try:
                    if int(tmp[2]) != 1 and tmp[0] in self.others[int(tmp[2]) - 1]:
                        del self.others[int(tmp[2]) - 1][tmp[0]]
                    self.others[int(tmp[2])][tmp[0]] = True
                    logger.debug(f"Add {tmp[0]} of level {tmp[2]}")
                except ValueError:
                    logger.warning("Something fucked up in INFO")
            elif tmp[1] == "HOST" and not self.looking_for_food and tmp[0] in self.others[self.lvl] and not went_to_host and self.is_valid_participant():
                went_to_host = True
                self.go_to_direction(i[0])
        self.messages = []

    def go_to_direction(self, direction: int) -> None:
        if direction == 1:
            self.forward()
        elif direction == 2:
            self.forward()
            self.left()
            self.forward()
        elif direction == 3:
            self.left()
            self.forward()
        elif direction == 4:
            self.left()
            self.forward()
            self.left()
            self.forward()
        elif direction == 5:
            self.left()
            self.left()
            self.forward()
        elif direction == 6:
            self.right()
            self.forward()
            self.right()
            self.forward()
        elif direction == 7:
            self.right()
            self.forward()
        elif direction == 8:
            self.forward()
            self.right()
            self.forward()

    def is_host(self) -> bool:
        for i, _ in self.others[self.lvl].items():
            if int(i, base=16) < int(self.uuid, base=16):
                return False
        return True

    def add_new_ally(self, requirements: dict) -> bool:
        num_ally = self.count_below_lvl()
        if num_ally >= requirements["player"] - 1:
            return False
        if self.fork_timing > 0:
            self.fork_timing -= 1
            return True
        self.fork_timing = 50
        logger.debug(f"Need other allies | {num_ally} | {self.others}")
        if self.get_unused() == 0:
            self.fork()
        if config.USE_SUBPROCESS:
            subprocess.Popen(sys.argv)
        return True

    def count_current_lvl(self):
        return len(self.others[self.lvl])

    def count_below_lvl(self) -> int:
        result = 0
        for i, y in self.others.items():
            if i > self.lvl:
                return result
            result += len(y)
        return result

    def receive(self, is_incant=False) -> str:
        msg = self.cli.receive()
        if msg.startswith("Elevation") and not is_incant:
            self.is_incanting = True
            return self.receive(is_incant)
        if msg.startswith('Current') and not is_incant:
            self.lvl += 1
            self.is_incanting = False
            logger.warning(f"Level up to {self.lvl}!")
            self.bc_info()
            return self.receive(is_incant)
        if msg.startswith('message'):
            tmp = msg[8:].split(',')
            if len(tmp) == 1:
                return self.receive(is_incant)
            try:
                self.messages.append((int(tmp[0]), ",".join(tmp[1:])))
            except ValueError:
                # TODO: Add proper warning message
                pass
            return self.receive(is_incant)
        if msg.startswith('eject'):
            return self.receive(is_incant)
        return msg

    def send(self, msg: str) -> None:
        return self.cli.send(msg)

    def __str__(self):
        return f"AI: ip({self.ip}), port({self.port}), team({self.team})"

    def forward(self) -> bool:
        logger.debug("Command forward")
        self.send("Forward")
        response = self.receive()
        if response != "ok":
            logger.warning("KO: Command forward")
        return response == "ok"

    def right(self) -> bool:
        logger.debug("Command right")
        self.send("Right")
        response = self.receive()
        if response != "ok" and config.WARNING_ON_KO:
            logger.warning("KO: Command right")
        return response == "ok"

    def left(self) -> bool:
        logger.debug("Command left")
        self.send("Left")
        response = self.receive()
        if response != "ok" and config.WARNING_ON_KO:
            logger.warning("KO: Command left")
        return response == "ok"

    def look(self) -> list:
        logger.debug("Command look")
        self.send("Look")
        return [tiles.Tile(*[y.count(r) for r in tiles.Tile.__init__.__code__.co_varnames[1:]]) for y in
                [i.split() for i in self.receive()[1:-1].strip().split(',')]]

    def inventory(self) -> dict:
        logger.debug("Command inventory")
        self.send("Inventory")
        data = self.receive()
        data = data.strip()
        data = data[1:-1]
        data = ' '.join(data.split())
        data = data.replace(" ,", ",").replace(", ", ",")
        data = data.replace(" ", "=")
        inv = {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
        inv.update(eval(f"dict({data})"))
        return inv

    def broadcast(self, msg: str) -> bool:
        logger.debug(f"Command broadcast with text : {msg}")
        self.send(f"Broadcast {msg}")
        response = self.receive()
        if response != "ok" and config.WARNING_ON_KO:
            logger.warning("KO: Command broadcast")
        return response == "ok"

    def get_unused(self) -> int:
        logger.debug(f"Command get_unused")
        self.send("Connect_nbr")
        response = self.receive()
        return int(response)

    def fork(self) -> bool:
        logger.debug("Command fork")
        self.send("Fork")
        response = self.receive()
        if response != "ok" and config.WARNING_ON_KO:
            logger.warning("KO: Command fork")
        return response == "ok"

    def eject(self) -> bool:
        logger.debug("Command eject")
        self.send("Eject")
        response = self.receive()
        if response != "ok" and config.WARNING_ON_KO:
            logger.warning("KO: Command eject")
        return response == "ok"

    def take(self, obj: Objects) -> bool:
        logger.debug(f"Command take {objects_map[obj]}")
        self.send(f"Take {objects_map[obj]}")
        response = self.receive()
        if response != "ok" and config.WARNING_ON_KO:
            logger.warning("KO: Command take")
            logger.warning(response)
        return response == "ok"

    def put(self, obj: Objects) -> bool:
        logger.debug(f"Command put {objects_map[obj]}")
        self.send(f"Set {objects_map[obj]}")
        response = self.receive()
        if response != "ok" and config.WARNING_ON_KO:
            logger.warning("KO: Command put")
        return response == "ok"

    def incantation(self) -> bool:
        logger.debug("Command incantation")
        self.send("Incantation")
        logger.debug("Start incantation")
        response1 = self.receive(True)
        if response1 == "ko" and config.WARNING_ON_KO:
            logger.warning("KO: Command incantation 1")
        logger.debug("Waiting for phase 2...")
        response2 = self.receive(True)
        if response2 == "ko" and config.WARNING_ON_KO:
            logger.warning("KO: Command incantation 2")
        logger.debug("got to the end of incantation")
        logger.debug(response1)
        logger.debug(response2)
        return response1 != "ko" and response2 != "ko"

    def bc_add(self) -> bool:
        return self.broadcast(f"{self.uuid} ADD")

    def bc_rem(self) -> bool:
        return self.broadcast(f"{self.uuid} REM")

    def bc_host(self) -> bool:
        return self.broadcast(f"{self.uuid} HOST")

    # This exists solely to answer bc_add
    # And to level up
    def bc_info(self) -> bool:
        return self.broadcast(f"{self.uuid} INFO {self.lvl}")

    def is_valid_participant(self):
        uuid_list = [self.uuid]
        req = incantation_requirements[self.lvl + 1]
        for i in self.others[self.lvl]:
            uuid_list.append(i)
        if len(uuid_list) <= req["player"]:
            return True
        uuid_list.sort()
        if uuid_list.index(self.uuid) + 1 <= req["player"]:
            return True
        # logger.warning(uuid_list)
        # logger.warning(f"{self.uuid} nah bro")
        return False


class MyParser(argparse.ArgumentParser):
    def error(self, message: str) -> None:
        sys.stderr.write(f"error: {message}\n")
        self.print_help(sys.stderr)
        sys.exit(84)


# Parses the arguments and configs the logger
def main(av: list) -> int:
    logger.debug("Server starting")
    logger.debug("Creation of the argparser")
    parser = MyParser(conflict_handler="resolve")
    parser.add_argument("-p", dest="port", type=int, required=True)
    parser.add_argument("-n", dest="team", required=True)
    parser.add_argument("-h", dest="machine", default="localhost")
    if "-help" in av:
        parser.print_help(sys.stdout)
        return 0
    logger.debug("Begin argument parsing")
    args = parser.parse_args(av[1:])
    logger.debug("End argument parsing")
    my_ai = AI(args.machine, args.port, args.team)
    try:
        logger.debug("Launching the AI")
        my_ai.run()
    except ConnectionError as e:
        logger.error(f"Could not connect to remote host : {e}")
    return 0
