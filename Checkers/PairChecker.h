#pragma once
#include "../Code/PokerHandChecker.h"
class PairChecker : public PokerHandChecker{
public:
HandRank check(const Hand& hand) override;
};