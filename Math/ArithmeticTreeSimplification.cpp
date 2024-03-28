#include "ArithmeticTree.h"

void ArithmeticTree::simplification(Node* node)
{
	if (node == nullptr || node->left == nullptr) { return; }
	simplification(node->left);
	simplification(node->right);

	//if()
}