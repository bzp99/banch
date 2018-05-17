#ifndef BANCH_BANCH_INTERACTIVEFUNCTIONS_HXX
#define BANCH_BANCH_INTERACTIVEFUNCTIONS_HXX

/// \file interactiveFunctions.hpp
///
/// \brief function objects for a simple interface

#include "banch.hpp"
#include "menu.hpp"

/// \brief namespace for the banch project
namespace banch {

///////////////
// FUNCTIONS //
///////////////

/// \brief global function to confirm things with user
///
/// \param stream to write messages into
/// \param stream to read user input from
/// \param text to prompt user with
///
/// \return true if the user confirms whatever
bool confirm(std::ostream &, std::istream &, std::string const);

/// \brief global function that asks the user for a number and validates it
///
/// \param stream to write messages into
/// \param stream to read number from
/// \param text to prompt user with
///
/// \return the number input by user
unsigned int askNumber(std::ostream &, std::istream &, std::string const);

/// \brief global function that prints a separator line to a stream
///
/// \param stream to print line into
/// \param number of characters to print
/// \param separator character
void printSep(std::ostream &, unsigned int = 25, char = '-');

//////////////////////
// FUNCTION OBJECTS //
//////////////////////

/// \brief abstract class for an interactive function object
class Finteractive_function {
public:
	/// \brief constructor with two parameters
	///
	/// \param os stream to write to
	/// \param is stream to read from
	Finteractive_function(std::ostream & os, std::istream & is)
		: os_(os), is_(is) {}

	/// \brief virtual operator() which all descendants will use
	virtual void operator()() = 0;

	/// \brief virtual destructor (required, since this class will have
	/// descendants)
	virtual ~Finteractive_function() {}


protected:
	std::ostream & os_; ///< stream the function object writes stuff into
	std::istream & is_; ///< stream the function object reads stuff from
}; // class Finteractive_function


/// \brief function object that lists Recipes in a RecipeBook
class Flist_recipes : public Finteractive_function {
public:
	/// \brief constructor with 2 parameters
	///
	/// \param os stream to write to
	/// \param book RecipeBook object reference to list
	///
	/// \note passes std::cin as an istream, but doesn't use it TODO
	Flist_recipes(std::ostream & os, RecipeBook const & book)
		: Finteractive_function(os, std::cin), book_(book) {}

	/// \brief function that actually calls the RecipeBook's list() method
	inline void operator()() { book_.list(this->os_); }


private:
	RecipeBook const & book_; ///< reference to RecipeBook to list
}; // class Fadd_recipe


/// \brief function object to prompt user with adding a new Beverage ingredient
class Fadd_beverage : public Finteractive_function {
public:
	/// \brief constructor with 3 parameters
	///
	/// \param os stream to write to
	/// \param is stream to read from
	/// \param recipe Recipe object reference to tamper with
	Fadd_beverage(std::ostream & os, std::istream & is, Recipe & recipe)
		: Finteractive_function(os, is), recipe_(recipe) {}

	/// \brief function that prompts user to create a new beverage ingredient
	void operator()();


private:
	Recipe & recipe_; ///< reference to Recipe to tamper with
}; // class Fadd_beverage


/// \brief function object to prompt user with adding a new Extra ingredient
class Fadd_extra : public Finteractive_function {
public:
	/// \brief constructor with 3 parameters
	///
	/// \param os stream to write to
	/// \param is stream to read from
	/// \param recipe Recipe object reference to tamper with
	Fadd_extra(std::ostream & os, std::istream & is, Recipe & recipe)
		: Finteractive_function(os, is), recipe_(recipe) {}

	/// \brief function that prompts the user to create a new Extra ingredient
	void operator()();


private:
	Recipe & recipe_; ///< reference to Recipe to tamper with
}; // class Fadd_beverage


class Fremove_ingredient : public Finteractive_function {
public:
	Fremove_ingredient(std::ostream & os, std::istream & is, Recipe & recipe)
		: Finteractive_function(os, is), recipe_(recipe) {}

