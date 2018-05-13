/// \file interactiveFunctions.hxx
///
/// \brief function definitons for interactiveFunctions.hxx

#include "banch/interactiveFunctions.hxx"

/// \brief namespace for the banch project
namespace banch {

///////////////
// FUNCTIONS //
///////////////

bool confirm(std::ostream & os, std::istream & is, std::string const text)
{
		os << '\t' << text << std::endl;
		os << "Confirm? [y/n] ";
		std::string confirmation;
		do
		{
			getline(is, confirmation);
		} while (!(confirmation == "y" || confirmation == "n"));

		if (confirmation == "y")
		{
			return true;
		}
		else
		{
			return false;
		}
}

unsigned int askNumber(std::ostream& os,
						std::istream & is,
						std::string const text)
{
	os << std::endl;
	os << text << ' ';
	std::string input;
	int rv;
	do
	{
		getline(is, input);
	}
	while (!(std::stringstream(input) >> rv));

	return rv;
}

void printSep(std::ostream & os, unsigned int n, char sepChar)
{
	for (unsigned int i = 0; i < n; ++i)
	{
		os << sepChar;
	}
	os << std::endl;
}



//////////////////////
// FUNCTION OBJECTS //
//////////////////////

// class Fadd_beverage //

void Fadd_beverage::operator()()
{
	// prompt for Beverage name
	this->os_ << "Please enter the beverage's name: ";
	std::string name;
	getline(this->is_, name);

	// prompt for Beverage quantity
	int quanta;
	do
	{
		quanta = askNumber(this->os_,
							this->is_,
							"Please enter how many units of the beverage is" \
							" needed:");
	}
	while (quanta <= 0);

	// confirm
	this->os_ << std::endl;
	this->os_ << "Will add:";
	std::stringstream tmp;
	tmp << quanta << " units of " << name;
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->recipe_.add(new Beverage(name, quanta));
	}
}


// class Fadd_extra //

void Fadd_extra::operator()()
{
	this->os_ << "Please enter the extra (garnish, decoration, etc): ";
	std::string extra;
	getline(this->is_, extra);

	this->os_ << std::endl;
	this->os_ << "Will add:";
	if (confirm(this->os_, this->is_, extra))
	{
		this->recipe_.add(new Extra(extra));
	}
}


// class Fremove_ingredient //

void Fremove_ingredient::operator()()
{
	// list Ingredients
	this->os_ << "0) cancel";
	this->recipe_.show(this->os_, /* numbering= */ true);
	this->os_ << std::endl;

	// make user choose one
	int selection;
	do
	{
		selection = askNumber(this->os_,
								this->is_,
								"Please enter number of ingredient to remove" \
								" (0 to cancel):");
	}
	while (selection < 0 || selection > this->recipe_.number_of_ingredients());

	// 0 cancels
	if (selection == 0)
	{
		return;
	}

	// confirm
	this->os_ << std::endl;
	this->os_ << "Will remove:";
	std::stringstream tmp;
	tmp << "ingredient number " << selection;
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->recipe_.remove(selection);
	}
}


// class Fadd_recipe //

void Fadd_recipe::operator()()
{
	// create recipe with chosen name
	this->os_ << "Please enter a name for the new recipe: ";
	std::string recipename;
	getline(this->is_, recipename);
	Recipe * recipe = new Recipe(recipename);

	menu::Menu menu(this->os_, this->is_);
	menu.add(menu::Option("add new beverage ingredient",
						std::function<void()>(Fadd_beverage(this->os_,
															this->is_,
															*recipe)
												)
					)
			);
	menu.add(menu::Option("add new extra ingredient",
						std::function<void()>(Fadd_extra(this->os_,
															this->is_,
															*recipe)
												)
					)
			);
	menu();

	// confirm
	this->os_ << std::endl;
	this->os_ << "Will add this recipe:" << std::endl;
	std::stringstream tmp;
	recipe->show(tmp);
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->book_.add(recipe);
	}
}


// class Fmodify_recipe //

void Fmodify_recipe::operator()()
{
	// list Recipes with numbers
	this->book_.list(this->os_, /* numbering= */ true);

	// ask user which Recipe to modify
	int selection;
	do
	{
		selection = askNumber(this->os_,
								this->is_,
								"Please enter number of recipe to modify" \
								" (0 cancels):");
	}
	while (selection < 0 || selection > this->book_.number_of_entries());

	// 0 cancels
	if (selection == 0)
	{
		return;
	}

	// get reference to chosen Recipe
	Recipe & recipe = this->book_.getNth(selection);

	this->os_ << "Editing:" << std::endl;
	recipe.show(this->os_);

	// create menu with options
	menu::Menu menu(this->os_, this->is_);
	menu.add(menu::Option("add beverage ingredient",
							std::function<void()>(Fadd_beverage(this->os_,
																this->is_,
																recipe))));
	menu.add(menu::Option("add extra ingredient",
							std::function<void()>(Fadd_extra(this->os_,
																this->is_,
																recipe))));
	menu.add(menu::Option("remove ingredient",
							std::function<void()>(Fremove_ingredient(this->os_,
																	this->is_,
																	recipe))));

	menu();
}

// class Fremove_recipe //

void Fremove_recipe::operator()()
{
	// list Recipes
	this->os_ << "0) cancel" << std::endl;
	this->book_.list(this->os_, /* numbering= */ true);
	this->os_ << std::endl;

	// make user choose one
	int selection;
	do
	{
		selection = askNumber(this->os_,
								this->is_,
								"Please enter number of Recipe to remove" \
								" (0 cancels):");
	}
	while (selection < 0 || selection > this->book_.number_of_entries());

	// 0 cancels
	if (selection == 0)
	{
		return;
	}

	// confirm
	this->os_ << std::endl;
	this->os_ << "Will remove:";
	std::stringstream tmp;
	tmp << "recipe number " << selection;
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->book_.remove(selection);
	}
}

} // namespace banch

