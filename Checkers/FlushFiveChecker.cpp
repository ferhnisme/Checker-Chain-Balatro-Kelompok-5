#include <iostream>
#include "FlushFiveChecker.h"

bool isFlushFive(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    // Flush Five: semua kartu sama suit DAN semua nilai sama
    if (!hand.isAllSameSuit()) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    for (int count : counts) {
        if (count == 5) return true; // Semua 5 kartu punya nilai yang sama
    }
    return false;
}

HandRank FlushFiveChecker::check(const Hand& hand){
    if (isFlushFive(hand)){
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
