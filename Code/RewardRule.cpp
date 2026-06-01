#include "RewardRule.h"
#include <iostream>

int RewardRule::earnMoney(bool win, int score, bool skipBlind) {
    if (skipBlind) {
        std::cout << "Skipping blind. Base reward = " << score << "\n";
        return score;
    }

    std::cout << "Earning money - win: " << (win ? "yes" : "no") << ", score: " << score << "\n";
    return win ? score * 2 : 0;
}
