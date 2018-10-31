#ifndef __AVL_CPP
#define __AVL_CPP
#include "avl.h"
#include <fstream>

template <class T>
AvL<T>::AvL()
{
	root = NULL;
}

template <class T>
AvL<T>::~AvL()
{
}

template <class T>
AvLNode<T>* AvL<T>::search(T k)
{
	AvLNode<T> *ptr = root;
	
	while (ptr != NULL)
	{
		if (k > ptr->key)
		{
			ptr = ptr->right;
		}
		else if (k < ptr->key)
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
void AvL<T>::replace(T ok, T nk)
{
		AvLNode<T> *nodeNew = search(nk);
	if (nodeNew != NULL)
	{
		return;
	}
	else
	{
		AvLNode<T> *nodeOld = search(ok);
		if (nodeOld == NULL)
		{
			return;
		}
		else
		{
			string temp = nodeOld->value;
			insert(temp, nk);
			delete_node(ok);
		}	
	}
}

template <class T>
void AvL<T>::delete_node(T k)
{
	AvLNode<T> *node = search(k);
	
	if (node == NULL)
	{
		return;
	}
	
	// Case 1 : node has no subtree
	if (!node->right && !node->left)
	{
		if (node == root)		// node is the root
		{
			root = NULL;
		}
		else if (node->key < node->parent->key)		// node is the left child
		{
			node->parent->left = NULL;
		}
		else if (node->key > node->parent->key)		// node is the right child	
		{
			node->parent->right = NULL;
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
			}
			else if (node->key < node->parent->key)		// node is the left child
			{
				node->parent->left = node->left;
				node->left->parent = node->parent;
			}
			else if (node->key > node->parent->key)		// node is the right child	
			{
				node->parent->right = node->left;
				node->left->parent = node->parent;				
			}
		}
		else if (node->right)	// node has a right subtree
		{
			if (node == root)	// node is the root
			{
				root = node->right;
				node->right->parent = NULL;
			}
			else if (node->key < node->parent->key)		// node is the left child
			{
				node->parent->left = node->right;
				node->right->parent = node->parent;
			}
			else if (node->key > node->parent->key)		// node is the right child	
			{
				node->parent->right = node->right;
				node->right->parent = node->parent;
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
			
			AvLNode<T> *ptr = node->right;
			while (ptr->left != NULL)
			{
				ptr = ptr->left;
			}
			
			node->left->parent = ptr;
			ptr->left = node->left;
		}
		else if (node->key < node->parent->key)		// node is the left child
		{
			node->parent->left = node->right;
			node->right->parent = node->parent;
			
			AvLNode<T> *ptr = node->right;
			while (ptr->left != NULL)
			{
				ptr = ptr->left;
			}
			
			node->left->parent = ptr;
			ptr->left = node->left;
		}
		else if (node->key > node->parent->key)		// node is the right child	
		{
			node->parent->right = node->right;
			node->right->parent = node->parent;
			
			AvLNode<T> *ptr = node->right;
			while (ptr->left != NULL)
			{
				ptr = ptr->left;
			}
			
			node->left->parent = ptr;
			ptr->left = node->left;
		}
	}
	reBalance(node->parent);
	delete node;
}

template <class T>
void AvL<T>::insert(string val, T k)
{
	AvLNode<T> *temp = new AvLNode<T>(val, k);
	
	if (root == NULL)
	{
		root = temp;
	}
	else
	{
		insert_recursive(temp, root);	
	}
}

template<class T>
int AvL<T>::nodeHeight( AvLNode<T> *n)
{
	if (n == NULL)
	{
		return -1;
	}
	else
	{
		int h_left = nodeHeight(n->left);
		int h_right = nodeHeight(n->right);
		
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
AvLNode<T>* AvL<T>::getRoot()
{
	return root;
}

template<class T>
void AvL<T>::insert_recursive(AvLNode<T> *temp, AvLNode<T> *node)
{
	if (temp->key > node->key)
	{
		if (!node->right)
		{
			node->right = temp;
			temp->parent = node;
			reBalance(node);
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
			reBalance(node);
		}
		else
		{
			insert_recursive(temp, node->left);
		}
	}
}

template<class T>
void AvL<T>::set_height_d(AvLNode<T> *node)
{
	node->height_d = nodeHeight(node->left) - nodeHeight(node->right);
	return;
}

template<class T>
AvLNode<T>* AvL<T>::rightRotate(AvLNode<T> *node)
{
	AvLNode<T> *newRoot = node->left;
	newRoot->parent = node->parent;
	node->parent = newRoot;
	node->left = newRoot->right;
	newRoot->right = node;
	
	
	set_height_d(newRoot);
	set_height_d(node);
	return newRoot;
}

template<class T>
AvLNode<T>* AvL<T>::leftRotate(AvLNode<T> *node)
{
	AvLNode<T> *newRoot = node->right;
	newRoot->parent = node->parent;
	node->parent = newRoot;
	node->right = newRoot->left;
	newRoot->left = node;
	
	set_height_d(newRoot);
	set_height_d(node);
	return newRoot;
}

template<class T>
void AvL<T>::reBalance(AvLNode<T> *node)
{
	set_height_d(node);

	if (node->height_d == -2)
	{
		if (nodeHeight(node->right->right) >= nodeHeight(node->right->left))
		{
			if (root == node)
			{
				root = leftRotate(node);
			}
			else if (node->parent->right == node)
			{
				node->parent->right = leftRotate(node);
			}
			else
			{
				node->parent->left = leftRotate(node);
			}	
		}
		else
		{
			node->right = rightRotate(node->right);
			
			if (root == node)
			{
				root = leftRotate(node);
			}
			else if (node->parent->right == node)
			{
				node->parent->right = leftRotate(node);
			}
			else
			{
				node->parent->left = leftRotate(node);
			}
		}
	}
	else if (node->height_d == 2)
	{
		if (nodeHeight(node->left->left) >= nodeHeight(node->left->right))
		{
			if (root == node)
			{
				root = rightRotate(node);
			}
			else if (node->parent->right == node)
			{
				node->parent->right = rightRotate(node);
			}
			else
			{
				node->parent->left = rightRotate(node);
			}	
		}
		else
		{
			node->left = leftRotate(node->left);
			
			if (root == node)
			{
				root = rightRotate(node);
			}
			else if (node->parent->right == node)
			{
				node->parent->right = rightRotate(node);
			}
			else
			{
				node->parent->left = rightRotate(node);
			}
		}
	}
	
	if (node->parent != NULL)
	{
		reBalance(node->parent);
	}

}
#endif
