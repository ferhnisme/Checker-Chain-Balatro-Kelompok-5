#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "HighCardChecker.h"
#include "PairChecker.h"
#include "FourOfAKindChecker.h"
#include "StraightFlushChecker.h"
#include "RoyalFlushChecker.h"
#include "FiveOfAKindChecker.h"
#include "FlushFiveChecker.h"
#include "FlushHouseChecker.h"
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
StraightFlushChecker straightFlushChecker;
RoyalFlushChecker royalFlushChecker;
FiveOfAKindChecker fiveOfAKindChecker;
FlushFiveChecker flushFiveChecker;
FlushHouseChecker flushHouseChecker;
int convertRankToScore(HandRank rank);
}