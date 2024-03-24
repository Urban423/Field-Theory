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


void ArithmeticTree::mathCreateTree(Node* node, char* str, int start, int end)
{
	if(str[start] == '+')
	{
		start++;
	}
	
	//loop to skip this situation: '((((a + b))))' -> 'a + b'
	while(checkParenthesis(str, start, end)) {
		start++;
		end--;
	}
	
	
	unsigned char min_priority = 0xFF;
	int min_priority_index = 0x7F'FF'FF'FF;
	
	//find operator
	for(int i = start; i <= end; i++)
	{
		//skip some arithmetic '()'
		if(str[i] == '(') {
			i = findNextParenthesis(str, i);
		}
		
		unsigned char priority  = getOperatorPriority(str[i]);
		if(priority <= min_priority) {
			min_priority = priority;
			if(i < min_priority_index || end - i < end - min_priority_index) {
				min_priority_index = i;
			}
		}
	}
	
	
	
	//if operator was't found get value and parametr
	if(min_priority == 255)
	{		
		node->left = nullptr;
		node->right = nullptr;
		node->parametr = NUMBER;
		if (end - start < 0)
		{
			node->value = 0;
			return;
		}
		if(stringToDouble(node->value, str + start, end - start + 1) == OK)
		{
			return;
		}
		if(checkLetter(str[start]) == 1)
		{
			node->parametr = PARAMETR;
			node->value = str[start];
			return;
		}
		node->parametr = OPERATOR;
		node->value = str[start];
		return;
	}	
	
	//if operator was found, create left and right child, then calculate them both
	node->value 		= str[min_priority_index];
	node->left 			= new Node();
	node->right 		= new Node();
	node->left->depth 	= node->depth + 1;
	node->right->depth 	= node->depth + 1;
	
	
	
	
	mathCreateTree(node->left,  str, start, min_priority_index - 1);
	mathCreateTree(node->right, str, min_priority_index + 1, end  );
}

void ArithmeticTree::simplification(Node* node)
{
	if (node == nullptr || node->left == nullptr) { return; }
	simplification(node->left);
	simplification(node->right);

	//if()
}

std::string ArithmeticTree::toString()
{
	return nodeToString(&root);
}

