#include "mocha.h"

Mocha::Mocha() : EspressoBased() {
    name = "Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha &cap) : EspressoBased(cap) {
    for (Ingredient* ingredient : cap.side_items) {
        side_items.push_back(ingredient->clone());
    }
}

Mocha::~Mocha() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Mocha::operator=(const Mocha &cap) {
    if (&cap == this) {
        return;
    }
    for (Ingredient* ingredient : side_items) {
        delete ingredient;
    }
    side_items.clear();
    for (Ingredient* ingredient : cap.side_items) {
        side_items.push_back(ingredient->clone());
    }
}

std::string Mocha::get_name() {
    return name;
}

double Mocha::price() {
    double total_price = 0;
    for (Ingredient* ingredient : ingredients) {
        total_price += ingredient->price();
    }
    for (Ingredient* ingredient : side_items) {
        total_price += ingredient->price();
    }

    return total_price;
}

void Mocha::add_side_item(Ingredient *side) {
    side_items.push_back(side);
}

std::vector<Ingredient *> &Mocha::get_side_items() {
    return side_items;
}
