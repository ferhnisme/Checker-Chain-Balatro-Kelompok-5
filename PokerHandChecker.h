#pragma once
#include "Hand.h"
enum class HandRank {
HIGH_CARD,
PAIR,
TWO_PAIR,
THREE_OF_A_KIND,
STRAIGHT,
FLUSH,
FULL_HOUSE
};
class PokerHandChecker{
public:
virtual HandRank check(const Hand& hand) = 0;
void setNext(PokerHandChecker* next);
protected:
PokerHandChecker* nextChecker = nullptr;
};

#include "PokerHandChecker.h"
void PokerHandChecker::setNext(PokerHandChecker* next){
nextChecker = next;
}