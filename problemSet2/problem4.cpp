/* problem5.cpp, CS106b, Luke Garrison
 *
 * This program will use a map to count the number of occurances of each
 * character in a file stream. After the file is read, the map is iterated over
 * to find which character occured the most.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <ctype.h>
using namespace std;

/* takes a file stream and places the count for each character in a map.
 * Returns the character which occurs the most
 */
char MostFrequentChar(ifstream &ifs, int &numOccurrences) {
	map<char, int> occurences;	// key = the char, val = num occurences
	// initialize all counts to 0
	int alphabetSize = 26;
	for(int i = 0; i < alphabetSize; i++) {
		occurences.insert(pair<char, int>('a' + i, 0));
	}
	
	// read in the file, char by char, and continuously update counts
	while(!ifs.eof()) {
		char c = ifs.get();
		c = tolower(c);
		if(! isalpha(c)) continue;
		int prevCount = occurences[c];
		occurences[c] = occurences[c] + 1;
	}
	
	// iterate over map to find the char with the highest frequency
	int highestFrequency = 0;
	char mostCommonChar;
	map<char, int>::iterator it;
	for(it = occurences.begin(); it != occurences.end(); it++) {
		if(it->second > highestFrequency) { // char has highest frequency
			highestFrequency = it->second;	// set new highestFrequncy
			mostCommonChar = it->first;		// set most common char
		}
	}
	
	return mostCommonChar;	
}

int main() {
	// get a valid file name from the user
	ifstream ifs;
	while(true) {
		string filename;
		cout << "Enter a file name: ";
		cin >> filename;
		ifs.open(filename.c_str());
		if(ifs.good()) break;
		else cout << "  Invalid file name. Please try again." << endl;
	}

	int numOccurences = 0;	// will be passed by reference to function
	cout << "Most frequent character in file: " << MostFrequentChar(ifs, numOccurences) << endl;
	
	return 0;
}
