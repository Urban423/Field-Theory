#pragma once

struct Node
{
	int value;
	int depth;
	Node* parent;
	Node* left;
	Node* right;
};


class Tree
{
public:
	Tree();
	Tree(char* str, unsigned int size);
	~Tree();
private:
	Node root;
};