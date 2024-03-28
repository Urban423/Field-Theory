#include "ArithmeticTree.h"
#include "StringAdvanced.h"

#include <math.h>
#include <algorithm>

ArithmeticTree::ArithmeticTree()
{
	root.depth = 0;
}

ArithmeticTree::ArithmeticTree(std::string& input)
{
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	mathCreateTree(&root, (char*)input.c_str(), 0, input.size() - 1);
}

ArithmeticTree::ArithmeticTree(char* str, unsigned int size)
{
	mathCreateTree(&root, str, 0, size - 1);
}

ArithmeticTree::~ArithmeticTree()
{
	
}

void ArithmeticTree::simplificate()
{
	simplification(&root);
}

void ArithmeticTree::setValue(char valueName, double value)
{
	values[valueName] = value;
}



double ArithmeticTree::calculate()
{
	return calculation(&root);
}


double ArithmeticTree::calculation(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	//if node is one of the last ones
	if(node->right == nullptr)
	{
		if(node->parametr == PARAMETR)
		{
			return values[(int)node->value];
		}
		return node->value;
	}
	
	double a = calculation(node->left);
	double b = calculation(node->right);
	
	switch((int)node->value)
	{
		case('+'):
		{
			return a + b;
		}
		case('-'):
		{
			return a - b;
		}
		case('*'):
		{
			return a * b;
		}
		case('^'):
		{
			return pow(a, b);
		}
		case(LN):
		{
			if (b <= 0)
			{
				b = 1;
			}
			return log(b);
		}
	}
	return a + b;
}

std::string ArithmeticTree::toString()
{
	return nodeToString(&root);
}

ArithmeticTree ArithmeticTree::differentiation(char parametrName)
{
	ArithmeticTree tree;
	Node* newRoot = rootDifferentiation(&root, parametrName, 0);
	tree.root = *newRoot;
	if (newRoot != nullptr)
	{
		delete newRoot;
	}
	tree.simplificate();
	return tree;
}

Node* ArithmeticTree::copyNode(Node* node, int startDepth)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	Node* newNode = new Node();
	newNode->value = node->value;
	newNode->depth = startDepth;
	newNode->parametr = node->parametr;
	newNode->left  = copyNode(node->left,  startDepth + 1);
	newNode->right = copyNode(node->right, startDepth + 1);
	return newNode;
}