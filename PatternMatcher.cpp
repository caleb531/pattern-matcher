#include <string>
#include "PatternMatcher.h"
using namespace std;

//Constructor. Sets the number of starting patterns to 0.
PatternMatcher::PatternMatcher() {
	numPatterns = 0;
}

/**
 * addPattern creates a new branch off of the NDFA by adding the patternName
 * and the patternSubstring to the existing patterns array. addPattern
 * takes two arguments. The first is its identification so other functions 
 * can refure to that branch. The second is the string that defines the 
 * diffrent tranistions for each branch.
 */
int PatternMatcher::addPattern(string patternName, string patternSubstring) {
	patterns[numPatterns].name = patternName;
	patterns[numPatterns].substring = patternSubstring;
	patterns[numPatterns].currentState = 0;
	numPatterns += 1;
}

/**
 * readChar takes in a single character and compares it to every next state
 * transition in each branch of the NDFA. If the character is the expected
 * transition then the currentState for that part of the NDFA will incress.
 * If it is not the expected transition character the state will reset back
 * to zero.
 * 
 */
void PatternMatcher::readChar(char inputChar) {
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
 * argument is in it's final state. If it is, returns true. If it is not 
 * returns false.
 */
bool PatternMatcher::onFinalState(string patternName) {
	for (int p = 0; p < numPatterns; p++) {
		if (patterns[p].name == patternName) {
			return (patterns[p].currentState == patterns[p].substring.length());
		}
	}
	return false;
}
