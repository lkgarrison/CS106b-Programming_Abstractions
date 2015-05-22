/* problem4.cpp, CS106b, Luke Garrison
 *
 * This program will convert surnames to their corresponding Soundex code.
 * The user is able to enter as many surnames as desired before quitting.
 *
 */

#include <iostream>
#include <string>
#include <map>
#include <ctype.h>
using namespace std;

string getSoundexCode(string);
string directTranslation(string);
string applySoundexRules(string);
string setLength(string);

int main() {
	string surname;
	string soundexCode;
	while(1) {
		cout << "Enter surname (press 'q' to quit): ";
		cin >> surname;
		if(surname == "q") break;
		soundexCode = getSoundexCode(surname);
		cout << "Soundex code for " << surname << " is " << soundexCode << endl;
	} 

	return 0;
}
		
string getSoundexCode(string surname) {
	string temp = directTranslation(surname);	// apply translation rules
	temp = applySoundexRules(temp);			// remove duplicates, 0's
	string soundexCode = setLength(temp);	// ensure code has length of 4

	return soundexCode;
}

// return a direct translation of surname based on Soundex Translation
// Keep first letter, then translate each following letter to its #
string directTranslation(string surname) {
	map<char, int> soundexTranslator;
	soundexTranslator.insert(pair<char, int>('A', 0));
	soundexTranslator.insert(pair<char, int>('B', 1));
	soundexTranslator.insert(pair<char, int>('C', 2));
	soundexTranslator.insert(pair<char, int>('D', 3));
	soundexTranslator.insert(pair<char, int>('E', 0));
	soundexTranslator.insert(pair<char, int>('F', 1));
	soundexTranslator.insert(pair<char, int>('G', 2));
	soundexTranslator.insert(pair<char, int>('H', 0));
	soundexTranslator.insert(pair<char, int>('I', 0));
	soundexTranslator.insert(pair<char, int>('J', 2));
	soundexTranslator.insert(pair<char, int>('K', 2));
	soundexTranslator.insert(pair<char, int>('L', 4));
	soundexTranslator.insert(pair<char, int>('M', 5));
	soundexTranslator.insert(pair<char, int>('N', 5));
	soundexTranslator.insert(pair<char, int>('O', 0));
	soundexTranslator.insert(pair<char, int>('P', 1));
	soundexTranslator.insert(pair<char, int>('Q', 2));
	soundexTranslator.insert(pair<char, int>('R', 6));
	soundexTranslator.insert(pair<char, int>('S', 2));
	soundexTranslator.insert(pair<char, int>('T', 3));
	soundexTranslator.insert(pair<char, int>('U', 0));
	soundexTranslator.insert(pair<char, int>('V', 1)); 
	soundexTranslator.insert(pair<char, int>('W', 0));
	soundexTranslator.insert(pair<char, int>('X', 2));
	soundexTranslator.insert(pair<char, int>('Y', 0));
	soundexTranslator.insert(pair<char, int>('Z', 2));
	
	// build up translated surname
	string translation;
	translation.push_back(toupper(surname[0]));	// keep first letter of surname 
	for(int i = 1; i < surname.length(); i++) {
		char c = surname[i];
		if(isalpha(c)) {
			c = toupper(c);			// ensure uppercase
			char charOfInt = soundexTranslator[c] + '0';	// convert int to char
			translation.push_back(charOfInt);
		}
	}
	cout << "direct translation: " << translation << endl;
	return translation;
}	

// apply soundex rules to direct translation of surname. Remove consecutive
// digits, remove any 0's
string applySoundexRules(string temp) {
	// remove duplicates
	char prev = temp[0];
	for(int i = 1; i < temp.length(); i++) {
		if(temp[i] == prev) { // if duplicate consecutive char
			temp.erase(i, 1);
			i--;
		} else {			  // if not a consecutive duplicate
			prev = temp[i];
		}
	}	

	// remove 0's
	for(int i = 0; i < temp.length(); i++) {
		if(temp[i] == '0') {
			temp.erase(i, 1);
		}
	}
	cout << "after applying rules: " << temp << endl;
	return temp;
}

// set length to 4 (truncate or pad with 0's as appropriate)
string setLength(string temp) {
	int requiredLength = 4;
	if(temp.length() == requiredLength) return temp;
	else if(temp.length() < requiredLength) {
		// need to add 0's
		do {
			temp.push_back('0');
		} while(temp.length() < requiredLength);
	} else if(temp.length() > requiredLength) {
		// truncate the code
		temp.erase(requiredLength + 1, temp.length());
	}
	cout << "after setting length: " << temp << endl;
	return temp;
}

