#ifndef CAULDRON_HPP
#define CAULDRON_HPP

#include "Potion.hpp"

class Cauldron {
private:
    int volume;
    vector<Ingredient> ingredients;
    Base currentBase;

public:
    Cauldron();
    Cauldron(int v, Base b);
    Cauldron(const Cauldron& other);

    ~Cauldron();

    Cauldron& operator=(const Cauldron& other);

    int getVolume() const;
    vector<Ingredient> getIngredients() const;
    Base getCurrentBase() const;

    void setVolume(int v);
    void setCurrentBase(Base b);

    void addIngredient(Ingredient ing);
    void clearIngredients();
    void printInfo() const;

    Potion createPotion(string potionName, string potionDescription, int price);
    void fillFromPotion(const Potion& potion);
};

#endif