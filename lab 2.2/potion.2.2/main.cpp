#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include "Potion.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    vector<string> ing1;
    ing1.push_back("à");
    ing1.push_back("á");
    ing1.push_back("â");
    ing1.push_back("ã");

    vector<string> ing2;
    ing2.push_back("â");
    ing2.push_back("ã");
    ing2.push_back("ì");

    Potion p1("À", "à", 20, ing1);
    Potion p2("Â", "â", 10, ing2);

    p1.printInfo();
    p2.printInfo();

    cout << " \n ÒÅÑÒ + \n" << endl;
    Potion p3 = p1 + p2;
    p3.printInfo();

    cout << "\n ÒÅÑÒ += \n" << endl;
    Potion p4 = p1;
    cout << "Äî: " << p4.getName() << endl;
    p4 += p2;
    p4.printInfo();

    cout << "\n ÒÅÑÒ * \n" << endl;
    Potion p5 = p1 * p2;
    p5.printInfo();

    cout << "\n ÒÅÑÒ ÏÐÈÑÂÀÈÂÀÍÈß \n" << endl;
    Potion p6;
    p6 = p1;
    p6.printInfo();

    return 0;
}