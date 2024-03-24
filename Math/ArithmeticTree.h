#pragma once
#include <string>

#define NUMBER 		0
#define PARAMETR 	1
#define OPERATOR 	2
#define LN			3 //logarithm e

struct Node
{
	char parametr;
	double value;
	int depth;
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
	
	void simplificate();
	void setValue(char valueName, double value);
	double calculate();
	std::string toString();
	ArithmeticTree differentiation(char parametrName);
private:
	std::string nodeToString(Node* node);
	Node* rootDifferentiation(Node* node, char parametrName, int depth);
	Node* copyNode(Node* node, int startDepth);
	void mathCreateTree(Node* node, char* str, int start, int end);
	void simplification(Node* node);
	double calculation(Node* node);
private:
	Node root;
	double values[256] = {0}; 
};