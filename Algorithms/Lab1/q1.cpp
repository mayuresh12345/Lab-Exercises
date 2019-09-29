#include <iostream>
#include <stdlib.h>
using namespace std;

struct node
{
	int data;
	struct node *lchild, *rchild;
};

struct node* createTree(struct node* root, int data)
{
	if(!root)
	{
		root = (struct node*)malloc(sizeof(struct node));
		root -> data = data;
		root->lchild = NULL;
		root->rchild = NULL;
		return root;
	}

	if(root->data > data)
		root->lchild = createTree(root->lchild, data);
	else if(root->data < data)
		root->rchild = createTree(root->rchild, data);
	else
	{
		cout << "No duplicates allowed\n";
		exit(0);
	}
}
struct node* search(struct node* root, int ele)
{
	if(!root)
	{
		cout << "Element " << ele << " not found\nInserting into tree";
		root = createTree(root, ele);
		return root;
	}

	if(root->data == ele)
	{
		cout << "Found\n";
		return root;
	}
	else if(root->data > ele)
	{
		root->lchild = search(root->lchild, ele);
		return root;
	}
	else
	{
		root->rchild = search(root->rchild, ele);
		return root;
	}
}
void inorder(struct node* root)
{
	if(root)
	{
		inorder(root->lchild);
		cout << root->data << " ";
		inorder(root->rchild);
	}
}
int main()
{
	struct node* root = NULL;
	root = createTree(root, 2);
	root = createTree(root, 1);
	root = createTree(root, 3);

	cout << endl;
	inorder(root);
	cout << endl;
	
	root = search(root, 3);

	cout << endl;
	inorder(root);
	cout << endl;

	root = search(root, 4);


	cout << endl;
	inorder(root);
	cout << endl;
}