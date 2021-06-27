import zappy_networking
from logger import logger


class Client:
    def __init__(self) -> None:
        self.read_buffer = ""
        self.write_buffer = ""
        self.fd = 0
        logger.debug("Client initialized")

    def connect(self, ip: str, port: int) -> None:
        self.fd = zappy_networking.connect(ip, port)
        logger.info(f"Client connected successfully to {ip}:{port}")

    def disconnect(self) -> None:
        if self.fd != 0:
            zappy_networking.disconnect(self.fd)
            logger.info("Client disconnected")
        self.fd = 0

    def send(self, cmd: str) -> None:
        if str == "":
            return
        self.write_buffer += cmd + '\n'
        zappy_networking.send(self.fd, self.write_buffer)
        self.write_buffer = ""

    def __del__(self) -> None:
        self.disconnect()

    def receive(self) -> str:
        if '\n' in self.read_buffer:
            tmp = self.read_buffer[:self.read_buffer.index('\n')]
            self.read_buffer = self.read_buffer[self.read_buffer.index('\n') + 1:]
            if tmp == "dead":
                raise RuntimeError("I'm dead lul")
            return tmp
        self.read_buffer += zappy_networking.receive(self.fd)
        return self.receive()
