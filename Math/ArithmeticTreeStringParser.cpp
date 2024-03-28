#include "ArithmeticTree.h"
#include "StringAdvanced.h"


void ArithmeticTree::mathCreateTree(Node* node, char* str, int start, int end)
{
	if (str[start] == '+')
	{
		start++;
	}

	//loop to skip this situation: '((((a + b))))' -> 'a + b'
	while (checkParenthesis(str, start, end)) {
		start++;
		end--;
	}


	unsigned char min_priority = 0xFF;
	int min_priority_index = 0x7F'FF'FF'FF;

	//find operator
	for (int i = start; i <= end; i++)
	{
		//skip some arithmetic '()'
		if (str[i] == '(') {
			i = findNextParenthesis(str, i);
		}

		unsigned char priority = getOperatorPriority(str[i]);
		if (priority <= min_priority) {
			min_priority = priority;
			if (i < min_priority_index || end - i < end - min_priority_index) {
				min_priority_index = i;
			}
		}
	}



	//if operator was't found get value and parametr
	if (min_priority == 255)
	{
		node->left = nullptr;
		node->right = nullptr;
		node->parametr = NUMBER;
		if (end - start < 0)
		{
			node->value = 0;
			return;
		}
		if (stringToDouble(node->value, str + start, end - start + 1) == OK)
		{
			return;
		}
		if (checkLetter(str[start]) == 1)
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
	node->value = str[min_priority_index];
	node->left = new Node();
	node->right = new Node();
	node->left->depth = node->depth + 1;
	node->right->depth = node->depth + 1;




	mathCreateTree(node->left, str, start, min_priority_index - 1);
	mathCreateTree(node->right, str, min_priority_index + 1, end);
}