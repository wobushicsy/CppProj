#include "cappuccino.h"

Cappuccino::Cappuccino() {
    name = "Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino &cap) : EspressoBased(cap) {
    for (Ingredient* ingredient : cap.side_items) {
        side_items.push_back(ingredient->clone());
    }
}

Cappuccino::~Cappuccino() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino &cap) {
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

std::string Cappuccino::get_name() {
    return name;
}

double Cappuccino::price() {
    double total_price = 0;
    for (Ingredient* ingredient : ingredients) {
        total_price += ingredient->price();
    }
    for (Ingredient* ingredient : side_items) {
        total_price += ingredient->price();
    }

    return total_price;
}

void Cappuccino::add_side_item(Ingredient *side) {
    side_items.push_back(side);
}

std::vector<Ingredient *> &Cappuccino::get_side_items() {
    return side_items;
}
