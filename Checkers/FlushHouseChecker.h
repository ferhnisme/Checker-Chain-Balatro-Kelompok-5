#pragma once
#include "../Code/PokerHandChecker.h"

class FlushHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};