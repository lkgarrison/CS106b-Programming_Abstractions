/* problem2.cpp, CS106b, Luke Garrison
 * This problem reports the probability of an invalid election result using
 * 500 trials based on user specified parameters of the number of voters,
 * % spread between cantidates, and voting error percentage. Each of these 
 * parameters are checked to ensire valid inputs.
 *
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

bool isInvalidElection(int, double, double);

int main() {
	int nTrials = 500;		// defined by the problem
	int nVoters;
	double percentSpread, errorPercentage;
	srand(time(NULL));		// seed random number generator

	// get valid input for required paramters
	while(1) {
		cout << "Number of voters: ";
		cin >> nVoters;
		if(nVoters > 0) break;
		cout << "    Error: Enter a number greater than 0." << endl;
	}
	while(1) {
		cout << "Percentage spread between cantidates (decimal form): ";
		cin >> percentSpread;
		if(percentSpread > 0 && percentSpread < 1) break;
		cout << "    Error: Enter a decimal between 0 and 1" << endl;		
	}
	while(1) {
		cout << "Voting error percentage (decimal form): ";
		cin >> errorPercentage;
		if(errorPercentage > 0 && errorPercentage < 1) break;
		cout << "    Error: Enter a decimal between 0 and 1" << endl;
	}
	
	// calculate the number of invalid elections (due to chance of invalid vote)
	int nInvalidElections = 0;
	for(int i = 0; i < nTrials; i++) {
		if(isInvalidElection(nVoters, percentSpread, errorPercentage)) {
			nInvalidElections++;
		}
	}
	
	double chanceOfInvalidElection = (double)nInvalidElections / nTrials;
	cout << "Chance of invalid election result after " << nTrials << " trials = " << chanceOfInvalidElection * 100 << "%" << endl;
		
	return 0;
}

// returns T/F depending on whether or not the election was invalid or not
// based on the parameters and random chance
bool isInvalidElection(int nVoters, double percentSpread, double errorPercentage) {
	// calculate the number of voters for each cantidate
	int nVotedForA = (.5 - (.5 * percentSpread)) * nVoters;
	int nVotedForB =  nVoters - nVotedForA;
	bool isTie = nVotedForA == nVotedForB;
	bool A_won = nVotedForA > nVotedForB;

	// calculate # of votes for both cantidates that were misrecorded
	int nIncorrectA = 0;
	int nIncorrectB = 0;
	for(int i = 0; i < nVotedForA; i++) {
		double randomPercentage = rand() / (double) RAND_MAX;
		if(randomPercentage <= errorPercentage) nIncorrectA++;
	}	
	for(int i = 0; i < nVotedForB; i++) {
		double randomPercentage = rand() / (double) RAND_MAX;
		if(randomPercentage <= errorPercentage) nIncorrectB++;
	}

	// adjust nVotedForA and nVotedForB based on random errors	
	nVotedForA = nVotedForA - nIncorrectA + nIncorrectB;
	nVotedForB = nVotedForB - nIncorrectB + nIncorrectA;

	// return if election was invalid or not
	if(isTie) {
		if(nVotedForA == nVotedForB) return false;	// result is unchanged
		else return true;							// error changed outcome
	} else {
		if(A_won == (nVotedForA > nVotedForB)) {
			return false; // if A should have won/lost and still won/lost
		} else {
			return true; // if error changed outcome
		}
	}
}
