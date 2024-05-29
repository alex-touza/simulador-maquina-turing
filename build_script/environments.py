from __future__ import annotations

import fileinput
from abc import ABC, abstractmethod
from dataclasses import dataclass
from glob import glob
from os import mkdir, makedirs, rename
from os.path import abspath, join, relpath, isdir
from shutil import copy2, rmtree

from text import Estils, Colors
from actions import FormatAction


@dataclass
class FileType:
    name: str
    extension: str



class Environment:
    def __init__(self, root: str, origin_path: str, destination_path: str | None):
        self.root = root
        self.name = origin_path.split('/')[-1]

        self.origin_path = abspath(join(self.root, origin_path))
        self.destination_path = "" if destination_path is None else abspath(join(self.root, destination_path))
        self.files: dict[str, list[str]] | None = None

    def scan(self, extensions: list[FileType]):
        self.files: dict[str, list[str]] = {
            ext.name: glob(f"{self.origin_path}/**/*.{ext.extension}", recursive=True)
            for ext in extensions
        }

    @property
    def files_list(self):
        return [f for extFiles in self.files.values() for f in extFiles]

    def show(self, title: str | None = None):
        print(Colors.blau(f"Environment {Estils.brillant(self.name)}") if title is None else title)
        for k, v in {"Origin path": relpath(self.origin_path, self.root), "Destination path": "" if self.destination_path == "" else relpath(self.destination_path, self.root)}.items():
            if not v: continue
            value = f"{v:>40}"
            key = f"{k:<30}"
            print(f'{key} {Estils.brillant(value)}')

        for name, files in self.files.items():
            print(Estils.brillant(f"{len(files)} {name}"))
            for f in files:
                print(f"\t{relpath(f, self.root)}")

            print()

        print()

    def copy(self, common: Environment |None = None):
        print(Colors.blau(f"Copying environment {Estils.brillant(self.name)}..."))

        files = self.files_list
        if common:
            files.extend(common.files_list)

        if isdir(self.destination_path):
            print(Colors.groc("Destination path already exists. Removing directory..."))
            rmtree(self.destination_path)
            print(Colors.verd("Directory removed successfuly."))

        makedirs(self.destination_path)

        for i, f in enumerate(files, 1):
            print(f"Copying file {i} of {len(files)}: {f}")
            copy2(f, self.destination_path)

        print(Colors.verd("Files copied successfully."))
        print()


    def format(self, actions: list[FormatAction]):
        print(Colors.blau(f"Formatting enviornment {Estils.brillant(self.name)}..."))

        print(f"Renaming main file")
        rename(join(self.destination_path, "main.cpp"), join(self.destination_path, f"{self.name}.ino"))

        print("Fixing include directives...")
        for path in glob(f"{self.destination_path}/*"):
            with fileinput.input(path, inplace=True) as file:
                for line in file:
                    new_line = line
                    for action in actions:
                        new_line = action(new_line)

                    print(new_line, end='')


        print()


