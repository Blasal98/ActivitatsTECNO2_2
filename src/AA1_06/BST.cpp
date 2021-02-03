
#include "BST.h"


BST::BST()
{
	root = new Node(5);
	root->left = new Node(3);
	root->right = new Node(10);
	root->right->left = new Node(8);
	root->right->left->left = new Node(7);
	root->right->left->right = new Node(9);
	root->right->right = new Node(11);
}


BST::~BST()
{
}


int BST::Min()
{
	return 0;
}

int BST::Max()
{
	return 0;
}


BT::Node* BST::Search(int key) {

	return Search(root,key);

}BT::Node* BST::Search(Node* n,int key) {

	if (n->key == key) return n; //si es el input yasta
	if (key < n->key) {
		if (n->left != nullptr) return Search(n->left,key);
	}
	else if (key > n->key) {
		if (n->right != nullptr) return Search(n->right, key);
	}
	return nullptr; //si ni un ni laltre return nullptr
}

bool BST::Exist(int key)
{
	return (Search(key) != nullptr ?  true : false);
}

void BST::Insert(int key) {

	
}
void BST::GetKeysByOrder(std::vector<int>& v)
{
}
