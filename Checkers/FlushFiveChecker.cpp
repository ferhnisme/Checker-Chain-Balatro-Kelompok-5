#include <iostream>
#include "FlushFiveChecker.h"

bool isFlushFive(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    // Flush Five: semua kartu sama suit DAN semua nilai berbeda
    if (!hand.isAllSameSuit()) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    for (int count : counts) {
        if (count > 1) return false; // Tidak ada duplikat
    }
    return true;
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
