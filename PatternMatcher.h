#pragma once
#include <iostream>
#include <string>
using namespace std;

/**
 * A finite automaton class used to find patterns in strings
 */
class PatternMatcher {

	// The maximum number of patterns an automaton can recognize
	static const int MAX_NUM_PATTERNS = 3;
	// An array containing the original strings used to make the automaton
	string patterns[MAX_NUM_PATTERNS];
	// An array containing the current states for each pattern
	int currentStates[MAX_NUM_PATTERNS];
	// The current number of patterns
	int numPatterns;

	public:

		PatternMatcher();
		int addPattern(string pattern);

};
