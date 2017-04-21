#include "stdafx.h"
#include "RedBlackTree.h"
#include <iostream>
using namespace std;
bool RedBlackTree::compare(int** rows, int** rows2)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (rows[i][j]<rows2[i][j])
			{
				return true;
			}
			else{ return false; }
		}
	}
}
void RedBlackTree::insert(int** rows)
{
	int z, i = 0;
	node *p, *q;
	node *t = new node;
	t->rows = rows;
	t->left = NULL;
	t->right = NULL;
	t->color = 'r';
	p = root;
	q = NULL;
	if (root == NULL)
	{
		root = t;
		t->parent = NULL;
	}
	else
	{
		while (p != NULL)
		{
			q = p;
			if (compare(p->rows, t->rows))
				p = p->right;
			else
				p = p->left;
		}
		t->parent = q;
		if (compare(q->rows, t->rows))
			q->right = t;
		else
			q->left = t;
	}
	insertfix(t);
}
void RedBlackTree::insertfix(node *z)
{
	if (z->parent != NULL && z->parent->parent != NULL)
	{
		while (z != NULL && z->parent != NULL &&
			z->parent->parent != NULL && !z->parent->color == 'b')
			// ass long as color is not black, thus red
		{
			if (z->parent == z->parent->parent->left)
			{
				node *y = z->parent->parent->right;
				if (y != NULL && y->color == 'r')
				{
					z->parent->color = 'b';
					y->color = 'b';
					z->parent->parent->color = 'r';
					z = z->parent->parent;
				}
				else if (z == z->parent->right)
				{
					z = z->parent;
					leftrotate(z);
				}
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rightrotate(z->parent->parent);

			}
			else
			{

				node *y = z->parent->parent->left; // left instead of right
				if (y != NULL && y->color == 'r') // is red?
				{
					z->parent->color = 'b'; // color = black
					y->color = 'b'; // color = black
					z->parent->parent->color = 'r'; // color = red
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left) // left instead of right
					{
						z = z->parent;
						rightrotate(z);
					}
					z->parent->color = 'b'; // color is black
					z->parent->parent->color = 'r'; // color is red
					leftrotate(z->parent->parent);
				}
			}
		}
	}
}


void RedBlackTree::leftrotate(node *p)
{
	if (p->right == NULL)
		return;
	else
	{
		node *y = p->right;
		if (y->left != NULL)
		{
			p->right = y->left;
			y->left->parent = p;
		}
		else
			p->right = NULL;
		if (p->parent != NULL)
			y->parent = p->parent;
		if (p->parent == NULL)
			root = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->left = p;
		p->parent = y;
	}
}
void RedBlackTree::rightrotate(node *p)
{
	if (p->left == NULL)
		return;
	else
	{
		node *y = p->left;
		if (y->right != NULL)
		{
			p->left = y->right;
			y->right->parent = p;
		}
		else
			p->left = NULL;
		if (p->parent != NULL)
			y->parent = p->parent;
		if (p->parent == NULL)
			root = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->right = p;
		p->parent = y;
	}
}

node* RedBlackTree::successor(node *p)
{
	node *y = NULL;
	if (p->left != NULL)
	{
		y = p->left;
		while (y->right != NULL)
			y = y->right;
	}
	else
	{
		y = p->right;
		while (y->left != NULL)
			y = y->left;
	}
	return y;
}

void RedBlackTree::disp()
{
	display(root);
}
void RedBlackTree::display(node *p)
{
	if (root == NULL)
	{
		cout << "\nEmpty Tree.";
		return;
	}
	if (p != NULL)
	{
		cout << "\n\t NODE: ";
		cout << "\n Key: ";
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << p->rows[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << "\n Colour: ";
		if (p->color == 'b')
			cout << "Black";
		else
			cout << "Red";
		if (p->parent != NULL)
		{
			cout << "\n Parent: ";
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cout << p->parent->rows[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		else
			cout << "\n There is no parent of the node.  ";
		if (p->right != NULL)
		{
			cout << "\n Right Child: ";
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cout << p->right->rows[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		else
			cout << "\n There is no right child of the node.  ";
		if (p->left != NULL)
		{
			cout << "\n Left Child: ";
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cout << p->left->rows[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		else
			cout << "\n There is no left child of the node.  ";
		cout << endl;
		if (p->left)
		{
			cout << "\n\nLeft:\n";
			display(p->left);
		}
		/*else
		cout<<"\nNo Left Child.\n";*/
		if (p->right)
		{
			cout << "\n\nRight:\n";
			display(p->right);
		}
		/*else
		cout<<"\nNo Right Child.\n"*/
	}
}
bool RedBlackTree::search(int** rows)
{
	if (root == NULL)
	{
		return false;
	}
	node *p = root;
	bool tempCheck = 0;
	while (p != NULL&& tempCheck == 0)
	{
		tempCheck = true;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (!(p->rows[i][j] == rows[i][j]))
				{
					tempCheck = false;
					break;
				}
			}
			if (tempCheck == false)
				break;
		}
		if (tempCheck == 0)
		{
			if (compare(p->rows, rows))
				p = p->right;
			else
				p = p->left;
		}
	}
	return tempCheck;
}