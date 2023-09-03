#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFCLASS(_name, _price_unit)                                        \
class _name : public Ingredient {                                           \
public:                                                                     \
_name(size_t units) : Ingredient{_price_unit, units} {                      \
    this->name = #_name;                                                    \
}                                                                           \
Ingredient* clone() {                                                       \
    return new _name(*this);                                                \
}                                                                           \
                                                                            \
std::string get_name() override { return this->name; }                      \
};

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);


#endif // SUB_INGREDIENTS_H