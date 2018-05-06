#ifndef BANCH_BANCH_HXX
#define BANCH_BANCH_HXX

/// \file banch.hxx
///
/// \brief everything needed for drink-recipe keeping

#include "nostl/set.hxx"
#include "nostl/serializable.hxx"

/// \brief this class uses the standard C++ string implementation
using std::string;

/// \brief namespace for the banch project
namespace banch {

/// \brief abstract class for drink ingredients
class Ingredient : public nostl::Serializable {
public:
	/// \brief virtual method for printing the ingredient prettily
	///
	/// \param stream to print into
	virtual void print(std::ostream &) const = 0;

	/// \brief virtual destructor
	virtual ~Ingredient() {}
}; // class Ingredient

/// \brief derived ingredient: a beverage / drink
class Beverage : public Ingredient {
public:
	/// \brief constructor with default arguments
	///
	/// \param name the name we can refer to the beverage as
	/// \param quanta the quantity used in the recipe expressed in units
	Beverage(string const name = "", unsigned int const quanta = 0)
		:	name_(name), quanta_(quanta) {}

	/// \brief implementation of the print method
	///
	/// \param os stream to print into
	void print(std::ostream & os) const
	{
		os << this->quanta_ << " units of " << this->name_ << '\n';
	}

	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	void serialize(std::ostream & os) const
	{
		os << "beverage" << '\n';
		os << this->name_ << '\n' << this->quanta_ << '\n';
	}

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	void deserialize(std::istream & is)
	{
		getline(is, this->name_);
		(is >> this->quanta_).ignore(1);
	}


private:
	string name_; ///< the name of the beverage, for example: "Coke"
	unsigned int quanta_; ///< the quantity of the beverage in the recipe
							///< expressed in units
}; // class Beverage

/// \brief a derived ingredient class
///
/// This is for modelling ingredients that aren't drinks, for example a slice of
/// lemon or something.
class Extra : public Ingredient {
public:
	/// \brief constructor with default argument
	///
	/// \param text the extra itself
	Extra(string const text = "") : text_(text) {}

	/// \brief implementation of the print method
	///
	/// \param os stream to print into
	void print(std::ostream & os) const
	{
		os << this->text_ << '\n';
	}

	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	void serialize(std::ostream & os) const
	{
		os << "extra" << '\n';
		os << this->text_ << '\n';
	}

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	void deserialize(std::istream & is)
	{
		getline(is, this->text_);
	}

private:
	string text_; ///< the extra, for example: "A cherry"
}; // class Extra

/// \brief class that contains ingredients (well, pointers to them)
class Recipe : public nostl::Serializable {
public:
	/// \brief constructor with default argument
	///
	/// \param name the name of the Recipe
	Recipe(string const name = "") : name_(name) {}

	/// \brief method that adds an ingredient
	///
	/// \param addendum ingredient to add
	void add(Ingredient * addendum)
	{
		this->ingredients_.insert(addendum);
	}

	/// \brief method that removes an ingredient
	///
	/// \param delendum ingredient to remove
	void remove(Ingredient * delendum)
	{
		this->ingredients_.remove(delendum);
	}

	/// \brief method that prints all ingredients
	///
	/// \param os stream to print into
	void show(std::ostream & os) const
	{
		os << "Recipe: " << this->name_ << '\n';
		for (nostl::Set<Ingredient *>::Iterator i = this->ingredients_.begin();
				i != this->ingredients_.end();
				++i)
		{
			(*i)->print(os);
		}
	}

	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	void serialize(std::ostream & os) const
	{
		os << "startrecipe" << '\n';
		os << this->name_ << '\n';
		for (nostl::Set<Ingredient *>::Iterator i = ingredients_.begin();
				i != ingredients_.end();
				++i)
		{
			(*i)->serialize(os);
		}
		os << "endrecipe" << '\n';
	}

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	void deserialize(std::istream & is)
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


private:
	string name_; ///< name of the recipe
	nostl::Set<Ingredient *> ingredients_; ///< heterogenous container
											///< of Ingredient*s
}; // class Recipe

/// \brief a collection of Recipes
class RecipeBook : public nostl::Serializable {
public:
	/// \brief add recipe to the collection
	///
	/// \param addendum recipe to add
	void add(Recipe * addendum)
	{
		this->recipes_.insert(addendum);
	}

	/// \brief remove a recipe from the collection
	///
	/// \param delendum recipe to remove
	void remove(Recipe * delendum)
	{
		this->recipes_.remove(delendum);
	}

	/// \brief list all recipes in the book
	///
	/// \param os stream to print into
	void list(std::ostream & os) const
	{
		for (nostl::Set<Recipe *>::Iterator i = this->recipes_.begin();
				i != this->recipes_.end();
				++i)
		{
			(*i)->show(os);
			os << '\n';
		}
	}

	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	void serialize(std::ostream & os) const
	{
		for (nostl::Set<Recipe *>::Iterator i = recipes_.begin();
				i != recipes_.end();
				++i)
		{
			(*i)->serialize(os);
		}
	}

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	void deserialize(std::istream & is)
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


private:
	nostl::Set<Recipe *> recipes_; ///< set containing the recipes (pointers)
}; // class RecipeBook

} // namespace banch

#endif // BANCH_BANCH_HXX
