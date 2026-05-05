#pragma once
#include "../Code/PokerHandChecker.h"

class HighCardChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};