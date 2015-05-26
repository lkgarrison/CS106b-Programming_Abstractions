/* problem2.h, CS106b, Luke Garrison
 *
 * This interface file contains the definition for the ReverseQueue function.
 */

#include <queue>
#include <stack>	// use this to reverse the queue
using namespace std;

// move queue onto a stack, and pop off and place back in the queue
void ReverseQueue(queue<int> & q) {
	stack<int> s;		// use this stack to reverse the queue's contents
	
	// remove elements from queue and push onto stack
	while(! q.empty()) {
		s.push(q.front());
		q.pop();
	}

	// pop the elements off the stack and back onto the queue
	while(! s.empty()) {
		q.push(s.top());
		s.pop();
	}
}
