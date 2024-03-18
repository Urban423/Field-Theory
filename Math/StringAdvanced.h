#pragma once

#define OK 0
#define CANT_FIND -1
#define ERROR_NUMBER_CORRUPTED 1



//function check if character is a digit
char checkLetter(unsigned char character);

//function check if character is a digit
char checkDigit(unsigned char character);

//function that tranforms string to double, return ERROR_NUMBER_CORRUPTED if can't do it else OK
char stringToDouble(double& number, char* str, int size);

//function return character's priority, by default returns 255
unsigned char getOperatorPriority(char character);

//function that returns index of the next parenthesis, if cnat find returns CANT_FIND
int findNextParenthesis(char* str, int start);

//function that checks if the string starts and ends with pared  parenthesis
bool checkParenthesis(char* str, int start, int end);