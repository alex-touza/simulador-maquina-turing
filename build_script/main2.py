from os import chdir
from pathlib import Path

from colorama import init

from environments import *

init()

chdir(Path(__file__).parent.resolve())

ROOT = "../"
ROOT_ABS = abspath(ROOT)

PROJECT_NAME = "simulador-maquina-turing"
DESTINATION_PATH = f"./dist"

extensions = [FileType("source files", "cpp"), FileType("header files", "h")]

common = Environment(ROOT_ABS, "./src/common", None)

environments = [
    Environment(ROOT_ABS, f"./src/{name}", f"{DESTINATION_PATH}/{name}") for name in ["tape", "master"]
]
common.scan(extensions)
common.show(Colors.blau("Common environment"))

for e in environments:
    e.scan(extensions)
    e.show()

print()
input("Press enter to begin copy...")

for e in environments:

    e.copy(common)
    e.format()
