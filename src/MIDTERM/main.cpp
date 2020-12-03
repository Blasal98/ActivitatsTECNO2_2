
#include <iostream>

int main() {

	int* a = new int [10]; //aixo ha de portar espai despres de int
	//std::cout << a[0] << a[1] << std::endl;
	int *b = a;

	delete a;

	return 0;
}