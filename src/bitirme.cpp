/**
 * @file   BITIRME.cpp
 * @Author Muhammet Fikret ATAR (f.atar2018@gtu.edu.tr) 1801042693 Gebze Technical University
 *
 * @date   September 2021
 * @brief  Bitirme class provide diagrams to appear.
 */

 // BİTİRME.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
 //
 // C++ program to demonstrate rectangle
 // over a self-formed background image
	

#include"statediagram.h"
#include <sstream>

using namespace std;

/*
   Function that checks if the brackets valid
*/
void valid_paren(string input)
{
	// Declaraing a stack.
	stack <char> s;
	int length = input.length();
	char top;
	// Iterating over the entire string.
	for (int i = 0; i < length; i++) {
		//  If the input string contains an opening parenthesis,
		//  push in on to the stack.
		if (input[i] == '(' || input[i] == '{' || input[i] == '[') {
			s.push(input[i]);
		}
		else
		{ // In the case of valid parentheses, the stack cannot be 
		 // be empty if a closing parenthesis is encountered.
			if (s.empty()) {
				cout << input << " contains invalid parentheses." << endl;
				return;
			}
			else {
				top = s.top();
				// If the input string contains a closing bracket,
				// then pop the corresponding opening parenthesis if
				// present.
				if (input[i] == ')' && top == '(' ||
					input[i] == '}' && top == '{' ||
					input[i] == ']' && top == '[') {
					s.pop();
				}
				else {
					// The opening and closing parentheses are of
					// different types. This implies an invaled sequence
					cout << input << " contains invalid parentheses." << endl;
					return;
				}
			}
		}
	}
	//  Checking the status of the stack to determine the
	//  validity of the string.
	if (s.empty()) {
		cout << input << " contains valid parentheses." << endl;
	}
	else {
		cout << input << " contains invalid parentheses." << endl;
	}
}

/*
Function that checks if the token exists
*/
bool isContained(string query, string arr[], int s)
{
	for (int i = 0; i < s; i++)
	{
		if (query == arr[i])
			return true;
	}
	return false;
}

// Driver Code
int main(int argc, char** argv)
{

	convertt();
	convertAndPrint();
	printStates();
	return 0;

}
