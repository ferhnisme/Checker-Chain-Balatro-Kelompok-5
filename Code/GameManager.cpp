#include <iostream>
#include "../Code/GameManager.h"
void GameManager::runSession(){
    std::cout << "=== Run Started ===\n";

    char choice;
    std::cout << "Skip blind and take fixed money 20? (y/n): ";
    std::cin >> choice;

    bool skipBlind = (choice == 'y' || choice == 'Y');
    int reward = 0;

    if (skipBlind) {
        std::cout << "Blind skipped at the start. No score will be calculated.\n";
        reward = 20;
    } else {
        Hand hand = handGenerator.generateHand();
        handPlayer.playHand();
        int score = scoringRule.scoreHand(hand);
        bool win = blindRule.checkBlind(score);
        reward = rewardRule.earnMoney(win, score, false);
    }

    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}