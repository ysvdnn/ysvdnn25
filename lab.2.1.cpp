#include <iostream>
#include <string>
using namespace std;


class Potion {
private:
    string name;
    string desc;
    int price;
    string base;
    int volume;

public:
    Potion() : name("Unknown"), desc("Unknown"), price(0), base("Unknown"), volume(0) {}

    Potion(string n, string d, int p, string b, int v) : name(n), desc(d), price(p), base(b), volume(v) {}

    Potion(const Potion& other) : name(other.name), desc(other.desc), price(other.price), base(other.base), volume(other.volume) {}

    ~Potion() {
        cout << "dtor" << endl;
    }

    //Геттеры
    string getName() const {
        return name;
    }
    string getDesc() const {
        return desc;
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

    //Сеттеры
    void setPrice(int newPrice) {
        price = newPrice;
        cout << "New price: " << price << endl;
    }

    void changeBase(string newBase) {
        base = newBase;
        cout << "New base: " << base << endl;
    }

    void drink() {
        if (volume >= 1) {
            volume--;
            cout << "Portions left: " << volume << endl;
        }
        else {
            cout << "No portions left, you cant drink anymore" << endl;
        }
    }

    void info() {
        cout << "----------------------------" << endl;
        cout << "Information" << endl;
        cout << "Name: " << name << endl;
        cout << "Description: " << desc << endl;
        cout << "Price: " << price << endl;
        cout << "Base: " << base << endl;
        cout << "Portions left: " << volume << endl;
        cout << "----------------------------" << endl;
    }
};

int main() {
    Potion p1;
    p1.info();

    Potion p2("Cat", "Allows you to see in the dark", 200, "Moonshine", 3);
    p2.info();

    Potion p3 = p2;
    p3.info();

    p1.setPrice(250);
    p2.changeBase("Mushrooms");
    p3.drink();
    p3.drink();
    p3.drink();
    p3.drink();

    p1.info();
    p2.info();
    p3.info();
}
