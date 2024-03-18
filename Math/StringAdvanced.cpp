#include "StringAdvanced.h"

char checkLetter(unsigned char character)
{
	if(64 < character && character < 91)
	{
		return true;
	}
	if(96 < character && character < 123)
	{
		return true;
	}
	return false;
}

char checkDigit(unsigned char character)
{
	if(47 < character && character < 58)
	{
		return 1;
	}
	return 0;
}

char stringToDouble(double& number, char* str, int size)
{
	number = 0;
	
	double power = 0.1f;
	bool Float = false;
	bool sign = false;
	if(*str == '-')
	{
		size--;
		str++;
		sign = true;
	}
	
	
	for(int i = 0; i < size; i++)
	{
		if(*str == '.' || *str == ',')
		{
			Float = true;
			str++;
			continue;
		}
		if(checkDigit(*str) == false)
		{
			return ERROR_NUMBER_CORRUPTED;
		}
		
		if(Float)
		{
			number += (*str - '0') * power;
			power /= 10;
		}
		else
		{
			number *= 10;
			number += *str - '0';
		}
		str++;
	}
	if(sign)
	{
		number *= -1;
	}
	
	return OK;
}




unsigned char getOperatorPriority(char character)
{
	switch(character)
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
	return CANT_FIND;
}


bool checkParenthesis(char* str, int start, int end)
{
	if(str[start] != '(')
	{
		return false;
	}
	int i = findNextParenthesis(str, start);
	if(i == end)
	{
		return true;
	}
	return false;
}