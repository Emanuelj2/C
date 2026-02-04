#include <stdio.h>
#include <stdlib.h>

//node struct
typedef struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
}Node;


//initialize the node
Node* InitNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Node* AddNode(Node* root, int data)
{

	Node* newNode = InitNode(data);

	if(root == NULL)
	{
		return newNode;
	}

	if(data < root->data)
	{
		root->left = AddNode(root->left, data);
	}
	else
	{
		root->right = AddNode(root->right, data);
	}

	return root;
}

//search for the node
Node* Search(Node* root, int data)
{
	if(root == NULL ) return root;

	while(root !=  NULL)
	{
		if(root->data == data)
		{
			printf("node %d found", data);
			return root;
		}
		else if(root->data > data)
		{
			root =  root->left;
		}

		else
		{
			root = root->right;
		}
	}
	printf("node %d not fountd", data);
	return NULL; //nothing is returned
}


void PrintInOrder(Node* root)
{
	if(root == NULL)
	{
		return;
	}
	PrintInOrder(root->left);
	printf("%d, ", root->data);
	PrintInOrder(root->right);
}


int main(int argc, char **argv)
{
	printf("Binary tree\n");

	Node* root = NULL;

	root = AddNode(root, 10);
	AddNode(root, 20);
	AddNode(root, 5);

	printf("InOrder: ");
	PrintInOrder(root);
	printf("\n");

	Search(root, 20);
	printf("\n");
	Search(root, 50);
	printf("\n");
}

