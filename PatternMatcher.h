#pragma once
#include <iostream>
#include <string>
using namespace std;

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

		PatternMatcher();
		int addPattern(string patternName, string patternSubstr);
		void readChar(char inputChar);
		bool onFinalState(string patternName);

};
