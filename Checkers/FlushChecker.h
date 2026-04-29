#pragma once
#include "../Code/PokerHandChecker.h"
class FlushChecker : public PokerHandChecker{
public:
HandRank check(const Hand& hand) override;
};