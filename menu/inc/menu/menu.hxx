#ifndef BANCH_BANCH_MENU_HXX
#define BANCH_BANCH_MENU_HXX

/// \file menu.hxx
///
/// \brief a simple CLI interface for banch

#include <iostream>
#include <string>
#include <functional>

#include "nostl/list.hxx"

/// \brief this class uses the standard C++ string implementation
using std::string;

/// \brief namespace for the menu subproject
namespace menu {

/// \brief simple option for the menu
class Option {
public:
	/// \brief constructor with only name or nothing
	Option(string name = "") : name_(name) {}

	/// \brief constructor with two parameters
	///
	/// \param name name of the option
	/// \param fnctn function to execute when option is selected
	Option(string const name, std::function<void()> const & fnctn)
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
	inline void operator()() const;

private:
	string name_;
	std::function<void()> function_;
}; // class Option

class Menu {
public:
	/// \brief constructor (only adds an exit option)
	inline Menu();

	/// \brief add option to the menu
	///
	/// \param option to add (use std::move)
	inline void add(Option const &);

	/// \brief get number of option entries in the menu
	///
	/// \return number of entries
	unsigned int number_of_entries() const;


	/// \brief display the menu
	inline void operator()(std::ostream & = std::cout,
							std::istream & = std::cin) const;


private:
	nostl::List<Option> options_;
}; // class Menu


////////////////////////
// INLINE DEFINITIONS //
////////////////////////

// class Option //

void Option::operator()() const
{
	function_();
}

std::ostream & operator<<(std::ostream & os, Option const & obj)
{
	return os << obj.name_ << std::endl;
}

// class Menu //

Menu::Menu()
{
	this->add(std::move(Option("exit menu")));
}

void Menu::add(Option const & opt)
{
	this->options_.append(opt);
}

unsigned int Menu::number_of_entries() const
{
	return this->options_.size();
}

void Menu::operator()(std::ostream & os, std::istream & is) const
{
	while (true)
	{
		unsigned int selection; // the user's choice
		unsigned int option_count = 0; // options are numbered from 0

		// iterator to options
		nostl::List<Option>::Iterator i = this->options_.begin();

		// list options with numbers
		while (i != this->options_.end())
		{
			os << option_count++ << *(i++);
		}

		// get input from user
		do
		{
			is >> selection;
		}
		while (selection <= 0 || selection > this->number_of_entries());

		// 0 is always the exit option
		if (selection == 0)
		{
			break;
		}

		// iterate until option
		i = this->options_.begin();
		for (unsigned int k = 0; k < selection; ++k)
		{
			++i;
		}

		// call option
		(*i)();
	}
}

} // namespace menu

#endif // BANCH_BANCH_MENU_HXX
