/* problem2.cpp, Luke Garrison
 * This program will utilize a struct definition and read in scores from a file
 * and then place the statistics into a struct.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // atoi
using namespace std;

// struct to hold exam stats
struct ExamStats {
	int min;
	int max;
	double avg;
};

ExamStats calcStats(string filename) {
	ifstream statsFile(filename.c_str());
	ExamStats examStats;	// the struct that will be returned
	examStats.min = 100;	// initialize min
	examStats.max = 0;		// initialize max
	int sum = 0;			// sum of scores in file (used to compute avg)
	int count = 0;			// count of # of scores in file
	string scoreString;		// holds one score at a time as they are read in from the file
	int score;

	// read in file	
	while(getline(statsFile, scoreString)) {
		score = atoi(scoreString.c_str());	// convert string score to an integer	
		if(score < examStats.min) examStats.min = score;
		if(score > examStats.max) examStats.max = score;
		sum += score;
		count++;
	}
	examStats.avg = (double) sum / count; // use sum and count to compute avg score
	return examStats;	
}

int main() {
	string filename = "sampleStats.txt";
	ExamStats examStats = calcStats(filename);
	
	// demo calcStats function	
	cout << "Score statistics for " << filename << ":" << endl;
	cout << "\tmin: " << examStats.min << endl;
	cout << "\tmax: " << examStats.max << endl;
	cout << "\tavg: " << examStats.avg << endl;	

	return 0;
}	
	
