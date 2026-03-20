#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include "Potion.hpp"
#include "Cauldron.hpp"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Base waterBase("Water", "Regular water", 1.0);
    Base magicBase("Magic Base", "Ancient magic", 2.0);

    Ingredient herb("Herb", "Healing herb", "Heals");
    Ingredient mushroom("Mushroom", "Glowing mushroom", "Night vision");
    Ingredient crystal("Crystal", "Magic crystal", "Enhances magic");

    cout << "\n--- PART 1: POTIONS ---" << endl;

    vector<Ingredient> potion1Ings;
    potion1Ings.push_back(herb);
    potion1Ings.push_back(mushroom);

    Potion p1("Healing", "Restores health", 100,
        waterBase, 5, potion1Ings);

    vector<Ingredient> potion2Ings;
    potion2Ings.push_back(mushroom);
    potion2Ings.push_back(crystal);

    Potion p2("Magic", "Enhances magic", 200,
        magicBase, 3, potion2Ings);

    cout << "\nOriginal potions:" << endl;
    p1.printInfo();
    p2.printInfo();

    cout << "\nOPERATORS" << endl;
    Potion p3 = p1 + p2;
    cout << "Result p1 + p2:" << endl;
    p3.printInfo();

    Potion p4 = p1 * p2;
    cout << "Result p1 * p2:" << endl;
    p4.printInfo();

    cout << "\nCAULDRON" << endl;

    Cauldron cauldron(5, waterBase);
    cauldron.printInfo();

    cout << "\nAdding ingredients to cauldron:" << endl;
    cauldron.addIngredient(herb);
    cauldron.addIngredient(mushroom);
    cauldron.addIngredient(crystal);
    cauldron.printInfo();

    Potion p5 = cauldron.createPotion("Cauldron Potion",
        "Brewed in cauldron", 150);
    p5.printInfo();

    cout << "\nCauldron after creating potion:" << endl;
    cauldron.printInfo();

    cauldron.fillFromPotion(p2);
    cout << "\nCauldron after filling from potion p2:" << endl;
    cauldron.printInfo();

    cout << "POTION POWER" << endl;
    cout << "Power of p1 (Water x1.0):" << p1.calculatePower() << endl;
    cout << "Power of p2 (Magic x2.0): " << p2.calculatePower() << endl;

    cout << "   LABORATORY WORK EVALUATION" << endl;
    cout << "My evalution: 9" << endl;
    cout << "Interest: 9 out of 10" << endl;
    cout << "Completeness: 10 out of 10" << endl;
    cout << "Difficulty: 9 out of 10" << endl;

    return 0;
}
