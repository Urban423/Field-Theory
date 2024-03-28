#include "ArithmeticTree.h"



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

	std::string strLeft = nodeToString(node->left);
	std::string strRight = nodeToString(node->right);

	char oper = (char)node->value;
	if (oper == LN)
	{
		oper = 'l';
	}
	return '(' + strLeft + ')' + oper + '(' + strRight + ')';
}