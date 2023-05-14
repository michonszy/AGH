//Szymon Michoń
#include <iostream>
using namespace std;

struct node
{
	int value;
	node* next;
	
};

void add_to_tail(node*& head, int valueToAdd)
{
	node* nodeToAdd = new node;
	nodeToAdd->value = valueToAdd; //tworzenie nowego węzła
	nodeToAdd->next = NULL;

	if (!head) //jeśli lista jest pusta
	{
		head = nodeToAdd;
		return;
	}

	node* pom = head;

	while (pom->next) //szukamy ostatniego elementu (następnik wskazuje na NULL)
	{
		pom = pom->next; //analog i++ w tablicach

	}

	pom->next = nodeToAdd; //dodajemy jako następnika ostatniego elementu

}

void print_list(node* head)
{
	node* pom = head;

	if (!head)
	{
		cout << "lista jest pusta" << endl;
		return;
	}

	while (pom->next)
	{
		cout << pom->value << " ";
		pom = pom->next;
	}
	cout << pom->value << " ";
}

void remove_parzyste(node*& H) {
	node* p = H;
	if (!(p->value % 2))
	{
		H = H->next;
		delete p;
		p = H;
	}
	while (p->next) {
		if (!(p->next->value % 2)) {
			node* tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
		else p = p->next;
	}
}

void dzielenie_co_trzeciego_przez_dwa(node*& H) {

	node* p = H;
	int pomoc = 0;
	while (p->next->next->next) {
		p = p->next->next;
		p->value = (p->value / 2);
		//node* tmp = p->next;
		//p->next = p->next->next;
		//delete tmp;
		if (p->next->next->next) {
			p = p->next;
		}
		else pomoc = 1;
	}
	if (!pomoc) {
		p->value = (p->value / 2);
	}
}

void usun_przedostatni(node*& H) {
	if (!H) //lista pusta, nic nie usuwamy
	{
		cout << "Lista jest pusta" << endl;
		return;
	}

	node* p = H;

	while (p->next->next->next) 
	{
		p = p->next; 
	}
	node* tmp = p->next;
	p->next = p->next->next;
	delete tmp;

}

void sum_of_poprzednicy(node*& H) {
	
	node* pom = H;

	if (!H)
	{
		cout << "lista jest pusta" << endl;
		return;
	}
	int wartosc = 0;

	while (pom->next)
	{
		wartosc = wartosc + pom->value;
		pom->value = wartosc;
		pom = pom->next;
	}
	wartosc = wartosc + pom->value;
	pom->value = wartosc;
	pom = pom->next;
}

int main()
{

	setlocale(LC_CTYPE, "Polish");

	node* head = new node();
	head->value = 1;
	add_to_tail(head, 4);
	add_to_tail(head, -8);
	add_to_tail(head, 0);
	add_to_tail(head, 3);
	add_to_tail(head, 2);
	add_to_tail(head, 7);
	add_to_tail(head, 11);
	cout << "Poczatkowa lista: ";
	print_list(head);
	cout<< endl;


	int user_choose;
	//MENU GŁÓWNE PROGRAMU
	cout << "Witaj w programie, wybierz opcję działania" << endl;
	cout << "[1] Usuwanie elementów o parzystych wartościach" << endl;
	cout << "[2] Dzielenie wartości co trzeciego elementu przez 2" << endl;
	cout << "[3] Usuwanie przedostatniego elementu" << endl;
	cout << "[4] Zamiana wartości każdego elementu listy na sumę jego poprzedników" << endl;
	cout << endl;
	cout << "Podaj wybór: ";
	cin >> user_choose;
	switch (user_choose) {
	case 1:
		remove_parzyste(head);
		print_list(head);
		break;
	case 2:
		dzielenie_co_trzeciego_przez_dwa(head);
		print_list(head);
		break;
	case 3:
		usun_przedostatni(head);
		print_list(head);
		break;
	case 4:
		sum_of_poprzednicy(head);
		print_list(head);
		break;
	default:
		cout << "ERROR" << endl;
	}
}

