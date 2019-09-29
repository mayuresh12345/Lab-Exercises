// Insertion, search, delete, display
#include <iostream>
#include <stdlib.h>
using namespace std;
int i = 0;
struct node
{
	int data;
	struct node* next;
};
void display(struct node* head)
{
	cout << endl;
	while(head != NULL)
	{
		cout << head->data << " ";
		head = head -> next;
	}
	cout << endl;
}
struct node* insert(struct node* head, int data)
{
	
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node -> data = data;
	new_node -> next = NULL;
	
	if(!head)
	{
		head = new_node;
		return head;
	}
	
	struct node* temp = head;

	while(temp->next != NULL)
		temp = temp -> next;

	temp->next = new_node;

	return head;
}

int main()
{
	struct node* head = NULL;
	
	head = insert(head, 1);
	head = insert(head, 2);
	head = insert(head, 3);
	head = insert(head, 4);
}