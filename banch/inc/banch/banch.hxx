#ifndef BANCH_BANCH_HXX
#define BANCH_BANCH_HXX

#include "nostl/string.hxx"
#include "nostl/set.hxx"
#include "measure/measure.hxx"

namespace banch {

class Ingredient {
using nostl::String;

public:
	Ingredient(String const name, double const amount, nostl::String unit)
		:	name_(name), amount_(amount, unit) {}

	void print(std::ostream & os) const
	{
		os << this->amount_ << this->name_;
	}


private:
	measure::Measure<double> amount_;
	nostl::String name_;
};

class Recipe {
public:
	void add(Ingredient const * addendum)
	{
		this->ingredients_.insert(addendum);
	}

	void remove(Ingredient const * delendum)
	{
		this->ingredients_.remove(delendum);
	}

	void show() const
	{
		for (nostl::Set<Ingredient*>::Iterator i = this->ingredients_.begin();
				i != this->ingredients_.end();
				++i)
		{
			i->show();
		}
	}

	void save() const;
	void load();


private:
	nostl::Set<Ingredient*> ingredients_; // heterogenous container
}; // class Recipe

} // namespace banch

#endif // BANCH_BANCH_HXX
