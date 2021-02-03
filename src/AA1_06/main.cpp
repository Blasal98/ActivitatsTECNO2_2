#include <iostream>
#include "BT.h"
#include "BST.h"

int main() {

	

	BT t1;
	//Destructor fet
	//Search + Exist fet               
	//std::cout << t1.Exist(1) << std::endl;

	t1.PreOrder();
	t1.InOrder();
	t1.PostOrder();


	//std::cout << t1.GetNumberNodes() << std::endl;
	//std::cout << t1.GetNumberNodesI() << std::endl;

	/*std::vector<int> pairVec;
	t1.GetNPair(pairVec);
	std::cout << pairVec.size() << std::endl;*/

	t1.PreOrderI();

	std::cout << t1.Height() << std::endl;
	std::cout << t1.IsBalanced() << std::endl;

	BST bst1;

	//std::cout << bst1.Exist(1);
	
	


	
	return 0;

};
