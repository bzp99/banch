#include "catch/catch.hpp"
#include "menu/menu.hxx"

using namespace menu;

// function object to test with
class say_hello {
public:
	say_hello(std::ostream & os) : os_(os) {}

	void operator()() const { os_ << "hello" << std::endl; }


private:
	std::ostream & os_;
};

TEST_CASE("An empty menu can be created", "[menu][sanity]")
{
	// create a menu and add our function object
	Menu foo;
	foo.add(Option("greet me", std::function<void()>(say_hello(std::cout))));

	// display menu
	foo();
}
