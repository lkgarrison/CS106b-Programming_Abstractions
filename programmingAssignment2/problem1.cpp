/* problem1.cpp, CS106b, Luke Garrison
 *
 * This program has the goal of creating a random writer using the Markov model
 * The program reads in a source file (which should be sufficiently large) and
 * tallies the occurence of each character after 1 through k (specified by the
 * user) preceding characters. Thus, the higher the k value specified, the
 * better the Markov model will emulate actual words.
 *
 * For example, 'q' is almost always followed by 'u', and "sh" is often
 * followed by a vowel. Additionally, the word "leave" is often followed by 's'
 * or a space, but never by 'j' or 'q'.
 *
 * This implementation is simplified by using a map of string to a vector of
 * characters. The key is "seed", or sequence of characters, and the value in
 * the map is a vector containing all occurences of what characters follow
 * the given key in the source file. Thus, an index of the vector can be picked
 * at random to pick a good and likely valid next character.
 */

#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

/* Recursive function will read in the file and build the map containing the 
 * prediction data. 
 * Function can safely assume filename is valid, as the filename is tested
 * at the beginning of the program
 * This function will call itself, reducing the markovOrder each time.
 * The end case is when markovOrder == 0
 */
void buildModel(string filename, map<string, vector<char> > & modelData, int markovOrder) {
	if(markovOrder == 0) return;	// end case for recursive function

	// open ifstream for filename
	ifstream ifs;
	ifs.open(filename.c_str());

	// store initial k (markovOrder) characters
	string initial;		
	int count = 0;
	// the file is guaranteed to have at least markovOrder # of chars
	for(int i = 0; i < markovOrder; i++) {
		char c = ifs.get();
		initial.push_back(c);
	}	
		
	// for the rest of the characters in the file, 
	string currentSeed = initial;	// starts off as initial
	char c;
	while(ifs.get(c) && !ifs.eof()) {
		//if(c == '\n') continue;
//		if(c == '\n') c = ' ';
		// check and see if currentSeed is already a key in the map
		if(modelData.find(currentSeed) != modelData.end()) {
			// if it is already a key, add this character's occurence
			modelData[currentSeed].push_back(c);

		} else {
			// if not a key, create a new vector and add this char to it
			// then add the vector to the map
			vector<char> listOfChars;
			listOfChars.push_back(c);
			modelData.insert(pair<string, vector<char> >(currentSeed, listOfChars));
		}
		currentSeed.erase(currentSeed.begin());  // erase the 1st letter
		currentSeed.push_back(c);	// append newest char to the end

	}
	// function is recursive. Repeat until markovOrder reaches 0
	buildModel(filename, modelData, --markovOrder);	
}

/* iterates over the keys of the map to find the key with the largest vector.
 * This key (string) is thus the most occuring, because it had the most
 * recorded instances when reading in the file
 * do not return space. if space is the most occuring, discard this result
 * and use the next most occuring
 */
string findMostOccuringString(map<string, vector<char> > & modelData) {
	map<string, vector<char> >::iterator it;
	string mostOccuringString;
	int mostOccurences = 0;
	for(it = modelData.begin(); it != modelData.end(); it++) {
		if((it->second).size() > mostOccurences) {
			// do not consider a space to be the most occuring string
			if(it->first == " ") continue;	//
			// if this string has the most recorded occurences (so far)
			mostOccurences = (it->second).size();
			mostOccuringString = it->first;
		}
	}
	return mostOccuringString;
}	

/* this method will return the string with the leftmost character removed
 * so that a shorter seed can be used to select another character
 */
string popFront(string seed) {
	if(seed.size() <= 1) throw "Cannot remove more characters. String length is already <= 1";
	string shortenedSeed = seed;
	shortenedSeed.erase(shortenedSeed.begin());
	return shortenedSeed;
}

int main() {
	// initialize random generator
	srand(1);
	// srand(time(NULL));	

	// ask user to provide a markov order number, 1-10
	int markovOrder;
	while(true) {
		cout << "Enter a markov order number, 1-10, for the model: ";
		cin >> markovOrder;
		if(markovOrder > 0 && markovOrder <= 10) break;
		else cout << "  Invalid number entered. Please try again." << endl;
	}
		
	// get a source file from the user
	ifstream ifs;
	string filename;
	while(true) {
		cout << "Enter a source file name, used for prediction power: ";
		cin >> filename;
		ifs.open(filename.c_str());
		// make sure file is good (has more than markovOrder # of chars)
		if(ifs.good()) {
			for(int i = 0; i < markovOrder; i++) {
				if(ifs.fail()) break; 	//  display error message. bad file
				char c = ifs.get();
			}
			if(ifs.good()) break;		// file is good, exit while loop
		} else {
			cout << "Invalid file name. Please try again." << endl;
		}
	}
	ifs.close();
	
	map<string, vector<char> > modelData; 
	
	// analyze source file to build the model
	buildModel(filename, modelData, markovOrder);

	// display keys and their values to check what was read in and stored
	/*map<string, vector<char> >::iterator it;
	for(it = modelData.begin(); it != modelData.end(); it++) {
		for(int i = 0; i < (it->second).size(); i++) {
			// cout << (it->second)[i] << ", ";
		}
		// cout << endl;
	}
	*/

	// find the most occuring key, use as seed
	string seed = findMostOccuringString(modelData);
	cout << "most occuring string (seed): " << seed << endl;

	int demoLength = 2000;		// display 2000 characters for the demo
	int count = seed.size();	// start off with the seed
	cout << seed;

	// try to use markovOrder # of chars to select next char
	// if this sequence has no matches, try 1 less
	while(count < demoLength) {
		// if modelData has a key of seed string, select a random observed char
		if(modelData.find(seed) != modelData.end()) {
			// record number of observations for this seed
			int nObservations = modelData[seed].size();
			
			// randomly choose a valid index of the vector of chars
			int randIndex = rand() % nObservations;	
			char c = modelData[seed][randIndex];	// the char selected
			cout << c;
			count++;	// increment count since a valid char was added
			seed.push_back(c);	// append new char to seed
			if(seed.size() > markovOrder) {
				// only erase 1st char if seed has exceeded user's length
				seed.erase(seed.begin());	// remove 1st char from seed
			}

		/* else if the current seed doesn't exist as a key in the map, remove
		 * the oldest (left-most) char and try again
		 */
		} else {
			if(seed.size() <= 1) {
				cout << "No matches were found for the seed." << endl;
				break;
			}
			cout << "seed not found. shortening..."; 
			string shortenedSeed = popFront(seed);
			continue;	// try again with this shortened seed
		}
	}
	
	cout << endl;

	return 0;
}
