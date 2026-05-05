#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
#include "../Checkers/FullHouseChecker.h"
#include "../Checkers/FlushChecker.h"
#include "../Checkers/HighCardChecker.h"
#include "../Checkers/PairChecker.h"
#include "../Checkers/FourOfAKindChecker.h"
#include "../Checkers/StraightFlushChecker.h"
#include "../Checkers/RoyalFlushChecker.h"
#include "../Checkers/FiveOfAKindChecker.h"
#include "../Checkers/FlushFiveChecker.h"
#include "../Checkers/FlushHouseChecker.h"
#include "../Checkers/StraightChecker.h"
#include "../Checkers/ThreeOfAKindChecker.h"
#include "../Checkers/TwoPairChecker.h"

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
StraightChecker straightChecker;
ThreeOfAKindChecker threeOfAKindChecker;
TwoPairChecker twoPairChecker;
int convertRankToScore(HandRank rank);
};