#ifndef BANCH_BANCH_INTERACTIVEFUNCTIONS_HXX
#define BANCH_BANCH_INTERACTIVEFUNCTIONS_HXX

/// \file interactiveFunctions.hxx
///
/// \brief function objects for a simple interface

#include "banch/banch.hxx"
#include "menu/menu.hxx"

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


/// \brief function object to prompt user with adding a new Beverage ingredient
class Fadd_beverage : Finteractive_function {
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
class Fadd_extra : Finteractive_function {
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


/// \brief function object to prompt user with creating a new Recipe
class Fadd_recipe : Finteractive_function {
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


/// \brief function object that lists Recipes in a RecipeBook
class Flist_recipes : Finteractive_function {
public:
	/// \brief constructor with 2 parameters
	///
	/// \param os stream to write to
	/// \param book RecipeBook object reference to list
	Flist_recipes(std::ostream & os, RecipeBook const & book)
		: Finteractive_function(os, std::cin), book_(book) {}

	/// \brief function that actually calls the RecipeBook's list() method
	inline void operator()() { book_.list(this->os_); }


private:
	RecipeBook const & book_; ///< reference to RecipeBook to list
}; // class Fadd_recipe

} // namespace banch

#endif // BANCH_BANCH_INTERACTIVEFUNCTIONS_HXX
