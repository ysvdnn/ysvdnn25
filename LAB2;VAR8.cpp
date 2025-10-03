#include <iostream>
#include <cmath>
#include <bitset>

int main() {
	//1
	short A;
	int i;
	std::cin >> A >> i;
	if (i >= 0 && i < 8) {
		bool bit = (A >> i) & 1;
		if (bit != 0) {
			short NA = A * 5;
			std::cout << A << "*5 =" << NA << "=" << std::bitset<8>(NA) << std::endl;
		}
		else {
			short INV = ~A;
			std::cout << "~" << A << "=" << INV << "=" << std::bitset<8>(INV) << std::endl;
		}
	} 
	//2
	int cheat;
	std::cin >> cheat;

	switch (cheat) {
		case 787898: std::cout << "Endless Health" << std::endl; break;
		case 7878991: std::cout << "Moving to the previous level" << std::endl; break;
		case 7878993: std::cout << "Moving to the next level" << std::endl; break;
		case 7878995: std::cout << "Completing the current level with the maximum score" << std::endl; break;
		case 7878997: std::cout << "Changing the gravity of the ball (will make it fly up, like an anti-gravity spike)" << std::endl; break;
		default: std::cout << "The code was not found" << std::endl; break;
	}
	return 0;

}