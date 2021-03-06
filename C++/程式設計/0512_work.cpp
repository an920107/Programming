#include <bits/stdc++.h>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node{
	int data;
	struct node *next;
};
typedef struct node Node;

void createQ();
void addQ(int);
void deleteQ();
void printList();

Node *Front, *Rear;

int main(int argc, char** argv) {
	
	createQ();
	addQ(5);
	addQ(6);
	addQ(7);
	printList();
	deleteQ();
	printList();

    system("pause");
	return 0;
}

void createQ() {
	Front = new Node;
    Rear = new Node;
	Rear->next = Front;
    Front->next = NULL;
}

void addQ(int item) {
	Node *newnode = new Node;
	newnode->data = item;
    newnode->next = NULL;
    Rear->next->next = newnode;
    Rear->next = newnode;
}

void deleteQ() {
	Node *temp = Front->next;
    if (temp == NULL) return;
    if (temp->next == NULL) Rear->next = Front;
    Front->next = temp->next;
    delete temp;
}

void printList() {
	Node *temp;
	temp = Front->next;
	while (temp != NULL){
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}