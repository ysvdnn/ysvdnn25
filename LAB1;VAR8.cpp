#include <iostream>
#include <cmath>
int main()
{
	int x;
	std::cin >> x;
	int k = 32;
	int maxk = pow(2, 31) - 1;
	int mink = pow(2, 31) * (-1);
	std::cout << "The opposite number for " << x <<": " << (-1) * x << std::endl;
	std::cout << "The value of the root of the second degree for " << x << ": " << sqrt(x) << std::endl;
	std::cout << "The value of the root of the fifth degree for " << x << ": " << pow(x,0.2) << std::endl;
	std::cout << "int, occupies " << k << "bit(a), min. value = " << mink << ", max. value = " << maxk << std::endl;

}