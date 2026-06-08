#include <iostream>
#include "GameManager.h"

void GameManager::runSession(){
    std::cout << "=== Run Started ===\n";

    handGenerator.resetDeck();

    const int startingCoins = 10;
    ShopOptions shopOptions = shop.openShop(startingCoins);

    int reward = 0;
    if (shopOptions.skipBlind) {
        std::cout << "Skip Blind purchased. No scoring will be processed.\n";
        reward = 20;
    } else {
        Hand hand = handGenerator.generateHand();
        if (hand.cardValues.empty()) {
            std::cout << "Cannot generate a full hand; deck is depleted.\n";
        } else {
            std::cout << "Generated hand: ";
            hand.display();
            handPlayer.playHand(hand);
            std::cout << "Hand after play: ";
            hand.display();
            int score = scoringRule.scoreHand(hand, shopOptions.jokerType);
            bool win = blindRule.checkBlind(score);
            reward = rewardRule.earnMoney(win, score, false);
        }
    }

    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}