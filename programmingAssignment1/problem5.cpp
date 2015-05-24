/* problem5.cpp, CS106b, Luke Garrison
 * This program processes an input file and categories the scores in the file
 * based on their range. (ie, tally the number of scores 0-9, 10-19, ect). 
 * Then, a "histogram" of the results are displayed to visually represent
 * the scores in the file.
 * 
 * This assignment and program assumes scores are between 0 and 99.
 */

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
	// get a filename from the user
	string filename;
	ifstream file;
	while(1) {
		cout << "Enter a file name containing scores: ";
		cin >> filename;
		file.open(filename.c_str());
		if(file.good()) break;
		cout << "Invalid file name. Please try again." << endl;
	}

	// initialize a vector for the score tallies
	int nBuckets = 10;
	vector<int> scoreBuckets; // for score ranges. index 0 = 0-9
	for(int i = 0; i < nBuckets; i++) {
		scoreBuckets.push_back(0);
	}

	// process file
	string score;
	while(getline(file, score)) {
		double scoreDouble = strtod(score.c_str(), NULL); // string -> double
		int bucket = scoreDouble / 10;	// 0 = 0-9, 1 = 10-19, ect
		scoreBuckets[bucket]++;			// add a tally to the score bucket	
	}

	// display the results in a "histogram"
	for(int i = 0; i < scoreBuckets.size(); i++) {
		cout << 0 + i*10 << "-" << 9 + i*10 << ": ";
		for(int j = 0; j < scoreBuckets[i]; j++) { // display an "x"/score 
			cout << "x";
		}
		cout << endl;
	}
	return 0;
}	
