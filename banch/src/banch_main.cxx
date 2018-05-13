#include "banch/banch.hxx"
#include "menu/menu.hxx"
#include "banch/interactiveFunctions.hxx"

#include <functional>

int main(int argc, char ** argv)
{
	banch::RecipeBook myBook;

	menu::Menu mainMenu(std::cout, std::cin);
	mainMenu.add(menu::Option("list recipes",
								std::function<void()>(banch::Flist_recipes(
																	std::cout,
																	myBook))));
	mainMenu.add(menu::Option("add recipe",
								std::function<void()>(banch::Fadd_recipe(
																	std::cout,
																	std::cin,
																	myBook))));
	mainMenu.add(menu::Option("modify recipe",
								std::function<void()>(banch::Fmodify_recipe(
																	std::cout,
																	std::cin,
																	myBook))));
	mainMenu.add(menu::Option("remove recipe",
								std::function<void()>(banch::Fremove_recipe(
																	std::cout,
																	std::cin,
																	myBook))));
	mainMenu.add(menu::Option("save database to file",
								std::function<void()>(banch::Fsave_recipebook(
																	std::cout,
																	std::cin,
																	myBook))));
	mainMenu.add(menu::Option("load database from file",
								std::function<void()>(banch::Fload_recipebook(
																	std::cout,
																	std::cin,
																	myBook))));

	std::cout << "Welcome to banch ʘ‿ʘ" << std::endl;
	std::cout << " Please select one from the options below" << std::endl;
	mainMenu();

	return 0;
}
