#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include "PatternMatcher.h"
using namespace std;

/**
 * Normalizes the given document contents by lowercasing it and stripping out
 * non-alphanumeric non-whitespace characters
 * @param  origContents The original contents of the document
 * @return              The new contents of the document
 */
string normalizeDocContents(string origContents) {

	stringstream newContents;

	for (int c = 0; c < origContents.length(); c++) {
		// If string is whitespace or alphabnumeric
		if (isalnum(origContents[c]) || origContents[c] == ' ' || origContents[c] == '\n') {
			// Convert character to lowercase and add it to new string
			newContents << (char)tolower(origContents[c]);
		}
	}

	return newContents.str();

}

int main() {

	ifstream fin("testdoc.txt");
	stringstream buffer;
	buffer << fin.rdbuf();
	string docContents = normalizeDocContents(buffer.str());

	// This will change later
	PatternMatcher matcher;
	matcher.addPattern("text mining");
	matcher.addPattern("information retrieval");
	matcher.addPattern("text data mining");

	// Print the contents of testdoc.txt
	for (int c = 0; c < docContents.length(); c++) {
		cout << docContents[c];
	}

	return 0;

}
