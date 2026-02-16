#include <iostream>
#include <string>
#include <clocale>
using namespace std;

class Potion {
private:
    string name;
    string description;
    int price;
    string base;
    int volume;

    void validatePrice(int newPrice) {
        if (newPrice < 0) {
            price = 0;
        }
        else {
            price = newPrice;
        }
    }

    void validateVolume(int newVolume) {
        if (newVolume < 0) {
            volume = 0;
        }
        else {
            volume = newVolume;
        }
    }

public:
    Potion() {
        name = "Unknown";
        description = "Unknown";
        price = 0;
        base = "Unknown";
        volume = 0;
    }

    Potion(string n, string d, int p, string b, int v) {
        name = n;
        description = d;
        base = b;
        validatePrice(p);
        validateVolume(v);
    }

    Potion(const Potion& other) {
        name = other.name;
        description = other.description;
        price = other.price;
        base = other.base;
        volume = other.volume;
    }

    ~Potion() {
        cout << "Деструктор: " << name << endl;
    }


    string getName() const {
        return name;
    }

    string getDescription() const {
        return description;
    }

    int getPrice() const {
        return price;
    }

    string getBase() const {
        return base;
    }

    int getVolume() const {
        return volume;
    }


    void setPrice(int newPrice) {
        if (newPrice < 0) {
            return;
        }
        price = newPrice;
        cout << "Новая цена " << name << ": " << price << " золотых" << endl;
    }

    void changeBase(string newBase) {
        if (newBase.empty()) {
            cout << "Ошибка: основа не может быть пустой!" << endl;
            return;
        }
        base = newBase;
        cout << "Основа " << name << "изменена на:" << base << endl;
    }

    void changeBase() {
        base = "Вода";
        cout << "Основа " << name << " сброшена на Воду" << endl;
    }

    void drink() {
        if (volume <= 0) {
            cout << "В зелье " << name << "нет порций!" << endl;
            return;
        }
        volume--;
        cout << "Осталось порций " << name << ": " << volume << endl;
    }

    void printInfo() const {
        cout << "Название: " << name << endl;
        cout << "Описание: " << description << endl;
        cout << "Цена: " << price << " золотых" << endl;
        cout << "Основа: " << base << endl;
        cout << "Порций: " << volume << endl;
        cout << "--------\n" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Potion p1;  
    Potion p2("Кошачье зрение", "Видеть в темноте", 200, "Лунный свет", 5);  
    Potion p3 = p2;  

    p2.setPrice(250);           
    p2.changeBase("Грибы");      
    p2.changeBase();             

    p2.drink();  
    p2.drink();  
    p2.drink();   
    p2.drink();  
    p2.drink();  
    p2.drink();  

    p2.printInfo(); 

    return 0;
}