std::string ArithmeticTree::nodeToString(Node* node)
{
	if (node == nullptr)
	{
		return "";
	}
	//if node is one of the last ones
	if (node->right == nullptr)
	{
		if (node->parametr == PARAMETR)
		{
			return std::string(1, node->value);
		}
		return std::to_string(node->value);
	}

	std::string strLeft  = nodeToString(node->left);
	std::string strRight = nodeToString(node->right);

	char oper = (char)node->value;
	if (oper == LN)
	{
		oper = 'l';
	}
	return '(' + strLeft + ')' + oper + '(' + strRight + ')';
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

Node* ArithmeticTree::rootDifferentiation(Node* node, char parametrName, int depth)
{
	Node* newNode = new Node();
	newNode->depth = depth;
	newNode->left = nullptr;
	newNode->right = nullptr;

	if (node->right == nullptr)
	{
		newNode->parametr = NUMBER;
		if (node->parametr == PARAMETR)
		{
			newNode->value = static_cast<char>(node->value) == parametrName ? 1 : 0;
			return newNode;
		}
		newNode->value = 0;
		return newNode;
	}

	printf("operator\n");
	switch (static_cast<char>(node->value))
	{
		case('+'): { }
		case('-'):
		{
			newNode->value = node->value;
			newNode->parametr = node->parametr;
			newNode->left  = rootDifferentiation(node->left,  parametrName, depth + 1);
			newNode->right = rootDifferentiation(node->right, parametrName, depth + 1);
			return newNode;
		}
		case('*'): 
		{
			newNode->value = '+';
			newNode->parametr = OPERATOR;

			//left
			newNode->left = new Node();
			newNode->left->depth = depth + 1;
			newNode->left->parametr = OPERATOR;
			newNode->left->value = '*';
			newNode->left->left  = rootDifferentiation(node->left, parametrName, depth + 2);
			newNode->left->right = copyNode(node->right, depth + 2);

			//right
			newNode->right = new Node();
			newNode->right->depth = depth + 1;
			newNode->right->parametr = OPERATOR;
			newNode->right->value = '*';
			newNode->right->left  = copyNode(node->right, depth + 2);
			newNode->right->right = rootDifferentiation(node->right, parametrName, depth + 2);
			return newNode;
		}
		case('/'):
		{
			newNode->value = '-';
			newNode->parametr = OPERATOR;

			//left
			newNode->left = new Node();
			newNode->left->depth = depth + 1;
			newNode->left->parametr = OPERATOR;
			newNode->left->value = '/';
			newNode->left->left = rootDifferentiation(node->left, parametrName, depth + 2);
			newNode->left->right = copyNode(node->right, depth + 2);

			//right
			newNode->right = new Node();
			newNode->right->depth = depth + 1;
			newNode->right->parametr = OPERATOR;
			newNode->right->value = '/';

			//right -> left
			newNode->right->left = new Node();
			newNode->right->left->depth = depth + 2;
			newNode->right->left->parametr = OPERATOR;
			newNode->right->left->value = '*';

			newNode->right->left->left = copyNode(node->left, depth + 3);
			newNode->right->left->right = rootDifferentiation(node->right, parametrName, depth + 3);


			//right -> right
			newNode->right->right = new Node();
			newNode->right->right->depth = depth + 2;
			newNode->right->right->parametr = OPERATOR;
			newNode->right->right->value = '^';

			newNode->right->right->left = copyNode(node->right, depth + 3);
			newNode->right->right->right = new Node();
			newNode->right->right->right->parametr = NUMBER;
			newNode->right->right->right->depth = depth + 3;
			newNode->right->right->right->value = 2;
			return newNode;

		}
		case('^'):
		{
			newNode->value = '+';
			newNode->parametr = OPERATOR;

			newNode->left = new Node();
			newNode->left->depth = depth + 1;
			newNode->left->value = '*';
			newNode->left->parametr = OPERATOR;

			newNode->left->left = new Node();
			newNode->left->left->depth = depth + 2;
			newNode->left->left->value = '^';
			newNode->left->left->parametr = OPERATOR;
			newNode->left->left->left  = copyNode(node->left,  depth + 3);
			newNode->left->left->right = copyNode(node->right, depth + 3);


			newNode->left->right = new Node();
			newNode->left->right->depth = depth + 2;
			newNode->left->right->value = '*';
			newNode->left->right->parametr = OPERATOR;
			newNode->left->right->left = rootDifferentiation(node->right, parametrName, depth + 3);


			newNode->left->right->right = new Node();
			newNode->left->right->right->depth = depth + 3;
			newNode->left->right->right->value = LN;
			newNode->left->right->right->parametr = OPERATOR;
			newNode->left->right->right->right = copyNode(node->left, depth + 4);


			newNode->right = new Node();
			newNode->right->depth = depth + 1;
			newNode->right->value = '*';
			newNode->right->parametr = OPERATOR;



			newNode->right->left = new Node();
			newNode->right->left->depth = depth + 2;
			newNode->right->left->value = '^';
			newNode->right->left->parametr = OPERATOR;
			newNode->right->left->left = copyNode(node->left, depth + 3);

			newNode->right->left->right = new Node();
			newNode->right->left->right->depth = depth + 3;
			newNode->right->left->right->value = '-';
			newNode->right->left->right->parametr = OPERATOR;
			newNode->right->left->right->left = copyNode(node->right, depth + 4);


			newNode->right->left->right->right = new Node();
			newNode->right->left->right->right->depth = depth + 4;
			newNode->right->left->right->right->value = 1;
			newNode->right->left->right->right->parametr = NUMBER;


			newNode->right->right = new Node();
			newNode->right->right->depth = depth + 2;
			newNode->right->right->value = '*';
			newNode->right->right->parametr = OPERATOR;
			newNode->right->right->left  = rootDifferentiation(node->left, parametrName, depth + 3);
			newNode->right->right->right = copyNode(node->right, depth + 3);
			return newNode;

		}
		default:
			break;
	}
	


	return newNode;
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