	void operator()();


private:
	Recipe & recipe_; ///< reference to Recipe to tamper with
}; // class Fremove_ingredient


/// \brief function object to prompt user with creating a new Recipe
class Fadd_recipe : public Finteractive_function {
public:
	/// \brief constructor with 3 parameters
	///
	/// \param os stream to write to
	/// \param is stream to read from
	/// \param book RecipeBook object reference to tamper with
	Fadd_recipe(std::ostream & os, std::istream & is, RecipeBook & book)
		: Finteractive_function(os, is), book_(book) {}

	/// \brief function that prompts the user to create a new Recipe
	void operator()();


private:
	RecipeBook & book_; ///< reference to RecipeBook to tamper with
}; // class Fadd_recipe


/// \brief function object to prompt user with modifying an existing Recipe
class Fmodify_recipe : public Finteractive_function {
public:
	/// \brief contructor with 3 parameters
	///
	/// \param os stream to write into
	/// \param is stream to read from
	/// \param book RecipeBook object reference to tamper with
	Fmodify_recipe(std::ostream & os, std::istream & is, RecipeBook & book)
		: Finteractive_function(os, is), book_(book) {}

	/// \brief function that prompts the user to modify an existing Recipe
	void operator()();


private:
	RecipeBook & book_; ///< reference to RecipeBook to tamper with
}; // class Fmodify_recipe


/// \brief function object to prompt user with deleting an existing Recipe
class Fremove_recipe : public Finteractive_function {
public:
	/// \brief constructor with 3 parameters
	///
	/// \param os stream to write into
	/// \param is stream to read from
	/// \param book RecipeBook object reference to tamper with
	Fremove_recipe(std::ostream & os, std::istream & is, RecipeBook & book)
		: Finteractive_function(os, is), book_(book) {}

	/// \brief function that prompts the user to modify an existing Recipe
	void operator()();


private:
	RecipeBook & book_; ///< reference to RecipeBook to tamper with
}; // class Fremove_recipe


/// \brief function object that prompts the user with saving database to file
class Fsave_recipebook : public	Finteractive_function {
public:
	/// \brief constructor with 3 parameters
	///
	/// \param os stream to write into
	/// \param is stream to read from
	/// \param book RecipeBook object reference to tamper with
	Fsave_recipebook(std::ostream & os, std::istream & is, RecipeBook & book)
		: Finteractive_function(os, is), book_(book) {}

	/// \brief method that prompts the user for a filename and serializes book_
	void operator()();


private:
	RecipeBook & book_; ///< reference to RecipeBook to tamper with
}; // class Fsave_recipebook


/// \brief function object that prompts the user with loading a file into RAM
class Fload_recipebook : public	Finteractive_function {
public:
	/// \brief constructor with 3 parameters
	///
	/// \param os stream to write into
	/// \param is stream to read from
	/// \param book RecipeBook object reference to tamper with
	Fload_recipebook(std::ostream & os, std::istream & is, RecipeBook & book)
		: Finteractive_function(os, is), book_(book) {}

	/// \brief method that prompts the user for a filename and deserializes book_
	void operator()();


private:
	RecipeBook & book_; ///< reference to RecipeBook to tamper with
}; // class Fload_recipebook


/// \brief helper function object that acts like an std::bind
///
/// TODO actually use std::bind?
/// TODO this is not even an interactiveFunction...
class Fshow_recipe : public Finteractive_function {
public:
	/// \brief constructor with 3 paramters
	///
	/// \param os stream to write into
	/// \param is stream to read from
	/// \param recipe
	///
	/// \note passes std::cin as an istream, but doesn't use it TODO
	Fshow_recipe(std::ostream & os, Recipe & recipe)
		: Finteractive_function(os, std::cin), recipe_(recipe) {}

	/// \brief method that prints the recipe to the stream
	inline void operator()() { this->recipe_.show(this->os_); }


private:
	Recipe & recipe_; ///< reference to Recipe to tamper with
}; // class Fremove_recipe

} // namespace banch

#endif // BANCH_BANCH_INTERACTIVEFUNCTIONS_HXX
