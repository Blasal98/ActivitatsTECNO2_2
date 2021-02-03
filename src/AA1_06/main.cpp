#include <iostream>
#include "BT.h"
#include "BST.h"

int main() {

	

	BT t1;
	//Destructor fet
	//Search + Exist fet               
	//std::cout << t1.Exist(1) << std::endl;

	/*t1.PreOrder();
	t1.PostOrder();
	t1.InOrder();
*/
	BST bst1;

	std::cout << bst1.Exist(1);
	std::cout << bst1.Exist(2);
	std::cout << bst1.Exist(3);
	std::cout << bst1.Exist(4);
	std::cout << bst1.Exist(5);
	std::cout << bst1.Exist(6);
	std::cout << bst1.Exist(7);
	std::cout << bst1.Exist(8);
	std::cout << bst1.Exist(9);
	std::cout << bst1.Exist(10);
	std::cout << bst1.Exist(11);
	std::cout << bst1.Exist(12);
	

	/*int x = t1.GetNumberNodesI();

	std::vector<int> v;

	t1.GetNPair(v);*/
	
	return 0;

};
