import argparse
from collections import Counter
import hashlib
import sys
import os


class Duplicator:
    def __init__(self):
        self.directory = ""
        self.data = []
        self.ext = ""
        self.way = 0
        self.paths = []
        self.file = {"path": "", "ext": "", "size": ""}
        self.library = []
        self.hash_value = {"value": "", "size": "", "file": ""}
        self.duplicates = []
        self.hash_values = []

    def parse(self):
        ways = ("1", "2", "")
        if len(sys.argv) < 2:
            print("Directory is not specified")
            sys.exit(1)
        parser = argparse.ArgumentParser(description="Building file tree")
        parser.add_argument("dir", type=str, help="Main directory to build a tree of folders and files")
        args = parser.parse_args()
        self.directory = args.dir
        self.ext = input("Enter file format:\n")
        print("\nSize sorting options:")
        print("1. Descending")
        print("2. Ascending\n")
        self.way = input("Enter a sorting option:\n")
        while self.way not in ways:
            print("\nWrong option\n")
            self.way = input("Enter a sorting option:\n")

    def build_tree(self):
        for i in os.walk(self.directory):
            self.data.append(i)

    def print_tree(self, show=False):
        for address, dirs, files in self.data:
            for file in files:
                path = address + "\\" + file
                if show:
                    print(path)
                self.paths.append(path)

    def get_file_info(self):
        for path in self.paths:
            self.file.update({"path": path, "ext": os.path.splitext(path)[1][1:], "size": os.path.getsize(path)})
            if len(self.ext) != 0:
                if self.file["ext"] == self.ext:
                    self.library.append(self.file)
            else:
                self.library.append(self.file)
            self.file = {}

    def filter_and_sort(self):
        self.library = list(filter(lambda x: x.pop("ext", None), self.library))
        self.library = sorted(self.library, key=lambda x: x["size"], reverse=self.way == "1")

    def get_duplicates(self):
        paths, sizes = [], []
        for file in self.library:
            paths.append(file["path"])
            sizes.append(file["size"])
        self.library = []
        for i in range(len(sizes)):
            if sizes.count(sizes[i]) > 1:
                self.library.append({"path": paths[i], "size": sizes[i]})

    def print_library(self):
        size = 0
        for file in self.library:
            if file["size"] != size:
                size = file["size"]
                print(str(size) + " bytes")
            print(file["path"])

    def check_duplicates(self):
        choices = ("yes", "no")
        answer = input("Check for duplicates?\n")
        while answer not in choices:
            print("Wrong option")
            answer = input("Check for duplicates?\n")
        if answer == choices[0]:
            self.get_hash()
            self.clean_hash()
            self.print_hash()
        else:
            sys.exit(1)

    def get_hash(self):
        for file in self.library:
            self.hash_value["size"] = str(file["size"]) + " bytes"
            with open(file["path"], "rb") as f:
                hash_md5 = hashlib.md5()
                # for chunk in iter(lambda: f.read(4096), b""):
                hash_md5.update(f.read())
            self.hash_value["value"] = hash_md5.hexdigest()
            self.hash_value["file"] = file["path"]
            self.duplicates.append(self.hash_value)
            self.hash_values.append(self.hash_value["value"])
            self.hash_value = {"value": "", "size": "", "file": ""}

    def clean_hash(self):
        stats = Counter(self.hash_values)
        for v in self.hash_values:
            if stats[v] == 1:
                self.duplicates = list(filter(lambda x: x["value"] != v, self.duplicates))

    def print_hash(self):
        size, hash_value, counter = "", "", 1
        for duplicate in self.duplicates:
            if duplicate["size"] != size:
                print()
                print(duplicate["size"])
                print("Hash:", duplicate["value"])
                size = duplicate["size"]
                hash_value = duplicate["value"]
            if duplicate["value"] != hash_value:
                print("Hash:", duplicate["value"])
                hash_value = duplicate["value"]
            print(str(counter) + ".", duplicate["file"])
            counter += 1


def main():
    file_handler = Duplicator()
    file_handler.parse()
    file_handler.build_tree()
    file_handler.print_tree()
    file_handler.get_file_info()
    file_handler.filter_and_sort()
    file_handler.get_duplicates()
    file_handler.print_library()
    file_handler.check_duplicates()


if __name__ == "__main__":
    main()
