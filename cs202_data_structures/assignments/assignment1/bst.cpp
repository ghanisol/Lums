#ifndef __BST_CPP
#define __BST_CPP
#include <iostream>
#include "bst.h"
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;
template <class T>
bst<T>::bst()
{
	root = NULL;
}

template <class T>
void bst<T>::insert(string val,T key1)
{
	bst_node<T> *temp = new bst_node<T>(val, key1);
	
	if (root == NULL)
	{
		root = temp;
	}
	else
	{
		insert_recursive(temp, root);	
	}
	
}

template <class T>
bst_node<T>* bst<T>::search(T key1)
{	
	bst_node<T> *ptr = root;
	
	while (ptr != NULL)
	{
		if (key1 > ptr->key)
		{
			ptr = ptr->right;
		}
		else if (key1 < ptr->key)
		{
			ptr = ptr->left;
		}
		else
		{
			return ptr;
		}
	}
	return NULL;
}

template <class T>
void bst<T>::delete_node(T key1)
{
	bst_node<T> *node = search(key1);
	
	if (node == NULL)
	{
		return;
	}
	
	// Case 1 : node has no subtree
	if (isExternal(node))
	{
		if (node == root)		// node is the root
		{
			root = NULL;
			delete node;
		}
		else if (node->key < node->parent->key)		// node is the left child
		{
			node->parent->left = NULL;
			delete node;
		}
		else if (node->key > node->parent->key)		// node is the right child	
		{
			node->parent->right = NULL;
			delete node;
		}
	}
	// Case 2 : node has one subtree
	else if (!node->left || !node->right)
	{
		if (node->left)		// node has a left subtree
		{
			if (node == root)	// node is the root
			{
				root = node->left;
				node->left->parent = NULL;
				delete node;
			}
			else if (node->key < node->parent->key)		// node is the left child
			{
				node->parent->left = node->left;
				node->left->parent = node->parent;
				delete node;
			}
			else if (node->key > node->parent->key)		// node is the right child	
			{
				node->parent->right = node->left;
				node->left->parent = node->parent;				
				delete node;
			}
		}
		else if (node->right)	// node has a right subtree
		{
			if (node == root)	// node is the root
			{
				root = node->right;
				node->right->parent = NULL;
				delete node;
			}
			else if (node->key < node->parent->key)		// node is the left child
			{
				node->parent->left = node->right;
				node->right->parent = node->parent;
				delete node;
			}
			else if (node->key > node->parent->key)		// node is the right child	
			{
				node->parent->right = node->right;
				node->right->parent = node->parent;
				delete node;
			}
		}
	}
	// Case 3 : node has 2 subtrees
	else if (node->right && node->left)
	{
		if (node == root)	// node is the root
		{
			root = node->right;
			node->right->parent = NULL;
			
			bst_node<T> *ptr = node->right;
			while (ptr->left != NULL)
			{
				ptr = ptr->left;
			}
			
			node->left->parent = ptr;
			ptr->left = node->left;
			delete node;
		}
		else if (node->key < node->parent->key)		// node is the left child
		{
			node->parent->left = node->right;
			node->right->parent = node->parent;
			
			bst_node<T> *ptr = node->right;
			while (ptr->left != NULL)
			{
				ptr = ptr->left;
			}
			
			node->left->parent = ptr;
			ptr->left = node->left;
			delete node;
		}
		else if (node->key > node->parent->key)		// node is the right child	
		{
			node->parent->right = node->right;
			node->right->parent = node->parent;
			
			bst_node<T> *ptr = node->right;
			while (ptr->left != NULL)
			{
				ptr = ptr->left;
			}
			
			node->left->parent = ptr;
			ptr->left = node->left;
			delete node;
		}
	}
}

template <class T>
int bst<T>::height(bst_node<T> *temp)
{
	if (temp == NULL)
	{
		return -1;
	}
	else
	{
		int h_left = height(temp->left);
		int h_right = height(temp->right);
		
		if (h_left > h_right)
		{
			return h_left + 1;
		}
		else
		{
			return h_right + 1;
		}
	}
}

template<class T>
void bst<T>::replace(T old_key,T new_key)
{
	bst_node<T> *nodeNew = search(new_key);
	if (nodeNew != NULL)
	{
		return;
	}
	else
	{
		bst_node<T> *nodeOld = search(old_key);
		if (nodeOld == NULL)
		{
			return;
		}
		else
		{
			string temp = nodeOld->value;
			insert(temp, new_key);
			delete_node(old_key);
		}	
	}
}
	
		

template <class T>
bst_node<T>* bst<T>::getroot()
{
	return root;
}

template <class T>
void bst<T>::insert_recursive(bst_node<T> *temp, bst_node<T> *node)
{
	if (temp->key > node->key)
	{
		if (!node->right)
		{
			node->right = temp;
			temp->parent = node;
		}
		else
		{
			insert_recursive(temp, node->right);
		}
	}
	else
	{
		if (!node->left)
		{
			node->left = temp;
			temp->parent = node;
		}
		else
		{
			insert_recursive(temp, node->left);
		}
	}
}

template <class T>
bool bst<T>::isExternal(bst_node<T> *node)
{
	if (!node->left && !node->right)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
double bst<T>::execute(bst_node<T> *node)
{
	if (isExternal(node))
	{
		return atoi(node->value.c_str());
		
	}
	else
	{
		double left = execute(node->left);
		double right = execute(node->right);
		
		string op = node->value;
		if (op == "+")
		{
			return left + right;
		}
		else if(op == "-")
		{
			return left - right;
		}
		else if(op == "*")
		{
			return left * right;
		}
		else if(op == "/")
		{
			return left / right;
		}
		
	}
	
}

template <class T>
void bst<T>::buildExpTree(string exp)
{
	root = new bst_node<T>("NULL", 1);
	
	bst_node<T> *ptr = root;
	
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '(')
		{
			ptr->left = new bst_node<T>("NULL", 1);
			ptr->left->parent = ptr;
			ptr = ptr->left;
		}
		else if (exp[i] == ')')
		{
			ptr = ptr->parent;
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
		{
			ptr->value = exp[i];
			ptr->right = new bst_node<T>("NULL", 1);
			ptr->right->parent = ptr;
			ptr = ptr->right;
		}
		else
		{
			ptr->value = exp[i];
			ptr = ptr->parent;
		}
	}
}
#endif
