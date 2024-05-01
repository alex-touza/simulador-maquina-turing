from shutil import copy2
from glob import glob
from os import chdir, system, mkdir
from pathlib import Path
from os.path import abspath, join, isdir
from shutil import rmtree
from colorama import init
from text import Colors, Estils, titol
from postprocessing import Rename, FindReplace



init()

chdir(Path(__file__).parent.resolve())

ROOT = "../"
ORIGIN_PATHS = ["./src/master", "./src/tape"]
PROJECT_NAME = "casa-domotica"

DESTINATION_PATH = f"./dist/{PROJECT_NAME}/"
ORIGIN_DIR_NAME = ORIGIN_PATH.split('/')[-1]

ROOT_ABS = abspath(ROOT)
ORIGIN_PATH_ABS = abspath(join(ROOT_ABS, ORIGIN_PATH))
DESTINATION_PATH_ABS = abspath(join(ROOT_ABS, DESTINATION_PATH))

flatten_subdirectories = {"helpers", "pins"}
source_files = {"header": "h", "source": "cpp"}

postprocessing = [
    FindReplace("/main.cpp", [("#include <Arduino.h>\n", "")]),
    Rename("/main.cpp", f"/{PROJECT_NAME}.ino"),
    FindReplace("/Alarma.h", [("pins/", ""), ("helpers/", "")]),
    FindReplace("/Pantalla.h", [("pins/", ""), ("helpers/", "")]),
    FindReplace("/Iluminacio.h", [("pins/", ""), ("helpers/", "")]),
    FindReplace("/Joystick.h", [("pins/", ""), ("helpers/", "")]),
    FindReplace("/Motor.h", [("pins/", "")]),
    FindReplace("/Sensor.h", [("helpers/", "")]),
]

titol("CONFIG")
for k, v in {"Project name": PROJECT_NAME, "Origin path": ORIGIN_PATH, "Destination path": DESTINATION_PATH}.items():
    value = f"{v:>20}"
    print(f'{k:<30} {Estils.brillant(value)}')


if isdir(DESTINATION_PATH_ABS):
    Colors.groc()
    print()
    print("WARNING: Destination path already exists.\nCurrent content will be removed.")
    input("Press enter to confirm...")
    Colors.reset()
    try:
        rmtree(DESTINATION_PATH_ABS)
    except Exception as e:
        Colors.error()
        print(f"Error occured while clearing destination path.")
        print(e)
        Colors.reset()
        exit(1)

    print()
    print(Colors.verd("Destination path cleared successfully."))
    input("Press enter to continue...")


titol("FILES")
files_dict = {t: glob(f"{ORIGIN_PATH_ABS}/*.{ext}") for t, ext in source_files.items()}

for t, files in files_dict.items():
    for subdir in flatten_subdirectories:
        files.extend(glob(f"{ORIGIN_PATH_ABS}\\{subdir}/*.{source_files[t]}"))
    for path in files:
        print(Colors.blau(f"{t} ./" + path[path.rfind(ROOT_ABS) + len(ROOT_ABS) + 1:].replace('\\', '/')))
# for f in [abspath(p) for p in [glob(f"{ORIGIN_PATH_ABS}/*.{f}") for f in sourceFiles.values()]]:
#     print(Colors.blau("./" + f[f.rfind(ROOT_ABS) + len(ROOT_ABS) + 1:].replace('\\', '/')))
# print()

input("Press enter to continue...")

titol("POSTPROCESSING RULES")

for i, s in enumerate(postprocessing, 1):
    print(f"#{i} {s}")

print()
input(Colors.blau("Press enter to initiate the copy...") + Colors.groc)
Colors.reset()

system('cls||clear')
print("--------------")

print(Colors.blau(f"Copying directory {ORIGIN_PATH} to {DESTINATION_PATH}..."))

try:
    mkdir(DESTINATION_PATH_ABS)
    print("Created destination directory")
    for fl in list(files_dict.values()):
        for file in fl:
            print("Copied file", copy2(file, DESTINATION_PATH_ABS))

except Exception as e:
    print(Colors.error(f"Error occured while copying."))
    print(e)
    exit(1)

print(Colors.verd(f"Files copied successfully."))
print()

print(Colors.blau("Executing postprocessing rules..."))

n = len(postprocessing)

n_errors = 0

for i, s in enumerate(postprocessing, 1):
    try:
        s(DESTINATION_PATH_ABS)
    except Exception as e:
        n_errors += 1
        Colors.error()
        print(f"Error occured in postprocessing rule #{i}: {s.repr()}")
        print(e)
        Colors.reset()
    else:
        print(Colors.verd(f"Postprocessing rule {i} of {n} executed successfully."))

if n_errors:
    print(Colors.groc(f"Code processed with {n_errors} error(s)."))
else:
    print(Colors.verd("Code processed successfully."))

print()
input("Press enter to exit")
