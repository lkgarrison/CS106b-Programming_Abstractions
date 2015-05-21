/* problem3.cpp, Luke Garrison
 * CounterLetters function'
 * The purpose of this program is to create and demo the CountLetters function
 * The function will take a filename and count the number of occurances of
 * each letter in the file
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/* CountLetters will print the number of times each letter occurs in the
 * specified file
 */
void CountLetters(string filename) {
	ifstream file(filename.c_str());
	if(file.fail()) return;		// exit function if file name was bad

	// initialize counts vector to count chars
	vector<int> counts(26);		// vector to count chars. Index 0 for 'A'	
	for(int i = 0; i < counts.size(); i++) {
		counts[i] = 0;			// initialize counts of each letter to 0
	}
	
	// process file and count occurances
	char c;						// store the next char in the file
	while(!file.eof()) {		// while there is another char
		c = file.get();
		c = tolower(c);		
		if(isalpha(c)) {
			counts[c - 'a']++;	// incrememnt occurance count
		}
	}
	
	// display letter frequencies
	for(int i = 0; i < counts.size(); i++) {
		char letter = 'a' + i;	// convert int to char
		cout << letter << ": " << counts[i] << endl;
	}
}

int main() {
	string filename;
	cout << "Enter a file to count the letters: "; 
	cin >> filename;

	CountLetters(filename);
	
	return 0;
}	
