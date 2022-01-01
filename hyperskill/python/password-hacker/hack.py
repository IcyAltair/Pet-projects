import argparse
import socket
import sys


class Hacker:
    def __init__(self) -> None:
        self.parser = argparse.ArgumentParser(description="Hacking password")
        self.parser.add_argument("ip", type=str, help="IP address of resource")
        self.parser.add_argument("port", type=int, help="Port of IP address")
        self.parser.add_argument("password", type=str, help="Password of resource")
        self.ip_address, self.port, self.password = "", 0, ""
        self.buffer = 1024

    def parse(self):
        if len(sys.argv) < 4:
            print("Not enough arguments")
            sys.exit(1)
        args = self.parser.parse_args()
        self.ip_address = args.ip
        self.port = args.port
        self.password = args.password

    def connect(self):
        with socket.socket() as client_socket:
            hostname = self.ip_address
            port = self.port
            address = (hostname, port)

            client_socket.connect(address)

            data = self.password
            data = data.encode()

            client_socket.send(data)

            response = client_socket.recv(self.buffer)

            response = response.decode()
            print(response)


def main():
    hacker = Hacker()
    hacker.parse()
    hacker.connect()


if __name__ == "__main__":
    main()
