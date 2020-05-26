#!/usr/bin/python3

from book import Book
from recipe import Recipe


if __name__ == "__main__":
	r1 = Recipe("Moukraine à la glaviouze", 3, 80, ["i1", "i2", "i3"], "Niak", "breakfast")
	r2 = Recipe("Moukraine à la bile de vache", 3, 80, ["i1", "i2", "i3"], "Prek", "lunch")
	r3 = Recipe("Moukraine aux copeaux de foie de porc", 3, 80, ["i1", "i2", "i3"], "olok", "breakfast")

	print(r1)
	z = Book("Les meilleurs moukraines du monde", [r1, r2])
	print(z)
	z.add_recipe(r3)
	print(z)
	print(z.get_recipes_by_types("breakfast"))
