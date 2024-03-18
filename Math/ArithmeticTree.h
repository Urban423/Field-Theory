#pragma once
#include <string>

#define NUMBER 		0
#define PARAMETR 	1
#define OPERATOR 	2

struct Node
{
	char parametr;
	double value;
	int depth;
	Node* parent;
	Node* left;
	Node* right;
};


class ArithmeticTree
{
public:
	ArithmeticTree();
	ArithmeticTree(std::string& input);
	ArithmeticTree(char* str, unsigned int size);
	~ArithmeticTree();
	
	void setValue(char valueName, double value);
	double calculate();
private:
	void mathCreateTree(Node* node, char* str, int start, int end);
	double calculation(Node* node);
private:
	Node root;
	double values[256] = {0}; 
};