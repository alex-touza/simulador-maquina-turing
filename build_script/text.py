from typing import Any, overload
from colorama import Fore, Style


class Modificador:
	def __init__(self, c: str, r: str = Style.RESET_ALL):
		self.c = c
		self.r = r

	def __str__(self):
		return self.c

	def __call__(self, text: str | None=None) -> str | None:
		if text is None:
			print(self.c, end="")
			return
		else:
			return self.c + str(text) + self.r

	# Afegim funcions màgiques de suma perquè actuïn com a strings
	def __add__(self, other):
		return str(self) + other

	def __radd__(self, other):
		return other + str(self)


class Colors:
	blau = Modificador(Fore.BLUE)
	groc = Modificador(Fore.YELLOW)
	gris = Modificador(Fore.LIGHTBLACK_EX)
	verd = Modificador(Fore.GREEN)

	error = Modificador(Fore.RED)

	reset = Modificador(Fore.RESET)



class Estils:
	brillant = Modificador(Style.BRIGHT, Style.NORMAL)
	fosc = Modificador(Style.DIM, Style.NORMAL)


def titol(text: str):
	print()
	print(Estils.brillant(text))
	print("----------------")
