#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
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

	// Vectors for each of the terms to track the documents they are found in
	vector<string> term1Vector;
	vector<string> term2Vector;
	vector<string> term3Vector;

	for (int c = 0; c < docContents.length(); c++) {
		matcher.readChar(docContents[c]);
		if (matcher.onFinalState("docid")) {
			currentDocId += 1;
			term1Vector.resize(currentDocId);
			term2Vector.resize(currentDocId);
			term3Vector.resize(currentDocId);
		}
		if (matcher.onFinalState("term1")) {
			term1Vector[currentDocId - 1] = currentDocId + '0';
		}
		if (matcher.onFinalState("term2")) {
			term2Vector[currentDocId - 1] = currentDocId + '0';
		}
		if (matcher.onFinalState("term3")) {
			term3Vector[currentDocId - 1] = currentDocId + '0';
		}
	}

	cout << "\"text mining\" found in document(s): ";
	for (int i = 0; i < term1Vector.size(); i++) {
		cout << term1Vector[i] + " ";
	}
	cout << endl;
	cout << "\"information retrieval\" found in document(s): ";
	for (int i = 0; i < term2Vector.size(); i++) {
		cout << term2Vector[i] + " ";
	}
	cout << endl;
	cout << "\"text data mining\" found in document(s): ";
	for (int i = 0; i < term3Vector.size(); i++) {
		cout << term3Vector[i] + " ";
	}
	cout << endl;

	return 0;

}
