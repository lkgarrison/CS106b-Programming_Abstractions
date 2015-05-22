/* problem1.cpp, Luke Garrison
 * This program serves to define the function IsPerfect in addition to relevant
 * sub-functions. A perfect number is a number that is equalt to the sum of its
 * proper divisors (a proper divisor is any divisor less than N itself).
 */

#include <iostream>
#include <vector>
using namespace std;

// functon prototypes
vector<int> getProperDivisors(int n);
bool IsPerfect(int n);

int main() {
	// known perfect numbers include 6 and 28
	// demo IsPerfect function by displaying the 4 perfect #'s 1 <= n <= 10000
	int upperLimit = 10000;
	cout << "Perfect numbers between 1 and " << upperLimit << endl;

	for(int i = 1; i < upperLimit; i++) {
		if(IsPerfect(i)) {
			cout << i << endl; 
		}
	}
	return 0;
}

bool IsPerfect(int n) {
	vector<int> divisors = getProperDivisors(n);
	int sumOfDivisors = 0;
	// sum all of the proper divisors of n
	for(int i = 0; i < divisors.size(); i++) {
		sumOfDivisors+= divisors[i];
	}
	if(sumOfDivisors == n) return true;
	else return false;
}	

// return a vector of the proper divisors of any integer n
vector<int> getProperDivisors(int n) {	
	vector<int> divisors;
	if(n >= 0) {
		// brute force check to find every divisor of n (excluding n)
		for(int i = 1; i < n; i++) {
			if(n % i == 0) divisors.push_back(i);
		}
	} else {	// n is negative
		for(int i = -1; i >n; i--) {
			if(n % i == 0) divisors.push_back(i);
		}
	}
	return divisors;
}
