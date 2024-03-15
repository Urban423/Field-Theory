#include "stdio.h"
#include "Tree.h"
#include "string.h"

int main()
{
	string input = "(12 * (a * b - a^3) + 3b) - 4 * (a * b^2) - 677";
	input.removeSymbol(' ');
	
	Tree math(input);
	
	//printf("%s\n%d\n", input.c_str(), input.size());
	return 0;
}