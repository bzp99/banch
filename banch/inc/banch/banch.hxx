#ifndef BANCH_BANCH_HXX
#define BANCH_BANCH_HXX

#include "nostl/string.hxx"
#include "nostl/set.hxx"

namespace banch {

class Ingredient {
public:
	Ingredient(nostl::String const name, unsigned int const quanta)
		:	name_(name), quanta_(quanta) {}

	void print(std::ostream & os) const
	{
		os << this->amount_ << " units of " << this->name_;
	}


private:
	nostl::String name_;
	unsigned int quanta_;
}; // class Ingredient

class Recipe : public Serializable {
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
			i->print();
		}
	}


private:
	nostl::Set<Ingredient*> ingredients_; // heterogenous container
}; // class Recipe

} // namespace banch

#endif // BANCH_BANCH_HXX
