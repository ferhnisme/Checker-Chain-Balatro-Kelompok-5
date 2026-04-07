#include <iostream>
#include "ScoringRule.h"
ScoringRule::ScoringRule(){
flushFiveChecker.setNext(&fiveOfAKindChecker);
fiveOfAKindChecker.setNext(&royalFlushChecker);
royalFlushChecker.setNext(&straightFlushChecker);
straightFlushChecker.setNext(&fourOfAKindChecker);
fourOfAKindChecker.setNext(&fullHouseChecker);
fullHouseChecker.setNext(&flushChecker);
flushChecker.setNext(&straightChecker);
straightChecker.setNext(&threeOfAKindChecker);
threeOfAKindChecker.setNext(&twoPairChecker);
twoPairChecker.setNext(&pairChecker);
pairChecker.setNext(&highCardChecker);
}
int ScoringRule::scoreHand(const Hand& hand){
std::cout << "Calculating hand score...\n";
HandRank rank = flushFiveChecker.check(hand); 
int score = convertRankToScore(rank);
std::cout << "Final score = " << score << "\n";
return score;
}
int ScoringRule::convertRankToScore(HandRank rank){
switch (rank){
case HandRank::FULL_HOUSE:
return 25;
case HandRank::FLUSH:
return 20;
case HandRank::PAIR:
return 10;
case HandRank::HIGH_CARD:
default:
return 5;
case HandRank::TWO_PAIR:
    return 15;
case HandRank::THREE_OF_A_KIND:
    return 18;
case HandRank::STRAIGHT:
    return 22;
case HandRank::FOUR_OF_A_KIND:
    return 30;    
case HandRank::STRAIGHT_FLUSH:
    return 50;
case HandRank::ROYAL_FLUSH:
    return 100;
case HandRank::FIVE_OF_A_KIND:
    return 120;
case HandRank::FLUSH_FIVE:
    return 150;
}
}