/* binarySearch.cpp, Stanford CS106b, Luke Garrison
 * Implementation of binary search algorithm utilizing recursion
 */

#include <vector>
#include <iostream>
using namespace std;

/* Recursive binary search algorithm
 * @param start should be set to 0 in most cases
 * @param end should be set to vec.size() - 1 for initial method calling
 * returns -1 if key is not found
 */
int binarySearch(int key, vector<int> & vec, int start, int end) {
	// if key does not exist, return -1
	if(vec[start] > key || vec[end] < key) {
		return -1;
	}

	// base case, key is at the center of the vector
	// if size is even, pick lower index. If size is odd, pick middle index
	int middle = (start + end) / 2; // middle index of vector
	if(vec[middle] == key) {
		 return middle;
	}

	// if key wasn't found yet, decide if the key resides in the upper or lower
	// half of the current vector
	if(vec[middle] > key) {
		binarySearch(key, vec, start, middle - 1);
	} 
	// else vec[middle] < key (key would be in top half)
	else {
		binarySearch(key, vec, middle + 1, end);
	}
}

/* given a vector of int's and a key, display the key and the index of the
 * vector that the key is found at
 */
void testBS(int key, vector<int> vec) {
	cout << "Index of key (" << key << "): ";
	cout << binarySearch(key, vec, 0, vec.size() - 1) << endl;
}

int main() {
	// create and display a vector
	vector<int> test;
	cout << "vector 1: ";
	for(int i = 0; i < 15; i++) {
		test.push_back(i);
		cout << i << " ";
	}
	cout << endl;

	// display results. manually check if they are correct
	testBS(10, test);
	testBS(11, test);
	testBS(-2, test);

	// provide spacing to make output look nicer
	cout << endl;	

	// create and display a second vector
	vector<int> test2;
	cout << "vector 2: ";
	for(int i = 2; i < 20; i+=2) {
		test2.push_back(i);
		cout << i << " ";
	}
	cout << endl;

	// display results (manually check in console)
	testBS(2, test2);
	testBS(3, test2);
	testBS(10, test2);
	testBS(12, test2);
	testBS(18, test2);
	testBS(20, test2);

	return 0;
}
