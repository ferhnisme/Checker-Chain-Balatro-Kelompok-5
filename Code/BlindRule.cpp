#include "BlindRule.h"
#include <iostream>

bool BlindRule::checkBlind(int score) {
    std::cout << "Checking blind with score: " << score << "\n";
    return score >= 100;
}