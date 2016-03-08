#include <string>
#include "PatternMatcher.h"
using namespace std;

PatternMatcher::PatternMatcher() {
	numPatterns = 0;
	// Initialize current state of each path to zero
	for (int p = 0; p < MAX_NUM_PATTERNS; p++) {
		currentStates[p] = 0;
	}
}

int PatternMatcher::addPattern(string pattern) {
	patterns[numPatterns] = pattern;
}
