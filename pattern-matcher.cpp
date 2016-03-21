#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

/* A struct representing a particular pattern to match; used by PatternMatcher */
struct Pattern {
	// The name of the pattern used for identification
	string name;
	// The original substring to match
	string substring;
	// The current state
	int currentState;
};

/**
 * A finite automaton class used to find patterns in strings
 */
class PatternMatcher {

	// The maximum number of patterns an automaton can recognize
	static const int MAX_NUM_PATTERNS = 5;
	// An array containing the original strings used to make the automaton
	Pattern patterns[MAX_NUM_PATTERNS];
	// The current number of patterns
	int numPatterns;

	public:

		// Constructor; sets the number of starting patterns to 0.
		PatternMatcher() {
			numPatterns = 0;
		}

		/**
		 * addPattern creates a new branch off of the NDFA by adding the patternName
		 * and the patternSubstring to the existing patterns array. addPattern
		 * takes two arguments. The first is its identification so other functions
		 * can refer to that branch. The second is the string that defines the
		 * diffrent tranistions for each branch.
		 */
		int addPattern(string patternName, string patternSubstring) {
			patterns[numPatterns].name = patternName;
			patterns[numPatterns].substring = patternSubstring;
			patterns[numPatterns].currentState = 0;
			numPatterns += 1;
		}

		/**
		 * readChar takes in a single character and compares it to every next state
		 * transition in each branch of the NDFA. If the character is the expected
		 * transition then the currentState for that part of the NDFA will be
		 * incremented. If it is not the expected transition character the state will
		 * reset back to zero.
		 */
		void readChar(char inputChar) {
			for (int p = 0; p < numPatterns; p++) {
				if ((patterns[p].currentState + 1) <= patterns[p].substring.length() && inputChar == patterns[p].substring[patterns[p].currentState]) {
					patterns[p].currentState += 1;
				} else {
					patterns[p].currentState = 0;
				}
			}
		}

		/**
		 * onFinalState checks if the state of the branch given with the patternName
		 * argument is in its final state. If it is, returns true. If it is not,
		 * returns false.
		 */
		bool onFinalState(string patternName) {
			for (int p = 0; p < numPatterns; p++) {
				if (patterns[p].name == patternName) {
					return (patterns[p].currentState == patterns[p].substring.length());
				}
			}
			return false;
		}


};

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
