#include "Potion.hpp"
#include <cstdlib>
#include <ctime>

Ingredient::Ingredient() {
    name = "Unknown";
    description = "Unknown";
    effect = "None";
}

Ingredient::Ingredient(string n, string d, string e) {
    name = n;
    description = d;
    effect = e;
}

void Ingredient::printInfo() const {
    cout << "  Ingredient: " << name << endl;
    cout << "  Description: " << description << endl;
    cout << "  Effect: " << effect << endl;
}

Base::Base() {
    name = "Unknown";
    description = "Unknown";
    multiplier = 1.0;
}

Base::Base(string n, string d, float m) {
    name = n;
    description = d;
    if (m > 0) {
        multiplier = m;
    }
    else {
        multiplier = 1.0;
    }
}

void Base::printInfo() const {
    cout << "  Base: " << name << " (x" << multiplier << ")" << endl;
    cout << "  Description: " << description << endl;
}

void Potion::validatePrice(int newPrice) {
    if (newPrice < 0) {
        price = 0;
    }
    else {
        price = newPrice;
    }
}

void Potion::validateVolume(int newVolume) {
    if (newVolume < 0) {
        volume = 0;
    }
    else {
        volume = newVolume;
    }
}

Potion::Potion() {
    name = "Unknown";
    description = "Unknown";
    price = 0;
    base = Base();
    volume = 0;
}

Potion::Potion(string n, string d, int p, Base b, int v, vector<Ingredient> ing) {
    name = n;
    description = d;
    validatePrice(p);
    base = b;
    validateVolume(v);
    ingredients = ing;
}

Potion::Potion(const Potion& other) {
    name = other.name;
    description = other.description;
    price = other.price;
    base = other.base;
    volume = other.volume;
    ingredients = other.ingredients;
}

Potion::~Potion() {
    if (!ingredients.empty()) {
        ingredients.clear();
    }
}

Potion& Potion::operator=(const Potion& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        price = other.price;
        base = other.base;
        volume = other.volume;
        ingredients = other.ingredients;
    }
    return *this;
}

string Potion::getName() const {
    return name;
}

string Potion::getDescription() const {
    return description;
}

int Potion::getPrice() const {
    return price;
}

Base Potion::getBase() const {
    return base;
}

int Potion::getVolume() const {
    return volume;
}

vector<Ingredient> Potion::getIngredients() const {
    return ingredients;
}

void Potion::setName(string n) {
    if (n.empty()) {
        return;
    }
    name = n;
}

void Potion::setDescription(string d) {
    if (d.empty()) {
        return;
    }
    description = d;
}

void Potion::setPrice(int p) {
    if (p < 0) {
        return;
    }
    validatePrice(p);
}

void Potion::setBase(Base b) {
    base = b;
}

void Potion::setVolume(int v) {
    if (v < 0) {
        return;
    }
    validateVolume(v);
}

void Potion::setIngredients(vector<Ingredient> ing) {
    ingredients = ing;
}

void Potion::addIngredient(Ingredient ing) {
    ingredients.push_back(ing);
}

void Potion::changeBase(Base newBase) {
    base = newBase;
}

void Potion::changeBase() {
    base = Base("Water", "Regular water", 1.0);
}

void Potion::drink() {
    if (volume <= 0) {
        return;
    }
    volume--;
}

float Potion::calculatePower() const {
    float totalPower = 0;
    for (int i = 0; i < ingredients.size(); i++) {
        totalPower = totalPower + ingredients[i].name.length();
    }
    return totalPower * base.multiplier;
}

Potion Potion::operator+(const Potion& other) const {
    Base newBase;
    if (volume >= other.volume) {
        newBase = base;
    }
    else {
        newBase = other.base;
    }

    int newVolume = volume + other.volume;
    int newPrice = price + other.price;

    vector<Ingredient> newIngredients = ingredients;

    for (int i = 0; i < other.ingredients.size(); i++) {
        Ingredient ing = other.ingredients[i];
        bool found = false;

        for (int j = 0; j < newIngredients.size(); j++) {
            if (newIngredients[j].name == ing.name) {
                found = true;
                break;
            }
        }

        if (found) {
            Ingredient äîïIng = ing;
            äîïIng.name = ing.name + " extra";
            newIngredients.push_back(äîïIng);
        }
        else {
            newIngredients.push_back(ing);
        }
    }

    return Potion("Result +", "Mixture of potions", newPrice,
        newBase, newVolume, newIngredients);
}

Potion& Potion::operator+=(const Potion& other) {
    name = name + "extra";

    if (other.volume > volume) {
        base = other.base;
    }

    price = price + other.price;
    volume = volume + other.volume;

    for (int i = 0; i < other.ingredients.size(); i++) {
        Ingredient ing = other.ingredients[i];
        bool found = false;

        for (int j = 0; j < ingredients.size(); j++) {
            if (ingredients[j].name == ing.name) {
                found = true;
                break;
            }
        }

        if (found) {
            Ingredient äîïIng = ing;
            äîïIng.name = ing.name + " äîï";
            ingredients.push_back(äîïIng);
        }
        else {
            ingredients.push_back(ing);
        }
    }

    return *this;
}

Potion Potion::operator*(const Potion& other) const {
    srand(time(NULL));

    Base bases[4] = {
        Base("Water", "Pure water", 1.0),
        Base("Alcohol", "Strong alcohol", 1.5),
        Base("Oil", "Magical oil", 2.0),
        Base("Earth", "Ancient earth", 1.2)
    };

    int randomIndex = rand() % 4;
    Base newBase = bases[randomIndex];

    int sumVolume = volume + other.volume;
    int newVolume = sumVolume * 80 / 100;

    int sumPrice = price + other.price;
    int newPrice = sumPrice * 80 / 100;

    vector<Ingredient> allCommon;

    for (int i = 0; i < ingredients.size(); i++) {
        for (int j = 0; j < other.ingredients.size(); j++) {
            if (ingredients[i].name == other.ingredients[j].name) {
                allCommon.push_back(ingredients[i]);
                break;
            }
        }
    }

    vector<Ingredient> commonIngredients;

    for (int i = 0; i < allCommon.size(); i++) {
        bool alreadyAdded = false;

        for (int j = 0; j < commonIngredients.size(); j++) {
            if (allCommon[i].name == commonIngredients[j].name) {
                alreadyAdded = true;
                break;
            }
        }

        if (!alreadyAdded) {
            commonIngredients.push_back(allCommon[i]);
        }
    }

    Ingredient tail("tail", "Lizard tail", "Adds durability");
    Ingredient water("water", "Pure water", "Dilutes");
    commonIngredients.push_back(tail);
    commonIngredients.push_back(water);

    return Potion("Mix", "Mysterious potion", newPrice,
        newBase, newVolume, commonIngredients);
}

void Potion::printInfo() const {
    cout << "\n-POTION: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Price: " << price << endl;
    cout << "Volume: " << volume << endl;
    base.printInfo();
    cout << "Power: " << calculatePower() << endl;
    cout << "Ingredients:" << endl;

    if (ingredients.empty()) {
        cout << "none" << endl;
    }
    else {
        for (int i = 0; i < ingredients.size(); i++) {
            cout << "  " << (i + 1) << ". " << ingredients[i].name << endl;
        }
    }
}