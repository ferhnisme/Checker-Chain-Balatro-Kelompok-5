#include "RewardRule.h"
#include <iostream>

int RewardRule::earnMoney(bool win, int score) {
    std::cout << "Earning money - win: " << (win ? "yes" : "no") << ", score: " << score << "\n";
    return win ? score * 2 : 0;
}
