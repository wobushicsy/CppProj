#include "espresso_based.h"

void EspressoBased::brew() {

}

std::vector<Ingredient *> &EspressoBased::get_ingredients() {
    return ingredients;
}

EspressoBased::~EspressoBased() {
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

EspressoBased::EspressoBased() = default;

EspressoBased::EspressoBased(const EspressoBased &esp) {
    for (Ingredient* ingredient : esp.ingredients) {
        ingredients.push_back(ingredient->clone());
    }
    name = esp.name;
}

void EspressoBased::operator=(const EspressoBased &esp) {
    for (Ingredient* ingredient : esp.ingredients) {
        ingredients.push_back(ingredient->clone());
    }
    name = esp.name;
}


