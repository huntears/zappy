##
## EPITECH PROJECT, 2021
## zappy_ai
## File description:
## Client
##

from collections import deque
import zappy_networking


class CommandCallback:
    def __init__(self, func, cmd_pop: bool):
        self.func = func
        self.cmd_pop = cmd_pop


class Client:
    on_message = {}
    on_command = {}

    def __init__(self) -> None:
        self.read_buffer = ""
        self.write_buffer = ""
        self.command_queue = deque()
        self.fd = 0
        self.running = True
        print("Client initialized")

    def connect(self, ip: str, port: int) -> None:
        self.fd = zappy_networking.connect(ip, port)
        print(f"Client connected successfully to {ip}:{port}")

    def disconnect(self) -> None:
        if self.fd != 0:
            zappy_networking.disconnect(self.fd)
            print("Client disconnected")
        self.fd = 0

    def send(self, cmd: str) -> None:
        if str == "":
            return
        self.write_buffer += cmd + '\n'
        self.command_queue.append(cmd.split())

    def __del__(self) -> None:
        self.disconnect()

    def receive(self) -> str:
        if '\n' in self.read_buffer:
            tmp = self.read_buffer[:self.read_buffer.index('\n')]
            self.read_buffer = self.read_buffer[self.read_buffer.index('\n') + 1:]
            return tmp
        self.read_buffer += zappy_networking.receive(self.fd)
        return self.receive()

    def run(self) -> None:
        while self.running:
            try:
                received = self.receive()
            except:
                self.running = False
                continue
            if len(received.split()) == 0:
                continue
            if received.split()[0] in Client.on_message:
                Client.on_message[received.split()[0]](self, received.split())
            elif len(self.command_queue) != 0:
                cmd = self.command_queue.pop()
                if cmd[0] in Client.on_command:
                    Client.on_command[cmd[0]].func(self, received.split())
                    if not Client.on_command[cmd[0]].cmd_pop:
                        self.command_queue.appendleft(cmd)
                else:
                    print("Unsupported input from the server :")
                    print(received)
            else:
                print("Unsupported input from the server :")
                print(received)
            zappy_networking.send(self.fd, self.write_buffer)
            self.write_buffer = ""
        print("Run method stopped")


def on_message(msg: str):
    def inner(func):
        Client.on_message[msg] = func
    if msg in Client.on_message:
        raise RuntimeError(f"Key '{msg}' already exists")
    return inner


def on_command(cmd: str, pop_cmd=True):
    def inner(func):
        Client.on_command[cmd] = CommandCallback(func, pop_cmd)
    if cmd in Client.on_command:
        raise RuntimeError(f"Key '{cmd}' already exists")
    return inner
