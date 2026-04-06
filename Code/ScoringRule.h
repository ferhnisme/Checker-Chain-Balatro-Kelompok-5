#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "HighCardChecker.h"
#include "PairChecker.h"
class ScoringRule{
public:
ScoringRule();
int scoreHand(const Hand& hand);
private:
FullHouseChecker fullHouseChecker;
FlushChecker flushChecker;
PairChecker pairChecker;
HighCardChecker highCardChecker;
int convertRankToScore(HandRank rank);
}