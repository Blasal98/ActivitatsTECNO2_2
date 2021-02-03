#include <iostream>
#include "BT.h"

int main() {

	

	BT t1;
	std::cout << t1.Exist(1) << std::endl;
	std::cout << t1.Exist(2) << std::endl;
	std::cout << t1.Exist(3) << std::endl;
	std::cout << t1.Exist(4) << std::endl;
	std::cout << t1.Exist(5) << std::endl;
	std::cout << t1.Exist(6) << std::endl;
	std::cout << t1.Exist(7) << std::endl;
	std::cout << t1.Exist(8) << std::endl;
	std::cout << t1.Exist(9) << std::endl;

	/*t1.PreOrder();

	int x = t1.GetNumberNodesI();

	std::vector<int> v;

	t1.GetNPair(v);*/
	
	return 0;

};
