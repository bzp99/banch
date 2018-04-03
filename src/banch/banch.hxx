#ifndef BANCH_HXX
#define BANCH_HXX

#include "../nostl/string.hxx"

namespace banch {

class Ingredient {
public:
	// stuff

private:
	nostl::String name;
};

class Recipe {
public:
	Recipe();

	void show() const;
	void add();

	void save() const;
	void load();

	~Recipe();

private:
	Ingredient * ingredients;
};

}

#endif // BANCH_HXX
