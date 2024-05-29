from re import sub
from abc import ABC, abstractmethod


class FormatAction(ABC):
    @abstractmethod
    def __call__(self, line: str) -> str | None:
        return line


class FindReplace(FormatAction):
    def __init__(self, find: list[str] | str, replace: str):
        self.find = find if isinstance(find, list) else [find]
        self.replace = replace

    def __call__(self, line: str) -> str:
        new_line = line

        for f in self.find:
            new_line = new_line.replace(f, self.replace)

        return new_line

class RegexReplace(FormatAction):
    def __init__(self, find: str, replace: str):
        self.find = find
        self.replace = replace

    def __call__(self, line: str) -> str | None:
        return sub(self.find, self.replace, line)
