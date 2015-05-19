/* problem1.cpp, Luke Garrison
 * This program is my solution to the first problem in Problem Set 1 of 
 * Stanford's Programming Abstractions course, CS106b.
 *
 * The puprose of the program is to create a function that takes two strings
 * as input and returns the first string with all of the characters that are
 * present in the second string removed.
 */

#include <iostream>
#include <string>
using namespace std;

// will return a new string
string censorString1(string text, string remove) {
	// iterate through all of the characters in the remove string
	for(int i = 0; i < remove.length(); i++) {
		while(1) {
			size_t found = text.find(remove[i]); // npos if not found, otherwise index of char
			// if current removal char was not found, skip to next char to consider
			if(found == string::npos) break;
			text.erase(found, 1);   // erase the first instance of the found character
		}
	}
	return text;	
} 	

// will modify the original string
void censorString2(string &text, string remove) {
	// iterate through all characters of the removal string
	for(int i = 0; i < remove.length(); i++) {
		while(1) {
			// try to find removal char in string. found == npos if char not found
			size_t found = text.find(remove[i]);
			if(found == string::npos) break;	// current char is not in the string
			text.erase(found, 1);				// erase the first instance of the found character	
		}
	}
}	

int main() {
	// demo censorString1	
	string result1 = censorString1("Llamas like to laugh", "la");		
	cout << result1 << endl;
	string result2 = censorString1("Stanford University", "nt");
	cout << result2 << endl;

	// demo censorString2
	string text1 = "Llamas like to laugh";
	censorString2(text1, "la");
	cout << text1 << endl;
	string text2 = "Stanford University";
	censorString2(text2, "nt");
	cout << text2 << endl;

	return 0;
}

