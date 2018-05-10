#ifndef BANCH_BANCH_HXX
#define BANCH_BANCH_HXX

/// \file banch.hxx
///
/// \brief everything needed for drink-recipe keeping

#include "nostl/set.hxx"
#include "nostl/serializable.hxx"

/// \brief this class uses the standard C++ string implementation
using std::string;

/// \brief namespace for the banch project
namespace banch {

//////////////////
// DECLARATIONS //
//////////////////

/// \brief abstract class for drink ingredients
class Ingredient : public nostl::Serializable {
public:
	/// \brief virtual method for printing the ingredient prettily
	///
	/// \param stream to print into
	virtual void print(std::ostream &) const = 0;

	/// \brief virtual destructor
	virtual ~Ingredient() {}
}; // class Ingredient

/// \brief derived ingredient class for actual liquid beverages
class Beverage : public Ingredient {
public:
	/// \brief constructor with default arguments
	///
	/// \param name the name we can refer to the beverage as
	/// \param quanta the quantity used in the recipe expressed in units
	Beverage(string const name = "", unsigned int const quanta = 0)
		:	name_(name), quanta_(quanta) {}

	/// \brief implementation of the print method
	///
	/// \param os stream to print into
	inline void print(std::ostream & os) const;


	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	inline void serialize(std::ostream & os) const;

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	inline void deserialize(std::istream & is);


private:
	string name_; ///< the name of the beverage, for example: "Coke"
	unsigned int quanta_; ///< the quantity of the beverage in the recipe
							///< expressed in units
}; // class Beverage

/// \brief a derived ingredient class for everything that's not a beverage
///
/// This is for modelling ingredients that aren't drinks, for example a slice of
/// lemon or something.
class Extra : public Ingredient {
public:
	/// \brief constructor with default argument
	///
	/// \param text the extra itself
	Extra(string const text = "") : text_(text) {}

	/// \brief implementation of the print method
	///
	/// \param os stream to print into
	inline void print(std::ostream & os) const;


	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	inline void serialize(std::ostream & os) const;

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	inline void deserialize(std::istream & is);


private:
	string text_; ///< the extra, for example: "A cherry"
}; // class Extra

/// \brief class that contains ingredients (well, pointers to them)
class Recipe : public nostl::Serializable {
public:
	/// \brief constructor with default argument
	///
	/// \param name the name of the Recipe
	Recipe(string const name = "") : name_(name) {}

	/// \brief method that adds an ingredient
	///
	/// \param addendum ingredient to add
	inline void add(Ingredient * addendum);

	/// \brief method that removes an ingredient
	///
	/// \param delendum ingredient to remove
	inline void remove(Ingredient * delendum);

	/// \brief method that clears the recipe
	void clear();


	/// \brief method that prints all ingredients
	///
	/// \param os stream to print into
	void show(std::ostream & os) const;

	/// \brief method that prints number of ingredients in recipe
	///
	/// \return the number of ingredients
	inline unsigned int number_of_ingredients() const;


	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	void serialize(std::ostream & os) const;

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	void deserialize(std::istream & is);


	/// \brief destructor (frees memory)
	inline ~Recipe();


private:
	string name_; ///< name of the recipe
	nostl::Set<Ingredient *> ingredients_; ///< heterogenous container
											///< of Ingredient*s
}; // class Recipe

/// \brief a collection of Recipes
class RecipeBook : public nostl::Serializable {
public:
	/// \brief add recipe to the collection
	///
	/// \param addendum recipe to add
	inline void add(Recipe * addendum);

	/// \brief remove a recipe from the collection
	///
	/// \param delendum recipe to remove
	inline void remove(Recipe * delendum);

	/// \brief method that clears the book
	void clear();


	/// \brief list all recipes in the book
	///
	/// \param os stream to print into
	void list(std::ostream & os) const;

	/// \brief method that tells how many recipes there are in the book
	///
	/// \return the number of contained recipes
	inline unsigned int number_of_entries() const;


	/// \brief implementation of the serialization method
	///
	/// \param os stream to serialize into
	void serialize(std::ostream & os) const;

	/// \brief implementation of the deserialization method
	///
	/// \param is stream to deserialize from
	void deserialize(std::istream & is);


	/// \brief destructor (frees memory)
	inline ~RecipeBook();


private:
	nostl::Set<Recipe *> recipes_; ///< set containing the recipes (pointers)
}; // class RecipeBook



////////////////////////
// INLINE DEFINITIONS //
////////////////////////

// class Beverage //

void Beverage::print(std::ostream & os) const
{
	os << this->quanta_ << " units of " << this->name_ << std::endl;
}

void Beverage::serialize(std::ostream & os) const
{
	os << "beverage" << std::endl;
	os << this->name_ << std::endl;
	os << this->quanta_ << std::endl;
}

void Beverage::deserialize(std::istream & is)
{
	getline(is, this->name_);
	(is >> this->quanta_).ignore(1); // ignore is needed to flush the buffer
}


// class Garnish //

void Extra::print(std::ostream & os) const
{
	os << this->text_ << std::endl;
}

void Extra::serialize(std::ostream & os) const
{
	os << "extra" << std::endl;
	os << this->text_ << std::endl;
}

void Extra::deserialize(std::istream & is)
{
	getline(is, this->text_);
}


// class Recipe //

void Recipe::add(Ingredient * addendum)
{
	this->ingredients_.insert(addendum);
}

void Recipe::remove(Ingredient * delendum)
{
	// get rid of pointer
	this->ingredients_.remove(delendum);

	// free memory
	delete delendum;
}

unsigned int Recipe::number_of_ingredients() const
{
	return this->ingredients_.size();
}

Recipe::~Recipe()
{
	this->clear();
}


// class RecipeBook //

void RecipeBook::add(Recipe * addendum)
{
	this->recipes_.insert(addendum);
}

void RecipeBook::remove(Recipe * delendum)
{
	// get rid of pointer
	this->recipes_.remove(delendum);

	// free memory
	delete delendum;
}

unsigned int RecipeBook::number_of_entries() const
{
	return this->recipes_.size();
}

RecipeBook::~RecipeBook()
{
	this->clear();
}

} // namespace banch

#endif // BANCH_BANCH_HXX
