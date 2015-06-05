/* palindrome.cpp, Stanford CS106b, Luke Garrison
 * This program includes a function to recursively determine if a string is
 * a palindrome. 
 *
 * There are two base cases:
 * 		1. The empty string
 * 		2. A single character
 * Both of these base cases qualify as palindromes.
 * The first and last letters in the string will be compared until the letters
 * do not match, or one of the base cases occur.
 *
 */

#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
using namespace std;

/* Recurisively check for a palindrome (string without spaces) by checking the
 * first and last characters of the string. If the characters do not match, it
 * is not a palindrome. If they do and it is not a base case, remove the 2 end 
 * characters and call the function again.
 */
bool isPalindromeRecursive(string str) {
	// base case
	if(str.length() == 0 || str.length() == 1) return true;
	
	if(str[0] == str[str.length() - 1] && isPalindromeRecursive(str.substr(1, str.length() - 2))) {
		return true;
	} else {
		return false;
	}
}	

/* helper function that strips whitespace from the string before calling
 * isPalindromeRecursive()
 */
bool isPalindrome(string str) {
	// remove all whitespace in string before checking for palindrome
	for(int i = 0; i < str.length(); i++) {
		if(isspace(str[i])) {
			str.erase(str.begin() + i);
		}
	}
	
	// make call to recursive palindrome function
	if(isPalindromeRecursive(str)) {
		return true;
	} else {
		return false;
	}
}

int main() {
	// create test cases
	string t1 = "hannah";
	string t2 = "banana";
	string t3 = "was it a car or a cat i saw";
	string t4 = "add";
	string t5 = "az";
	string t6 = "zz";
	string t7 = "z";
	string t8 = "";

	// add test cases to vector
	vector<string> testCases;
	testCases.push_back(t1);
	testCases.push_back(t2);
	testCases.push_back(t3);
	testCases.push_back(t4);
	testCases.push_back(t5);
	testCases.push_back(t6);
	testCases.push_back(t7);
	testCases.push_back(t8);

	// test and display all test cases
	cout << "Test Cases:" << endl;
	for(int i = 0; i < testCases.size(); i++) {
		cout << testCases[i] << " : " << (isPalindrome(testCases[i]) ? "true" : "false") << endl;
	}

	return 0;
}
