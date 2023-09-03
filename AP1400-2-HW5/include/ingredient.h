#ifndef INGREDIENT_H
#define INGREDIENT_H

using std::size_t;

class Ingredient {
public:
    double get_price_unit() {
        return price_unit;
    }

    size_t get_units() {
        return units;
    }

    virtual std::string get_name() = 0;

    double price() {
        return price_unit * static_cast<double>(units);
    }

    virtual Ingredient* clone() = 0;


protected:
    Ingredient(double price_unit, size_t units)
            : price_unit(price_unit), units(units) {}

    double price_unit;
    size_t units;
    std::string name;
};

#endif // INGREDIENT_H