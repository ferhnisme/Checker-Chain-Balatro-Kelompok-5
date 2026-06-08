#pragma once

#include <iostream>
#include <string>
#include "Hand.h"
#include "PokerHandChecker.h"

enum class JokerType {
    NONE,
    PAIR,
    KING
};

inline std::string jokerTypeToString(JokerType type) {
    switch (type) {
        case JokerType::PAIR:
            return "Joker Pair";
        case JokerType::KING:
            return "Joker King";
        default:
            return "No Joker";
    }
}

inline int applyJokerBonus(int score, const Hand& hand, HandRank rank, JokerType type) {
    if (type == JokerType::PAIR) {
        if (rank == HandRank::PAIR) {
            std::cout << "pair joker aktif\n";
            return score * 2;
        }
        return score;
    }
    if (type == JokerType::KING) {
        bool hasKing = false;
        for (int value : hand.cardValues) {
            if (value == 13) {
                hasKing = true;
                break;
            }
        }
        if (hasKing) {
            std::cout << "king joker aktif\n";
            return score + 20;
        }
        return score;
    }
    return score;
}
