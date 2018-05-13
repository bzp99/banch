/// \file interactiveFunctions.hxx
///
/// \brief function definitons for interactiveFunctions.hxx

#include "banch/interactiveFunctions.hxx"

/// \brief namespace for the banch project
namespace banch {

// class Fadd_beverage //

void Fadd_beverage::operator()()
{
	// prompt for Beverage name
	this->os_ << "Please enter the beverage's name: ";
	std::string name;
	getline(this->is_, name);

	// prompt for Beverage quantity
	this->os_ << "Please enter how many units of the beverage is needed: ";
	std::string quantaString;
	int quanta;
	do
	{
		getline(this->is_, quantaString);
	}
	while (!(std::stringstream(quantaString) >> quanta) || quanta <= 0);

	// confirm
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

	if (confirm(this->os_, this->is_, extra))
	{
		this->recipe_.add(new Extra(extra));
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

	std::stringstream tmp;
	recipe->show(tmp);
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->book_.add(recipe);
	}
}

} // namespace banch

