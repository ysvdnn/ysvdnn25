#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include "Potion.hpp"
#include "Cauldron.hpp"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Base waterBase("Вода", "Обычная вода", 1.0);
    Base magicBase("Магическая основа", "Древняя магия", 2.0);

    Ingredient herb("Трава", "Лечебная трава", "Лечит");
    Ingredient mushroom("Гриб", "Светящийся гриб", "Ночное зрение");
    Ingredient crystal("Кристалл", "Магический кристалл", "Усиливает магию");

    cout << "\n--- ЧАСТЬ 1: ЗЕЛЬЯ ---" << endl;

    vector<Ingredient> potion1Ings;
    potion1Ings.push_back(herb);
    potion1Ings.push_back(mushroom);

    Potion p1("Лечебное", "Восстанавливает здоровье", 100,
        waterBase, 5, potion1Ings);

    vector<Ingredient> potion2Ings;
    potion2Ings.push_back(mushroom);
    potion2Ings.push_back(crystal);

    Potion p2("Магическое", "Усиливает магию", 200,
        magicBase, 3, potion2Ings);

    cout << "\nИсходные зелья:" << endl;
    p1.printInfo();
    p2.printInfo();

    cout << "\nОПЕРАТОРЫ" << endl;
    Potion p3 = p1 + p2;
    cout << "Результат p1 + p2:" << endl;
    p3.printInfo();

    Potion p4 = p1 * p2;
    cout << "Результат p1 * p2:" << endl;
    p4.printInfo();

    cout << "\nКОТЁЛ" << endl;

    Cauldron cauldron(5, waterBase);
    cauldron.printInfo();

    cout << "\nДобавление ингредиентов в котёл:" << endl;
    cauldron.addIngredient(herb);
    cauldron.addIngredient(mushroom);
    cauldron.addIngredient(crystal);
    cauldron.printInfo();

    Potion p5 = cauldron.createPotion("Зелье из котла",
        "Сварено в котле", 150);
    p5.printInfo();

    cout << "\nКотёл после создания зелья:" << endl;
    cauldron.printInfo();

    cauldron.fillFromPotion(p2);
    cout << "\nКотёл после заполнения из зелья p2:" << endl;
    cauldron.printInfo();

    cout << "РАСЧЁТ СИЛЫ ЗЕЛИЙ" << endl;
    cout << "Сила зелья p1 (вода x1.0): " << p1.calculatePower() << endl;
    cout << "Сила зелья p2 (магия x2.0): " << p2.calculatePower() << endl;

    cout << "   ОЦЕНКА ЛАБОРАТОРНОЙ РАБОТЫ" << endl;
    cout << "Моя оценка:" << endl;
    cout << "Интерес: 9 из 10" << endl;
    cout << "Наполненность: 10 из 10" << endl;
    cout << "Сложность: 8 из 10" << endl;

    return 0;
}
