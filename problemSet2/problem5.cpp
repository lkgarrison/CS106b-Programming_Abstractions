/* problem5.cpp, CS106b, Luke Garrison
 * This program contains the MineSweeper-specific function: MakeGridOfCounts
 * This function takes a grid (2-D) vector of True's and Falses (if there is 
 * a bomb or not) and returns a 2-D vector of the same dimensions with counts
 * in each grid representing the number of bombs immediately surrounding the
 * cell (including diagonals).
 */

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// return T/F if row, col is in bounds for a square grid of the given size
bool isInBounds(int row, int col, int maxDim) {
	if(row >= 0 && row < maxDim && col >= 0 && col < maxDim) {
		return true;
	} else {
		return false;	// row and col is out of bounds
	}
}

vector< vector<int> > MakeGridOfCounts(vector< vector<bool> > & bombLocations) {
	int maxDim = bombLocations[0].size();		// assume square grid
	vector< vector<int> > bombCounts;
	
	// for every cell, check all neighbors, if they are in bounds
	for(int row = 0; row < maxDim; row++) {
		vector<int> bombCountsRow;		// build one row of counts at a time
		for(int col = 0; col < maxDim; col++) {
			// check all 8 chells around the cell
			int bombCount = 0;
			for(int i = -1; i < 2; i++) {
				for(int j = -1; j < 2; j++) {
					if(i == 0 && j == 0) continue;	// don't count current cell
					if(isInBounds(row + i, col + j, maxDim)) {
						// if spot is in bounds and has a bomb, bombCount++
						if(bombLocations[row + i][col + j]) {
							bombCount++;
						}
					}
				}
			}
			bombCountsRow.push_back(bombCount);
		}
		bombCounts.push_back(bombCountsRow);
	}

	return bombCounts;
}

int main() {
	/* for demo purposes, randomly generate a 6x6 grid with randomly placed
 	 * bombs */
	srand(time(NULL));		// seed the random generator
	int boardDimension = 6;		// length and width of board
	vector< vector<bool> > bombLocations;

	/* randomly generate a board. 
	 * If random double is < .25, set a bomb in the cell
	 * if random double is >= .25, no bomb in cell 
	 */
	double bombCutoff = .25; // threshold for bomb. if < bombCutoff, bomb
	cout << "bomb locations:" << endl; 	// for testing/demo purposes
	for(int row = 0; row < boardDimension; row++) {
		vector<bool> bombLocationsRow;  // build one row at a time
		for(int col = 0; col < boardDimension; col++) {
			double randDouble = (double)rand() / RAND_MAX;
			if(randDouble < bombCutoff) {
				bombLocationsRow.push_back(true);
				cout << "O ";
			} else {
				bombLocationsRow.push_back(false);
				cout << ". ";
			}
		}
		cout << endl;
		bombLocations.push_back(bombLocationsRow); // push one row at a time
	}

	// utilize MakeGridOfCounts to create counts grid from bomb locations grid
	vector< vector<int> > bombCounts = MakeGridOfCounts(bombLocations);

	// display bomb counts
	cout << endl << "bomb counts:" << endl;
	for(int row = 0; row < boardDimension; row++) {
		for(int col = 0; col < boardDimension; col++) {
			cout << bombCounts[row][col] << " ";
		}
		cout << endl;
	}
	return 0;
}
