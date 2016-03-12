#include <string>
#include "PatternMatcher.h"
using namespace std;

PatternMatcher::PatternMatcher() {
	numPatterns = 0;
}

int PatternMatcher::addPattern(string patternName, string patternSubstring) {
	patterns[numPatterns].name = patternName;
	patterns[numPatterns].substring = patternSubstring;
	patterns[numPatterns].currentState = 0;
	numPatterns += 1;
}

void PatternMatcher::readChar(char inputChar) {
	for (int p = 0; p < numPatterns; p++) {
		if ((patterns[p].currentState + 1) <= patterns[p].substring.length() && inputChar == patterns[p].substring[patterns[p].currentState]) {
			patterns[p].currentState += 1;
		} else {
			patterns[p].currentState = 0;
		}
	}
}

bool PatternMatcher::onFinalState(string patternName) {
	for (int p = 0; p < numPatterns; p++) {
		if (patterns[p].name == patternName) {
			return (patterns[p].currentState == patterns[p].substring.length());
		}
	}
	return false;
}
