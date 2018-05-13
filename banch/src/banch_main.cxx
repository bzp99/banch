#include "banch/banch.hxx"
#include "menu/menu.hxx"
#include "banch/interactiveFunctions.hxx"

#include <functional>

int main(int argc, char ** argv)
{
	banch::RecipeBook myBook;
	banch::Recipe * mySoleRecipe = new banch::Recipe("tester");
	mySoleRecipe->add(new banch::Beverage("apple juice", 5));
	mySoleRecipe->add(new banch::Extra("some extra stuff"));
	myBook.add(mySoleRecipe);

	menu::Menu mainMenu(std::cout, std::cin);
	mainMenu.add(menu::Option("list recipes",
								std::function<void()>(banch::Flist_recipes(
																	std::cout,
																	myBook
																			)
														)

								)
	);
	mainMenu.add(menu::Option("add recipe",
								std::function<void()>(banch::Fadd_recipe(
																	std::cout,
																	std::cin,
																	myBook
																		)
														)
								)
	);

	mainMenu();
	return 0;
}
