/// \file menu.cxx
///
/// function defintions for menu.hxx

#include "menu/menu.hxx"

/// \brief this class uses the standard C++ string implementation
using std::string;

/// \brief namspace for the menu subproject
namespace menu {

// class Option //

std::ostream & operator<<(std::ostream & os, Option const & obj)
{
	return os << obj.name_ << std::endl;
}

// class Menu //

void Menu::operator()() const
{
	while (true)
	{
		unsigned int option_count = 0;

		// iterator to options
		nostl::List<Option>::Iterator i = this->options_.begin();

		// list options with numbers
		this->os_ << std::endl; // aesthetics
		while (i != this->options_.end())
		{
			this->os_ << option_count++ << ')' << ' ' << *(i++);
		}

		// get input from user
		std::string input;
		int selection;
		do
		{
			this->os_ << std::endl;

			this->os_ << ">> ";
			getline(this->is_, input);
		}
		while (!(std::stringstream(input) >> selection) ||
				selection < 0 || selection > (this->number_of_entries() - 1));

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

// class AdvancedMenu //

// TODO this is literally a copy--paste method
void AdvancedMenu::operator()() const
{
	while (true)
	{
		this->function_();

		unsigned int option_count = 0;

		// iterator to options
		nostl::List<Option>::Iterator i = this->options_.begin();

		// list options with numbers
		this->os_ << std::endl; // aesthetics
		while (i != this->options_.end())
		{
			this->os_ << option_count++ << ')' << ' ' << *(i++);
		}

		// get input from user
		std::string input;
		int selection;
		do
		{
			this->os_ << std::endl;

			this->os_ << ">> ";
			getline(this->is_, input);
		}
		while (!(std::stringstream(input) >> selection) ||
				selection < 0 || selection > (this->number_of_entries() - 1));

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
