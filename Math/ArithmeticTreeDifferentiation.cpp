#include "ArithmeticTree.h"


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
	case('+'): {}
	case('-'):
	{
		newNode->value = node->value;
		newNode->parametr = node->parametr;
		newNode->left = rootDifferentiation(node->left, parametrName, depth + 1);
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
		newNode->left->left = rootDifferentiation(node->left, parametrName, depth + 2);
		newNode->left->right = copyNode(node->right, depth + 2);

		//right
		newNode->right = new Node();
		newNode->right->depth = depth + 1;
		newNode->right->parametr = OPERATOR;
		newNode->right->value = '*';
		newNode->right->left = copyNode(node->right, depth + 2);
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
		newNode->left->left->left = copyNode(node->left, depth + 3);
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
		newNode->right->right->left = rootDifferentiation(node->left, parametrName, depth + 3);
		newNode->right->right->right = copyNode(node->right, depth + 3);
		return newNode;

	}
	default:
		break;
	}



	return newNode;
}