/* problem2.cpp, CS106b, Luke Garrison
 *
 * This is a driver program for the ReverseQueue function found in the file 
 * problem2.h. This program will demonstrate that the ReverseQueue function
 * works as expected.
 */

#include <queue>
#include <iostream>
#include "problem2.h"
using namespace std;

int main() {
	// instantiate a queue and add a few integers to it
	int n = 4;		// number of int's to add to queue
	queue<int> q;
	cout << "Original queue: ";
	for(int i = 0; i < n; i++) {
		q.push(i);
		cout << i << (((i+1) % n  == 0) ? " " : ", ");
	}
	cout << endl;

	ReverseQueue(q);	// call the ReverseQueue method

	// demo that the queue has been reversed
	cout << "Reversed queue: ";
	for(int i = 0; i < n; i++) {
		cout << q.front() << (((i+1) % n == 0) ? " " : ", ");
		q.pop();
	}
	cout << endl;

	return 0;
}
