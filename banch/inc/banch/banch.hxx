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
	Recipe() : number_of_ingredients_(0) {}

	void add(Ingredient * new_ingredient)
	{
		if (number_of_ingredients_ >= kMaxIngredients)
		{
			throw std::out_of_range("jar full");
		}
		ingredients_[number_of_ingredients_++] = new_ingredient;
	}

	void show() const;

	void save() const;
	void load();

	~Recipe();

private:
	Ingredient * ingredients_[kMaxIngredients]; // heterogenous container
	unsigned int number_of_ingredients_;
};

void Recipe::show() const
{
	for (unsigned int i = 0; i < this->number_of_ingredients_; ++i)
	{
		print(this->ingredients_[i]);
	}
}

} // namespace banch

#endif // BANCH_HXX
