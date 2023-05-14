//Szymon michon algo2
//PROGRAM JEST NIEDZIAŁAJĄCY :(
#include <iostream>
using namespace std;

struct node
{
	int value;
	node* next;
	node* prev;
};

void add_before_head(node*& head, int valueToAdd)
{
	node* nodeToAdd = new node;
	nodeToAdd->value = valueToAdd; //tworzenie nowego węzła

	nodeToAdd->next = head; //dopinamy wskaźnik nowego na starą głowę
	head = nodeToAdd; //głowę przepinamy na nowy węzeł
}

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
void find_parzysta2(node*& head) {

	if (!head)
	{
		cout << "Lista jest pusta więc i wartości parzystych nie ma" << endl;
	}

	node* pom = head;

	while (pom->next)
	{
		if (pom->value % 2 == 0) {
			cout << "Znaleziono parzyste " << pom->value << endl;
			pom = pom->next;
		}
		else {
			pom = pom->next;
		}
	}
}

void remove_first(node*& head)
{
	if (!head)
	{
		cout << "Lista jest pusta" << endl;
		return;
	}

	node* pom = head;
	head = head->next;
	delete pom;
}
void remove_pos(node*& head, int pos)
{
	if (!head) //lista pusta, nic nie usuwamy
	{
		cout << "Lista jest pusta" << endl;
		return;
	}

	if (pos == 0)
	{
		remove_first(head);
	}

	int i = 0; //zliczamy ilość elementów aż trafimy na pos

	node* pom = head;

	while (i < pos - 1 && pom->next->next) //szukamy elementu, który jest położony przed tym, który chemy usunąć
	{
		pom = pom->next;
		i++;
	}
	//usuwamy pom->next
	node* pom2 = pom->next; //zapisujemy element który chemy usunąć
	pom->next = pom2->next; //pom->next ma teraz wskazywać na to co jestpo usuwanym  elemencie
	delete pom2;
}

void remove_parzyste(node*& head) {

	if (!head)
	{
		cout << "Lista jest pusta więc i wartości parzystych nie ma" << endl;
	}

	node* pom = head;
	int wskaznik = 0;
	while (pom->next)
	{
		if (pom->value % 2 == 0) {
			cout << "Znaleziono parzyste " << pom->value << endl;
			
			cout << "Usuwam ją" << endl;
			 //zapisujemy element który chemy usunąć
			pom->prev = pom->next->next;
			delete pom;//pom->next ma teraz wskazywać na to co jestpo usuwanym  elemencie
			
			
		}
		else {
			pom = pom->next;
		}
		wskaznik = wskaznik + 1;
	}
}

void dzielenie_co_trzeciego_przez_dwa(node*& head) {
	node* pom = head;
	int pomocna = 1;
	while (pom->next) {
		if (pomocna % 3 == 0) {
			pom->value = pom->value / 2;
			pom = pom->next;
		}
		else {
			pom = pom->next;
		}
		pomocna++;
	}
	if (pomocna % 3 == 0) {
		pom->value = pom->value / 2;
		pom = pom->next;
	}
	else {
		pom = pom->next;
	}
}

void usun_przedostatni(node*& head) {
	if (!head) //lista pusta, nic nie usuwamy
	{
		cout << "Lista jest pusta" << endl;
		return;
	}


	node* pom = head;

	while (pom->next->next) //szukamy przedostatniego elementu (następnik wskazuje na NULL)
	{
		pom = pom->next; //analog i++ w tablicach
	}

	delete pom; //usuwamy ostatni (nastepnika przedostatniego)
	pom = NULL; //ręcznie ustawiamy wskaźnik na NULL
}
int find_size(node*& head) {
	node* pom = head;
	int licznik = 0;
	if (!head)
	{
		cout << "lista jest pusta, nie ma nic do policzenia" << endl;
		return licznik;
	}

	while (pom->next)
	{
		licznik++;
		pom = pom->next;
	}
	cout << "Lista ma " << licznik << " elementów" << endl;
	return licznik;
}
int main()
{
	setlocale(LC_CTYPE, "Polish"); //dodanie polskich znaków do konsoli
	node* head = new node();
	head->value = 1;
	//dodawanie po kolei elementów do listy (dopięcie do końca)
	add_to_tail(head, 4);
	add_to_tail(head, -8);
	add_to_tail(head, 0);
	add_to_tail(head, 3);
	add_to_tail(head, 2);
	add_to_tail(head, 7);
	add_to_tail(head, 11);

	//wyświetlenie listy
	cout << "Lista początkowa: ";
	print_list(head);
	cout << endl;
	cout << endl;

	////wielkośc listy
	//int lista_size = find_size(head);

	////test działania znajdowania parzystych
	find_parzysta2(head);
	remove_parzyste(head);
	cout << "Lista po usunięciu parzystych ";
	print_list(head);
	cout << endl;


	//sprawdzenie dzielenia
	//dzielenie_co_trzeciego_przez_dwa(head);
	//cout << "Lista po podzieleniu co 3 przez dwa" << endl;
	//print_list(head);
	//cout << endl;
	//for (int i=0; i <= lista_size; i++) {
	//	cout << "wchodzrm" << endl;
	//	find_parzysta(head, head->value);
	//}



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
		break;
	case 2:
		dzielenie_co_trzeciego_przez_dwa(head);
		break;
	case 3:
		usun_przedostatni(head);
		break;
	case 4:
		cout << "Opcja w trakcie pisania" << endl;
		break;
	default:
		cout << "Nie ma takiej możliwości" << endl;
	}




}
