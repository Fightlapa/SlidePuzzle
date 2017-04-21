#pragma once
#include <cstdlib>
struct node
{
	int** rows;
	node *parent;
	char color;
	node *left;
	node *right;
};
class RedBlackTree
{
public:
	int size;
	node *root;
	node *q;

	RedBlackTree(int size)
	{
		this->size = size;
		q = NULL;
		root = NULL;
	}
	~RedBlackTree()
	{
		if (root != NULL)
		{
			deleteNodes(root);
		}
	}
	void deleteNodes(node *q)
	{
		if (q->left != NULL)
		{
			deleteNodes(q->left);
		}
		if (q->right != NULL)
		{
			deleteNodes(q->right);
		}
		for (int i = 0; i < size; i++)
		{
			delete(q->rows[i]);
		}
		delete q->rows;
	}
	void insert(int**);
	void insertfix(node *);
	void leftrotate(node *);
	void rightrotate(node *);
	bool compare(int** rows, int** rows2);
	node* successor(node *);
	void disp();
	void display(node *);
	bool search(int** rows);
};