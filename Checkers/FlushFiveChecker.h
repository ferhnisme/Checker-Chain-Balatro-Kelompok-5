#pragma once
#include "../Code/PockerHandChecker.h"

class FlushFiveChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};