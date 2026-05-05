<<<<<<< Updated upstream
=======
#include <iostream>
#include "ThreeOfAKindChecker.h"

bool isThreeOfAKind(const Hand& hand){
    if (hand.cardValues.size() < 5) return false;
    
    std::vector<int> counts = hand.getValueCounts();
    for (int count : counts) {
        if (count == 3) return true;
    }
    return false;
}

HandRank ThreeOfAKindChecker::check(const Hand& hand){
    if (isThreeOfAKind(hand)){
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
>>>>>>> Stashed changes
