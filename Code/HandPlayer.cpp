#include "HandPlayer.h"
#include <iostream>

#include <sstream>
#include <set>

static std::set<int> parseSelectedIndices(const std::string& input, int handSize){
    std::set<int> indices;
    std::istringstream ss(input);
    int value;
    while (ss >> value) {
        if (value >= 1 && value <= handSize) {
            indices.insert(value - 1);
        }
    }
    return indices;
}

void HandPlayer::playHand(Hand& hand) {
    const int maxSelectable = 5;
    const int handSize = static_cast<int>(hand.cardValues.size());

    std::cout << "Playing hand...\n";
    if (handSize == 0) {
        std::cout << "Hand is empty. Nothing to play.\n";
        return;
    }

    std::cout << "Your hand (choose up to " << maxSelectable << " cards):\n";
    for (int i = 0; i < handSize; ++i) {
        std::cout << "[" << i + 1 << "] ";
        Hand cardOnly;
        cardOnly.cardValues = { hand.cardValues[i] };
        cardOnly.suits = { hand.suits[i] };
        cardOnly.display();
    }

    std::string input;
    std::set<int> selectedIndices;
    while (true) {
        std::cout << "Masukkan nomor kartu yang ingin dimainkan (pisahkan spasi, maksimal " << maxSelectable << "): ";
        std::getline(std::cin, input);
        selectedIndices = parseSelectedIndices(input, handSize);

        if (selectedIndices.empty()) {
            std::cout << "Pilihan tidak valid. Silakan pilih minimal satu kartu.\n";
            continue;
        }
        if (static_cast<int>(selectedIndices.size()) > maxSelectable) {
            std::cout << "Anda hanya boleh memilih maksimal " << maxSelectable << " kartu.\n";
            continue;
        }
        break;
    }

    Hand selectedHand;
    for (int index : selectedIndices) {
        selectedHand.cardValues.push_back(hand.cardValues[index]);
        selectedHand.suits.push_back(hand.suits[index]);
    }

    std::cout << "Kartu yang dimainkan: ";
    selectedHand.display();

    hand = std::move(selectedHand);
}

void HandPlayer::discardCards() {
    std::cout << "Discarding cards...\n";
}