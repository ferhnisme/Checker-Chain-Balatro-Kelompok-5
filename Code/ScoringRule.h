#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "HighCardChecker.h"
#include "PairChecker.h"
#include "FourOfAKindChecker.h"
class ScoringRule{
public:
ScoringRule();
int scoreHand(const Hand& hand);
private:
FullHouseChecker fullHouseChecker;
FlushChecker flushChecker;
PairChecker pairChecker;
HighCardChecker highCardChecker;
FourOfAKindChecker fourOfAKindChecker;
int convertRankToScore(HandRank rank);
}