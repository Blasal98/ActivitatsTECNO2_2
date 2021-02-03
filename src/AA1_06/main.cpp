#include <iostream>
#include "BT.h"

int main() {

	

	BT t1;
	//Destructor fet
	//Search + Exist fet               
	//std::cout << t1.Exist(1) << std::endl;


	t1.PreOrder();
	t1.PostOrder();
	t1.InOrder();

	/*int x = t1.GetNumberNodesI();

	std::vector<int> v;

	t1.GetNPair(v);*/
	
	return 0;

};
