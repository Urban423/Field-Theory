#include "Tree.h"

#include <stdio.h>
#include <unistd.h>

char checkDigit(unsigned char symbol)
{
	if(47 < symbol && symbol < 58)
	{
		return 1;
	}
	return 0;
}

unsigned char getPriority(char symbol)
{
	switch(symbol)
	{
		case('-'):
		{
			
		}
		case('+'):
		{
			return 0;
		}
		case('*'):
		{
			
		}
		case('/'):
		{
			return 1;
		}
		case('^'):
		{
			return 2;
		}
	}
	return 255;
}


int findNextParenthesis(char* str, int start)
{
	int depth = 1;
	start++;
	while(1) {
		if(str[start] == '(') { depth++; }
		else if(str[start] == ')') { depth--; if(depth == 0) { return start; } }
		start++;
	}
	return -1;
}


bool checkParenthesis(char* str, int start, int end)
{
	if(str[start] != '(')
	{
		return false;
	}
	
	int i = findNextParenthesis(str, start + 1);
	if(i == end)
	{
		return true;
	}
	return false;
}


void mathCreateTree(Node* node, char* str, int start, int end)
{
	while(checkParenthesis(str, start, end))
	{
		start++;
		end--;
	}
	
	unsigned char min_priority = 255;
	int min_priority_index = 10000000;
	
	
	for(int i = start; i <= end; i++)
	{
		//skip some arithmetic '()'
		if(str[i] == '(') {
			i = findNextParenthesis(str, i + 1);
		}
		
		unsigned char priority  = getPriority(str[i]);
		if(priority <= min_priority) {
			min_priority = priority;
			if(i < min_priority_index || end - i < end - min_priority_index) {
				min_priority_index = i;
			}
		}
	}
	
	if(min_priority == 255)
	{
		if(checkDigit(str[min_priority_index]))
		{
			int val = 0;
			//for()
		}
		node->value = str[start];
		node->left = nullptr;
		node->right = nullptr;
		return;
	}	
	
	node->value 		= str[min_priority_index];
	node->left 			= new Node();
	node->right 		= new Node();
	node->left->depth 	= node->depth + 1;
	node->right->depth 	= node->depth + 1;
	
	printf("%c %d\n", str[min_priority_index], min_priority_index);
	for(int i = start; i <= min_priority_index - 1; i++)
	{
		printf("%c", str[i]);
	}
	printf("\n");
	for(int i = min_priority_index + 1; i <= end; i++)
	{
		printf("%c", str[i]);
	}
	printf("\n");
	
	mathCreateTree(node->left,  str, start, min_priority_index - 1);
	mathCreateTree(node->right, str, min_priority_index + 1, end  );
}






Tree::Tree()
{
	root.depth = 0;
}

Tree::Tree(char* str, unsigned int size)
{
	mathCreateTree(&root, str, 0, size - 1);
}

Tree::~Tree()
{
	
}