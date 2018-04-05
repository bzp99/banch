#ifndef BANCH_HXX
#define BANCH_HXX

#include "nostl/string.hxx"

const unsigned int kMaxIngredients = 20;

namespace banch {

class Ingredient {
public:
	virtual void print() const;

	virtual ~Ingredient(); // virtual destructor for this class shall be derived later
};

class Recipe {
public:
	Recipe();

	void add(Ingredient*);

	void show() const;

	void save() const;
	void load();

	~Recipe();

private:
	Ingredient * ingredients_[kMaxIngredients]; // heterogenous container
	unsigned int number_of_ingredients_;
};

} // namespace banch

#endif // BANCH_HXX
