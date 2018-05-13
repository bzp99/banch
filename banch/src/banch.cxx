/// \file banch.cxx
///
/// \brief function definitions of banch.hxx

#include "banch/banch.hxx"
#include "banch/interactiveFunctions.hxx"

#include <cassert>
#include <iostream>

/// \brief namespace for the banch project
namespace banch {

// class Recipe //

void Recipe::remove(unsigned int const n)
{
	// assert that call is correct
	assert(((n > 0) && (n <= this->number_of_ingredients())));

	// get iterator to asked Ingredient
	nostl::Set<Ingredient *>::Iterator i = this->ingredients_.begin();
	for (unsigned int counter = 1; counter < n; counter++)
	{
		++i;
	}

	// remove that Ingredient
	this->remove(*i);
}

void Recipe::clear()
{
	// iterate though container and free memory
	nostl::Set<Ingredient *>::Iterator i = this->ingredients_.begin();
	while (i != this->ingredients_.end())
	{
		// we need to set this, otherwise we would have the i iterator point to
		// already freed locations
		Ingredient * tmp = *(i++);
		this->remove(tmp);
	}
}


void Recipe::show(std::ostream & os, bool numbered) const
{
	unsigned int counter = 0; // only needed if numbered
	os << std::endl;
	os << "Recipe: " << this->name_ << std::endl;
	printSep(os);
	for (nostl::Set<Ingredient *>::Iterator i = this->ingredients_.begin();
			i != this->ingredients_.end();
			++i)
	{
		if (numbered)
		{
			os << ++counter << ')' << ' ';
		}
		os << '-' << ' ';
		(*i)->print(os);
	}
}

void Recipe::serialize(std::ostream & os) const
{
	// start of recipe record
	os << "startrecipe" << std::endl;

	// name of recipe
	os << this->name_ << std::endl;

	// recipe ingredients
	for (nostl::Set<Ingredient *>::Iterator i = this->ingredients_.begin();
			i != this->ingredients_.end();
			++i)
	{
		(*i)->serialize(os);
	}

	// end of recipe record
	os << "endrecipe" << std::endl;
}

void Recipe::deserialize(std::istream & is)
{
	getline(is, this->name_);

	string currentLine;
	while (getline(is, currentLine) && currentLine != string("endrecipe"))
	{
		if (currentLine == string("beverage"))
		{
			Beverage * beverage = new Beverage;
			beverage->deserialize(is);
			this->add(beverage);
		}
		if (currentLine == string("extra"))
		{
			Extra * extra = new Extra;
			extra->deserialize(is);
			this->add(extra);
		}
	}
}


// class RecipeBook //

void RecipeBook::clear()
{
	// iterate though container and free memory
	nostl::Set<Recipe *>::Iterator i = this->recipes_.begin();
	while (i != this->recipes_.end())
	{
		// we need to set this, otherwise we would have the i iterator point to
		// already freed locations
		Recipe * tmp = *(i++);
		this->remove(tmp);
	}
}

Recipe & RecipeBook::getNth(unsigned int n)
{
	// assert correct call
	assert((n > 0) && (n <= this->number_of_entries()));

	// find Recipe asked for
	nostl::Set<Recipe *>::Iterator i = this->recipes_.begin();
	for (unsigned int k = 1; k < n; ++k)
	{
		++i;
	}
	// i now points to chose Recipe

	return **i;
}

void RecipeBook::list(std::ostream & os, bool numbered) const
{
	unsigned int counter = 0; // only needed if numbered
	for (nostl::Set<Recipe *>::Iterator i = this->recipes_.begin();
			i != this->recipes_.end();
			++i)
	{
		os << std::endl;
		if (numbered)
		{
			os << "### " << ++counter << " ###";
		}
		(*i)->show(os);
		os << std::endl;
	}
}

void RecipeBook::serialize(std::ostream & os) const
{
	for (nostl::Set<Recipe *>::Iterator i = this->recipes_.begin();
			i != this->recipes_.end();
			++i)
	{
		(*i)->serialize(os); 
	}
}

void RecipeBook::deserialize(std::istream & is)
{
	string currentLine;
	while (getline(is, currentLine))
	{
		if (currentLine == "startrecipe")
		{
			Recipe * recipe = new Recipe;
			recipe->deserialize(is);
			this->add(recipe);
		}
	}
}

} // namespace banch
