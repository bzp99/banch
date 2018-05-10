#include "banch/menu.hxx"

/// \file banch.cxx
///
/// \brief function definitions of menu.hxx

/// \brief namespace for the banch project
namespace banch {

// class Option<> //

std::ostream & operator<<(std::ostream & os, Option const & obj)
{
	return os << obj.name_ << std::endl;
}

} // namespace banch
