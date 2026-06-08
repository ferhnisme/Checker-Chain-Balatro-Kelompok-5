#include "Shop.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

static bool askYesNo(const std::string& prompt) {
    char choice;
    while (true) {
        std::cout << prompt;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') return true;
        if (choice == 'n' || choice == 'N') return false;
        std::cout << "Invalid input. Please enter y or n.\n";
    }
}

ShopOptions Shop::openShop(int startingCoins) {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }

    ShopOptions options;
    options.coinsLeft = startingCoins;

    std::cout << "=== Shop ===\n";
    std::cout << "You have " << options.coinsLeft << " coins.\n";

    if (options.coinsLeft >= 10) {
        JokerType offeredJoker = (std::rand() % 2 == 0) ? JokerType::PAIR : JokerType::KING;
        std::cout << "Joker offer available: " << (offeredJoker == JokerType::PAIR ? "Joker Pair" : "Joker King") << " for 10 coins.\n";
        if (askYesNo("Buy this Joker bonus? (y/n): ")) {
            options.jokerType = offeredJoker;
            options.coinsLeft -= 10;
        }
    } else {
        std::cout << "Not enough coins for Joker bonus.\n";
    }

    if (options.coinsLeft >= 5) {
        if (askYesNo("Buy Skip Blind for 5 coins? (y/n): ")) {
            options.skipBlind = true;
            options.coinsLeft -= 5;
        }
    } else {
        std::cout << "Not enough coins for Skip Blind.\n";
    }

    std::cout << "Shop closed. Coins left: " << options.coinsLeft << "\n";
    std::cout << "================\n";
    return options;
}
