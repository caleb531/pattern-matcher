#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include "PatternMatcher.h"
using namespace std;

/**
 * Normalizes the document contents by lowercasing it and stripping out
 * non-alphanumeric non-whitespace characters
 * @param  fin A reference to an existing ifstream object
 * @return The new contents of the document
 */
string normalizeDocContents(ifstream &fin) {

	stringstream newContents;
	char ch;
	while (!fin.eof()) {
		fin.get(ch);
		// If string is whitespace or alphabnumeric
		if (isalnum(ch) || ch == ' ' || ch == '\n') {
			// Convert character to lowercase and add it to new string
			newContents << (char)tolower(ch);
		}
	}

	return newContents.str();

}

int main() {

	ifstream fin("testdoc.txt");
	string docContents = normalizeDocContents(fin);

	int currentDocId = 0;

	// This will change later
	PatternMatcher matcher;
	matcher.addPattern("docid", "docdocid ");
	matcher.addPattern("term1", "text mining");
	matcher.addPattern("term2", "information retrieval");
	matcher.addPattern("term3", "text data mining");

	// Print the contents of testdoc.txt
	for (int c = 0; c < docContents.length(); c++) {
		// cout << docContents[c];
		matcher.readChar(docContents[c]);
		if (matcher.onFinalState("docid")) {
			currentDocId += 1;
			// cout << currentDocId << endl;
		}
		if (matcher.onFinalState("term1")) {
			cout << "\"text mining\" found in document " << currentDocId << endl;
		}
		if (matcher.onFinalState("term2")) {
			cout << "\"information retrieval\" found in document " << currentDocId << endl;
		}
		if (matcher.onFinalState("term3")) {
			cout << "\"information retrieval\" found in document " << currentDocId << endl;
		}
	}

	return 0;

}
