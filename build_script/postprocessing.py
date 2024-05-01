from os import rename, remove
from os.path import join, abspath
from text import Colors

class FindReplace:
    # Ruta relativa a la carpeta "dist".
    def __init__(self, path: str, pairs: list[tuple[str, str]] | tuple[str, str]):
        self.path = path
        self.pairs = pairs if isinstance(pairs, list) else [pairs]

    def __call__(self, root: str):
        s = ""
        with open(root + self.path, 'r') as file:
            s = file.read()
            for old, new in self.pairs:
                s = s.replace(old, new)

        remove(root + self.path)

        with open(root + self.path, 'w') as file:
            file.write(s)

    def __str__(self):
        return Colors.gris('Find and replace -- ') + Colors.blau(self.path) + Colors.gris(':') + ''.join(
            [('\n\t' + Colors.groc(
                old) + Colors.gris(
                ' => ') + (Colors.gris('(empty)') if new == "" else Colors.verd(new))) for old, new in self.pairs])

    def repr(self):
        return f"Find and replace -- {self.path} -- {len(self.pairs)} pairs"


class Rename:
    def __init__(self, oldPath: str, newPath: str):
        self.oldPath = oldPath
        self.newPath = newPath

    def __call__(self, root: str):
        rename(root + self.oldPath, root + self.newPath)

    def __str__(self):
        return Colors.gris('Rename -- ') + Colors.blau(self.oldPath) + Colors.gris(' => ') + Colors.verd(self.newPath)

    def repr(self):
        return f"Rename -- {self.oldPath} => {len(self.newPath)}"
