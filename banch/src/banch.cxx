/// \file banch.cxx
///
/// \brief function definitions of banch.hxx

#include "banch/banch.hxx"

/// \brief namespace for the banch project
namespace banch {

// class Recipe //

void Recipe::show(std::ostream & os) const
{
	os << "Recipe: " << this->name_ << std::endl;
	for (nostl::Set<Ingredient *>::Iterator i = this->ingredients_.begin();
			i != this->ingredients_.end();
			++i)
	{
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
	for (nostl::Set<Ingredient *>::Iterator i = ingredients_.begin();
			i != ingredients_.end();
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

void RecipeBook::list(std::ostream & os) const
{
	for (nostl::Set<Recipe *>::Iterator i = this->recipes_.begin();
			i != this->recipes_.end();
			++i)
	{
		(*i)->show(os);
		os << std::endl;
	}
}

void RecipeBook::serialize(std::ostream & os) const
{
	for (nostl::Set<Recipe *>::Iterator i = recipes_.begin();
			i != recipes_.end();
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
		if (currentLine == string("startrecipe"))
		{
			Recipe * recipe = new Recipe;
			recipe->deserialize(is);
			this->add(recipe);
		}
	}
}


} // namespace banch
