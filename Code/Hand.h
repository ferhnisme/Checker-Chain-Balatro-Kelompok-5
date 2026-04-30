<<<<<<< Updated upstream
=======
#pragma once
#include <vector>
#include <algorithm>

struct Hand{
    std::vector<int> cardValues; // Nilai kartu (2-14, dimana 14=As)
    std::vector<int> suits; // Jenis kartu (0=Spade, 1=Heart, 2=Diamond, 3=Club)
    
    Hand() {
        cardValues.resize(5);
        suits.resize(5);
    }
    
    // Helper untuk mendapatkan frekuensi nilai kartu
    std::vector<int> getValueCounts() const {
        std::vector<int> counts(15, 0); // Index 0 tidak digunakan
        for (int v : cardValues) {
            if (v >= 2 && v <= 14) counts[v]++;
        }
        return counts;
    }
    
    // Helper untuk cek apakah semua kartu sama suit
    bool isAllSameSuit() const {
        if (suits.empty()) return false;
        int first = suits[0];
        for (size_t i = 1; i < suits.size(); i++) {
            if (suits[i] != first) return false;
        }
        return true;
    }
    
    // Helper untuk cek apakah kartu berurutan
    bool isConsecutive() const {
        if (cardValues.empty()) return false;
        std::vector<int> sorted = cardValues;
        std::sort(sorted.begin(), sorted.end());
        
        for (size_t i = 0; i < sorted.size() - 1; i++) {
            if (sorted[i+1] != sorted[i] + 1) return false;
        }
        return true;
    }
};
>>>>>>> Stashed changes
