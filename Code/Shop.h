#pragma once
#include <string>
#include "Joker.h"

struct ShopOptions {
    JokerType jokerType = JokerType::NONE;
    bool skipBlind = false;
    int coinsLeft = 0;
};

class Shop {
public:
    ShopOptions openShop(int startingCoins);
};
