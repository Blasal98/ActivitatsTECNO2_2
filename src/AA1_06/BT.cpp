

#include "BT.h"


BT::BT() {
	root = new Node(2);
	root->left = new Node(7);
	root->right = new Node(5);
	root->left->right = new Node(6);
	root->left->right->left = new Node(1);
	root->left->right->right = new Node(11);
	root->right->right = new Node(9);
	root->right->right->left = new Node(4);
};

//Implementar (AA106)
BT::~BT() {
	deleteChildren(root);
}
void BT::deleteChildren(Node* n) {
	if (n->left != nullptr) deleteChildren(n->left);
	if (n->right != nullptr) deleteChildren(n->right);
	delete n;
}

#pragma region ORDERS
void BT::PreOrder()
{
	PreOrder(root);
	std::cout << std::endl;
}

void BT::PreOrder(Node* n)
{
	if (n == nullptr) return;
	std::cout << n->key << '-';  //raiz
	PreOrder(n->left);	  // se va al hijo izquierdo
	PreOrder(n->right);	  // se va al hijo derecho
}

void BT::InOrder()
{
	InOrder(root);
	std::cout << std::endl;
}

void BT::InOrder(Node* n)
{
	if (n == nullptr) return;
	InOrder(n->left);	  // se va al hijo izquierdo
	std::cout << n->key << '-';  //raiz
	InOrder(n->right);	  // se va al hijo derecho
}

void BT::PostOrder()
{
	PostOrder(root);
	std::cout << std::endl;
}

void BT::PostOrder(Node* n)
{
	if (n == nullptr) return;
	PostOrder(n->left);	  // se va al hijo izquierdo
	PostOrder(n->right);	  // se va al hijo derecho
	std::cout << n->key << '-';  //raiz
}

//Implementar uno de los siguientes: PreOrderI, InOrderI o PostOrderI
void BT::PreOrderI()
{
	Node* n = root;
	std::queue<Node*> q;
	q.push(n);
	while (!q.empty())
	{
		Node* tmp = q.front();
		q.pop();

		std::cout << tmp->key << '-';
		if (tmp->left != nullptr) q.push(tmp->left);
		if (tmp->right != nullptr) q.push(tmp->right);
	}
	std::cout << std::endl;
}

void BT::InOrderI()
{
}

void BT::PostOrderI()
{
}
#pragma endregion

#pragma region SEARCH/EXIST
//Implementar (AA106)
BT::Node* BT::Search(int key)
{
	return Search(root, key);
}
BT::Node* BT::Search(Node* n, int key)
{
	Node* tmp;
	if (n->key == key) return n; //si es el input yasta
	if (n->left != nullptr) {  //si te fill a left
		tmp = Search(n->left, key);
		if (tmp != nullptr) //si no era nullptr retornem
			return tmp;
	}
	if (n->right != nullptr) { //si te fill a right
		tmp = Search(n->right, key);
		if (tmp != nullptr) //si no era nullptr retornem
			return tmp;
	}
	return nullptr; //si ni ell ni fills son return nullptr
}

//Implementar (AA106)
bool BT::Exist(int key)
{
	if (Search(key) != nullptr) return true;
	return false;
}
#pragma endregion






//Devuelve en un vector los valores pares encontrados 
void BT::GetNPair(std::vector<int>& v) {
	return GetNPair(root, v);
};
void BT::GetNPair(Node* n, std::vector<int>& v) {
	if (n == nullptr) return;
	if (n->key % 2 == 0) { v.push_back(n->key); };
	GetNPair(n->left, v);
	GetNPair(n->right, v);
}
	

//Implementar (AA106)
int BT::Height()
{
	return Height(root);
}
int BT::Height(Node* n)
{
	if (n == nullptr) return 0;
	return 1 + std::max(Height(n->left), Height(n->right));
}

//Implementar (AA106)
bool BT::IsBalanced() {
	return IsBalanced(root);
}
bool BT::IsBalanced(Node* n) {
	if (n == nullptr) return true;
	if ((abs(Height(n->left) - Height(n->right)) <= 1) && IsBalanced(n->left) && IsBalanced(n->right)) return true;
	return false;
}

//Implementar (AA106)
int BT::Max()
{
	return 0;
}

//Implementar (AA106)
int BT::Min()
{
	return 0;
}

#pragma region NUMBER NODES
//Versión recursiva
int BT::GetNumberNodes() {
	return GetNumberNodes(root);
}
int BT::GetNumberNodes(Node* n) {
	if (n == nullptr) return 0;
	return GetNumberNodes(n->left) + GetNumberNodes(n->right) + 1;
}

//Versión iterativa
int BT::GetNumberNodesI() {
	Node* n = root;
	// Caso: tree vacio
	if (n == nullptr)	return 0;

	//Caso: tree no vacio
	std::queue<Node*> q;  //para guardar a los nodos que me quedan por visitar

	int count = 0; // contador de nodos
	q.push(n);
	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();

		count++;

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
	return count;
}

#pragma endregion









