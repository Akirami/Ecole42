#!/usr/bin/python3


class Recipe:
	def __init__(self, name, cooking_lvl, cooking_time, ingredients, description, recipe_type):
		if not isinstance(name, str):
			print("Name not a string")
			exit()
		self.name = name
		if not isinstance(cooking_lvl, int):
			print("cooking_lvl not an int")
			exit()
		if cooking_lvl > 5 or cooking_lvl < 1:
			print("cooking_lvl out of range (0, 5)")
			exit()
		self.cooking_lvl = cooking_lvl
		if not isinstance(cooking_time, int):
			print("cooking_time not an int")
			exit()
		if cooking_time < 0:
			print("cooking_time is negative")
			exit()
		self.cooking_time = cooking_time
		if not isinstance(ingredients, list):
			print("ingredients not  list")
			exit()
		for i in ingredients:
			if not isinstance(i, str):
				print("one ngredients is not a string")
				exit()
		self.ingredients = ingredients
		self.description = description
		if not isinstance(recipe_type, str):
			print("recipe_type not a string")
			exit()
		self.recipe_type = recipe_type
	def __str__(self):
		"""Return the string to print with the recipe info"""
		txt = ""
		txt += " Recipe: %s \n 	%s" % (self.name, self.description)
		return txt
