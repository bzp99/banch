#ifndef INGREDIENTS_HXX
#define INGREDIENTS_HXX

#include "banch.hxx"

namespace banch {
namespace ingredients {

class Liquid : public Ingredient {
private:
	float volume_centilitres_;
};

class AlcoholicBeverage : public Ingredient {
private:
	float alcohol_content_ratio_;
};

class SoftDrink : public Ingredient {
private:
	float sugar_content_miligrams_;
};

class Enhancer : public Ingredient {};

class Juice : public SoftDrink {};

} // namespace ingredients 
} // namespace banch

#endif // INGREDIENTS_HXX
