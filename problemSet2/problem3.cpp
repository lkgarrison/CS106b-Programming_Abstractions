/* problem3.cpp, Stanford CS106b, Luke Garrison
 * This program provides the function isCorrectlyNested(string), which returns
 * T/F depending on whether the html string's tags are correctly nested or not.
 */

#include <stack>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void addOpeningTag(stack<string> & tagStack, string tag) {
	tagStack.push(tag);
}

// return true if closing tag being added matches the last added opening tag
// will also pop off the last opening tag
bool addClosingTag(stack<string> & tagStack, string tag) {
	if(tagStack.empty()) return false;		// return false if stack is empty
	if(tagStack.top() == tag) {
		tagStack.pop();
		return true;
	} else {
		return false;
	}
}		

bool isCorrectlyNested(string htmlString) {
	stack<string> tagStack;

	stringstream ss(htmlString);
	string tag;
	char delim = ' ';
	while(getline(ss, tag, delim)) {

		// if tag is an HTML tag, process it. 
		if(tag.find("<") != string::npos) {
			// remove open and closing carrots ("<" and ">")
			int pos = tag.find("<");
			// if "<" was found, remove it
			if(pos != string::npos) {
				tag.erase(tag.begin() + pos);
			}
			
			// find and erase ">" 
			pos = tag.find(">");
			if(pos != string::npos) {
				tag.erase(tag.begin() + pos);
			}

			// check and see if the tag is an opening or closing tag 
			if(tag.find("/") != string::npos) {
				tag.erase(tag.begin() + tag.find("/"));	// remove "/" from tag
				if( !addClosingTag(tagStack, tag)) {
					return false;		// html string is not balanced
				}
			} else {
				addOpeningTag(tagStack, tag);
			}
		}
	}
	if(tagStack.empty()) {
		return true;			// html string is balanced if empty now
	} else {
		return false;			// html string is not balanced if not empty
	}
}

int main() {
	string html1 = "<html> <div> <span> </span> </div> </html>";
	cout << "original string: " << html1 << endl;
	if(isCorrectlyNested(html1)) {
		cout << "  -> correctly nested" << endl;
	} else {
		cout << "  -> NOT nested correctly" << endl;
	}
		
	string html2 = "</html>";
	cout << "original string: " << html2 << endl;
	if(isCorrectlyNested(html2)) {
		cout << "  -> correctly nested" << endl;
	} else {
		cout << "  -> NOT nested correctly" << endl;
	}
	
	return 0;

}
