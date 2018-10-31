#ifndef __TREE_CPP
#define __LIST_CPP
#include "tree.h"
#include <fstream>

Tree::Tree()
{
	head = NULL;
}

Tree::Tree(string file)
{
	head = NULL;
	
	ifstream in_file;
	in_file.open(file.c_str());
	
	if (in_file.fail())
	{
		cout << "Error : Reading file. \n";
		exit(1);
	}
	
	string item;
	while (!in_file.eof())
	{
		getline(in_file, item, '\n');
		insert(item);
	}
	
	in_file.close();
}

Tree::~Tree()
{
}

void Tree::insert(string item)
{	
	vector<string> path = parsePath(item);
	
	if (head == NULL)
	{
		head = new TreeItem(path[0]);
	}

	TreeItem *ptr1 = head;
	TreeItem *ptr2 = head->FChild;
	
	for (int i = 1; i < path.size(); i++)
	{	
		bool isFound = false;
		while (ptr2 != NULL)
		{
			if (ptr2->value == path[i])
			{
				isFound = true;
				break;
			}
			else
			{
				ptr2 = ptr2->NextS;
			}
		}
		if (isFound == false)
		{
			TreeItem *temp = new TreeItem(path[i]);
			temp->NextS = ptr1->FChild;
			temp->Parent = ptr1;
			ptr1->FChild = temp;
			ptr2 = temp;	
		}
		
		ptr1 = ptr2;
		ptr2 = ptr2->FChild;
	}
}

vector<string> Tree::Locate(string qry)
{
	TreeItem *node = searchRecursive(head, qry);
	
	vector<string> path;
	if (node)
	{
		while (node != NULL)
		{
			path.push_back(node->value);
			node = node->Parent;
		}
	}
	return path;
	
}

string Tree::LComAc(string a, string b)
{
	vector<string> pathA = Locate(a);
	vector<string> pathB = Locate(b);
	
	for (int i = 0; i < pathA.size(); i++)
	{
		for (int j = 0; j < pathB.size(); j++)
		{
			if (pathA[i] == pathB[j])
			{
				return pathA[i];
			}
		}
	}
}

TreeItem* Tree::getHead()
{
	return head;
}

int Tree::countFiles()
{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		int count = countRecursive(head->FChild);
		return count;
	}
}

vector<string> Tree::parsePath(string item)
{
	vector<string> path;
	string delim = "/";
	int pos = 0;
		
	while ((pos = item.find(delim)) != string::npos)
	{
		path.push_back(item.substr(0, pos));
		item.erase(0, pos + delim.length());
	}
	
	path.push_back(item);	// push back the last instance of the path
	
	return path;
}

TreeItem * Tree::searchRecursive(TreeItem *node, string item)
{
	if (node == NULL)
	{
		return NULL;
	}
	else if (node->value == item)
	{
		return node;	
	}
	else
	{
		 TreeItem *temp1 = searchRecursive(node->FChild, item);
		 TreeItem *temp2 = searchRecursive(node->NextS, item);
		 
		 if (temp1)
		 {
		 	return temp1;
		 }
		 else
		 {
		 	return temp2;
		 }
		
	}
}

int Tree::countRecursive(TreeItem *node)
{
	if (node == NULL)
	{
		return 1;
	}
	else
	{
		int childCount = countRecursive(node->FChild);
		int sibCount = 0;
		if (node->NextS)
		{
			sibCount = countRecursive(node->NextS);
		} 
		
		
		return childCount + sibCount;
	}
}

#endif
