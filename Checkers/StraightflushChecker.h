#pragma once
#include "../Code/PokerHandChecker.h"

class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};