#ifndef BANCH_BANCH_MENU_HXX
#define BANCH_BANCH_MENU_HXX

/// \file menu.hxx
///
/// \brief a simple CLI interface for banch

#include <iostream>
#include <string>
#include <functional>
#include <sstream>

#include "nostl/list.hxx"

/// \brief this class uses the standard C++ string implementation
using std::string;

/// \brief namespace for the menu subproject
namespace menu {

//////////////////
// DECLARATIONS //
//////////////////

/// \brief simple option for the Menu
class Option {
public:
	/// \brief constructor with only name or nothing
	inline Option(string name = "") : name_(name) {}

	/// \brief constructor with two parameters
	///
	/// \param name name of the option
	/// \param fnctn function to execute when option is selected
	inline Option(string const name, std::function<void()> const & fnctn)
		: name_(name), function_(fnctn) {}

	/// \brief overloaded inserter operator
	///
	/// \param ostream to write to
	/// \param Option to write to ostream
	///
	/// \return the stream object
	friend std::ostream & operator<<(std::ostream &, Option const &);

	/// \brief call function method
	///
	/// \param argument to call contained function with
	inline void operator()() const { this->function_(); }


private:
	string name_; ///< the name that shows up in the menu after option number
	std::function<void()> function_; ///< function object the option can 'call'
}; // class Option


/// \brief a simple menu of Options
class Menu {
public:
	/// \brief constructor (only adds an exit option)
	inline Menu(std::ostream & os, std::istream & is)
		: os_(os), is_(is) { this->add(std::move(Option("exit menu"))); }


	/// \brief add option to the menu
	///
	/// \param option to add (use std::move)
	inline void add(Option const & opt) { this->options_.append(opt); }

	/// \brief get number of option entries in the menu
	///
	/// \return number of entries
	inline unsigned int number_of_entries() const;


	/// \brief display the menu
	void operator()() const;


private:
	nostl::List<Option> options_; ///< List of options in the menu
	std::ostream & os_; ///< stream the Menu can write into
	std::istream & is_; ///< stream the Menu can read from
}; // class Menu



////////////////////////
// INLINE DEFINITIONS //
////////////////////////

// class Menu //

unsigned int Menu::number_of_entries() const
{
	return this->options_.size();
}

} // namespace menu

#endif // BANCH_BANCH_MENU_HXX
