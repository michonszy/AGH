#include <iostream>
using namespace std;

struct nodeBST
{
	nodeBST* left;
	nodeBST* right;
	nodeBST* parent;
	int value;
};

void insertBST(nodeBST*& root, int valueToAdd)
{
	nodeBST* nodeToAdd = new nodeBST;
	nodeToAdd->value = valueToAdd;
	nodeToAdd->parent = NULL;
	nodeToAdd->left = NULL;
	nodeToAdd->right = NULL;

	nodeBST* pom;
	if (!root) //puste drzewo
	{
		root = nodeToAdd;
	}
	else
	{
		pom = root;
		while (1)
		{
			if (nodeToAdd->value < pom->value) //porownojuemy klucze, jesli jest mnieszy
				if (!pom->left) //jeśli nie ma lewego syna to wstawiamy, przerywamy while
				{
					pom->left = nodeToAdd;
					break;
				}
				else
					pom = pom->left; //jeśli jest - idziemy na lewo

			else //jesli klucz jest większy lub równy
			{
				if (!pom->right) //jeśli nie ma prawego syna to wstawiamy, przerywamy while
				{
					pom->right = nodeToAdd;
					break;
				}
				else
					pom = pom->right; //jeśli jest - idziemy na prawo
			}
		}
		nodeToAdd->parent = pom;
	}
}


void inorder(nodeBST* root) //lewe poddrzewo, węzeł, prawe poddrzewo
{
	if (root)
	{
		inorder(root->left);
		cout << root->value << " ";
		inorder(root->right);
	}
}


int main()
{
	nodeBST* node1 = NULL;
	nodeBST* node2 = NULL;

	//insertBST(node1, 4);
	//insertBST(node1, 1);
	//insertBST(node1, 3);
	//insertBST(node1, 5);
	//insertBST(node1, 6);

	//insertBST(node2, 4);
	//insertBST(node2, 0);
	//insertBST(node2, 8);
	//insertBST(node2, 4);
	//insertBST(node2, 7);

	
	int liczba_galezi;
	cin >> liczba_galezi;
	for (int i = 0; i < liczba_galezi; i++) {
		
		int wartoscpodana;
		cin >> wartoscpodana;
		insertBST(node1, wartoscpodana);
	}

	int liczba_galezi2;
	cin >> liczba_galezi2;
	for (int i = 0; i < liczba_galezi2; i++) {

		int wartoscpodana2;
		cin >> wartoscpodana2;
		insertBST(node1, wartoscpodana2);
	}

	inorder(node1);;
	
	cout << endl;

}