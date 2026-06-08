# Checker Chain Balatro - Technical Design Document (TDD)

## Overview
Balatro adalah sistem evaluasi kartu poker dan scoring dalam C++ yang terinspirasi dari permainan poker roguelike.
Proyek ini dirancang untuk:
- mengevaluasi kombinasi poker,
- menghitung skor,
- menerapkan efek joker,
- mengelola tindakan pemain seperti PLAY dan DISCARD.

Arsitektur proyek bersifat modular, sehingga tiap sistem bertanggung jawab secara terpisah dan dapat diperluas tanpa merombak keseluruhan.

## 1. High-Level Architecture
Proyek dibagi menjadi sistem utama berikut:
- `GameManager`: mengontrol alur permainan keseluruhan.
- `Deck`: menyimpan dan mengelola kartu.
- `HandState`: menyimpan kartu yang sedang dipegang pemain.
- `ChosenHand`: menyimpan kartu yang dipilih untuk scoring.
- `PokerHandEvaluator`: mendeteksi tipe hand poker.
- `ScoringRule`: menghitung skor dasar.
- `JokerManager`: menerapkan efek joker.
- `ScoreContext`: menyimpan data skor yang dapat dimodifikasi.

## 2. Runtime Flow
Alur sesi permainan:
1. `main()`
2. `GameManager::runSession()`
3. Setup joker
4. Buat deck
5. Acak deck
6. Draw hand awal
7. Pemain memilih kartu
8. Evaluasi hand
9. Hitung skor dasar
10. Terapkan efek joker
11. Cetak hasil akhir

## 3. System Flow
Runtime dibagi menjadi tiga tahap utama:
1. Session Setup
2. Main Gameplay Loop
3. Action Branches

### 3.1. Session Setup
Tahap ini menyiapkan game sebelum pemain mulai bermain.
Flow:
`main()` → `GameManager::runSession()` → `RunSessionService::runSession()`

Tanggung jawab utama:
- `setupJokers()`: mendaftarkan efek joker aktif.
  - contoh: `PairJoker`, `FlatChipJoker`
- `createShuffledDeck()`: membuat deck 52 kartu dan mengacaknya.
- `drawInitialHand()`: menarik hand awal ke `HandState`.

### 3.2. Main Gameplay Loop
Tahap ini berulang sampai sesi selesai.
Flow:
`runSessionLoop()` → print state → baca aksi pemain → validasi aksi → proses aksi

Fungsi utama:
- `runSessionLoop()`: menjalankan siklus gameplay.
- `readPlayerActionRequest()`: membaca indeks kartu yang dipilih dan aksi (`PLAY` atau `DISCARD`).
- `canPerformAction()`: memastikan aksi masih dapat dilakukan.
  - contoh: sisa play, sisa discard.
- `processPlayerAction()`: mengarahkan ke branch `PLAY` atau `DISCARD`.

### 3.3. Action Branches
Alur gameplay berubah sesuai aksi pemain.

#### PLAY Branch
Digunakan saat pemain ingin meng-score hand.
Flow:
Kartu dipilih → evaluasi poker hand → hitung skor dasar → terapkan joker → update skor → kurangi sisa play

Tanggung jawab utama:
- `resolveHand()`: menentukan tipe poker hand, chip dasar, dan multiplier.
- `createScoreContext()`: membuat data skor runtime yang dapat dimodifikasi oleh joker.
- `applyJokers()`: menerapkan semua efek joker.
- `printResult()`: menampilkan tipe hand, chips, multiplier, dan skor akhir.

#### DISCARD Branch
Digunakan saat pemain mengganti kartu.
Flow:
Buang kartu terpilih → draw kartu baru → update hand → kurangi sisa discard

## 4. Card System

### 4.1. Card
Setiap kartu berisi:
- Rank: Two hingga Ace
- Suit: Hearts, Diamonds, Clubs, Spades

Kartu digunakan oleh:
- sistem deck,
- evaluasi hand,
- scoring,
- sistem joker.

### 4.2. Deck
Kelas `Deck` mengelola semua kartu.
Tanggung jawab utama:
- membuat 52 kartu,
- mengacak kartu,
- menarik kartu,
- melacak sisa kartu.

Fungsi utama:
- `initialize()`: buat semua kartu 52.
- `shuffle()`: acak urutan kartu.
- `drawCard()`: ambil kartu teratas.
- `size()`: kembalikan jumlah kartu tersisa.
- `isEmpty()`: cek apakah deck kosong.

Deck menggunakan:
- `std::shuffle`
- `std::mt19937`
untuk randomisasi.

### 4.3. HandState
`HandState` menyimpan hand yang sedang dipegang pemain.
Contoh:
`[7♥] [K♣] [2♦] [A♠] [10♠]`

### 4.4. ChosenHand
`ChosenHand` menyimpan kartu yang dipilih untuk scoring.
Dengan pemisahan ini, pemain dapat menyimpan banyak kartu tetapi hanya kartu terpilih yang dinilai.

### 4.5. Draw and Discard System
`DrawService`: menarik kartu dari deck ke hand pemain.
`DiscardService`: menghapus kartu terpilih dan menggantinya jika perlu.

## 5. Poker Hand Evaluation System

### 5.1. PokerHandEvaluator
Sistem ini menentukan tipe poker hand yang dibuat pemain.
Contoh:
- Pair
- Straight
- Flush
- Full House

### 5.2. Cara Evaluasi Bekerja
Evaluator menyimpan beberapa checker hand.
Checker diperiksa satu per satu berdasarkan prioritas.
Checker pertama yang cocok menjadi hasil final.

Contoh:
- Cek Flush Five → tidak cocok
- Cek Full House → cocok
- STOP
- Hasil = Full House

### 5.3. PokerHandChecker
Setiap checker bertanggung jawab untuk satu tipe poker hand.
Contoh:
- `FlushChecker`
- `StraightChecker`
- `PairChecker`

Fungsi yang dibutuhkan:
- `checkPokerHand(const std::vector<Card>& cards)`
- `getHandType()`

### 5.4. Evaluation Priority
Urutan pengecekan dari terkuat ke terlemah:
1. FlushFive
2. FlushHouse
3. FiveOfAKind
4. RoyalFlush
5. StraightFlush
6. FourOfAKind
7. FullHouse
8. Flush
9. Straight
10. ThreeOfAKind
11. TwoPair
12. Pair
13. HighCard

`HighCardChecker` bertindak sebagai fallback.
Jika tidak ada hand lain yang cocok, `HighCard` dikembalikan.

## 6. Scoring System

### 6.1. HandResolver
Menggabungkan evaluasi poker hand dan aturan scoring untuk menghasilkan `PlayedHandResult`.

`PlayedHandResult` menyimpan:
- cards: kartu terpilih
- handType: tipe poker hand
- level: level hand
- chips: nilai dasar chips
- mult: multiplier dasar
- finalScore: skor akhir

### 6.2. HandScoreTable
Menyimpan nilai skor untuk setiap tipe hand.
Contoh:
- Pair: 10 chips, mult 2
- Flush: 35 chips, mult 4
- Straight Flush: 100 chips, mult 8

### 6.3. ScoringRule
Menghitung skor dasar.
Formula dasar:
`Final Score = chips × mult`
Contoh:
`30 chips × 4 mult = 120 score`

## 7. Joker System

### 7.1. ScoreContext
Menyimpan data skor runtime yang dapat berubah.
`ScoreContext` memuat:
- cards,
- hand type,
- level,
- chips,
- multiplier.

Joker memodifikasi objek ini secara langsung.

### 7.2. JokerManager
Bertanggung jawab untuk:
- menyimpan joker,
- memberitahu joker,
- menerapkan efek modifier.

### 7.3. Joker Flow
Flow dasar:
Base Score → JokerManager notifies jokers → Jokers modify ScoreContext → Final score updated

### 7.4. Joker
Joker merupakan modifier skor.
Setiap joker dapat:
- memeriksa kondisi,
- memodifikasi chips,
- memodifikasi multiplier.

### 7.5. Built-In Jokers
Contoh:
- `PairJoker`
  - aktif saat hand type adalah Pair
  - efek: +4 mult
- `FlatChipJoker`
  - selalu aktif
  - efek: +20 chips

## 8. Extension Guide

### 8.1. Menambahkan Joker Baru
Langkah 1 — Buat Kelas Joker Baru
- Buat kelas yang mewarisi dari `Joker`, misalnya `MyNewJoker : public Joker`.

Langkah 2 — Implementasikan Fungsi Wajib
- `getName()`
- `getDescription(const ScoreContext&)`
- `onScoreCalculated(ScoreContext&)`

Langkah 3 — Daftarkan Joker
- Tambahkan joker di `GameManager::setupJokers()`.
- Contoh: `jokerManager.addJoker(std::make_unique<MyNewJoker>());`

Aturan Penting:
- Joker hanya boleh memodifikasi chips, multiplier, atau score context.
- Joker tidak boleh merusak pipeline scoring dasar.

### 8.2. Menambahkan Poker Hand Baru
Langkah 1 — Tambahkan Tipe Hand Baru
- Tambahkan nilai baru di enum `PokerHandType`.

Langkah 2 — Buat Checker Baru
- Buat kelas turunan `PokerHandChecker`.
- Implementasikan `checkPokerHand(const std::vector<Card>&)` dan `getHandType()`.

Langkah 3 — Daftarkan Checker
- Tambahkan checker di `PokerHandEvaluator`.
- Pastikan urutan pemeriksaan benar: hand terkuat terlebih dahulu.

Langkah 4 — Tambahkan Data Skor
- Update `HandScoreTable` dengan nilai skor untuk tipe hand baru.

## 9. Blind State System & Skip Reward Command System

Bagian ini menjelaskan proposal arsitektur untuk blind progression dan skip reward.
Tujuan utama:
- memisahkan logika blind dari gameplay loop utama,
- menghindari if-else blind progression yang panjang,
- membuat skip reward lebih modular,
- mendukung deferred reward execution,
- mempermudah extensibility di masa depan.

### 9.1. Masalah yang Dihadapi
Implementasi awal blind progression dapat berkembang menjadi banyak kondisi:
- Small Blind
- Big Blind
- Boss Blind

Jika semua logika berada di dalam `RunSessionService`, class akan:
- terlalu besar,
- penuh branching,
- sulit dipelihara,
- sulit diperluas.

Masalah serupa muncul pada skip reward:
- efek berbeda-beda,
- waktu aktivasi berbeda,
- beberapa reward langsung aktif,
- beberapa reward aktif pada blind berikutnya,
- beberapa reward aktif saat shop,
- beberapa reward aktif saat ante berikutnya.

Jika semua reward ditangani dengan `if (rewardType == ...)`, sistem akan sulit dikembangkan.

### 9.2. Solusi Arsitektur
Proposal membagi sistem menjadi dua bagian:
1. Blind Progression → State Pattern
2. Skip Reward → Command Pattern

#### Blind Progression - State Pattern
State Pattern menangani urutan:
Small Blind → Big Blind → Boss Blind → Next Ante

Setiap blind merupakan objek state terpisah.

#### Skip Reward - Command Pattern
Command Pattern menangani:
- reward hasil skip blind,
- reward deferred,
- reward yang dieksekusi nanti,
- reward dengan logic sendiri.

## 10. Blind State Pattern

### 10.1. Tujuan
State Pattern memungkinkan:
- tiap blind memiliki behavior sendiri,
- blind progression tanpa if-else,
- boss blind memiliki logic khusus,
- blind type baru mudah ditambahkan.

### 10.2. BlindState Interface
Contoh interface:
```cpp
class BlindState {
public:
    virtual ~BlindState() = default;
    virtual std::string getName() const = 0;
    virtual int getTargetScore(int ante) const = 0;
    virtual int getRewardMoney() const = 0;
    virtual PendingCommand createSkipRewardCommand() const = 0;
    virtual std::unique_ptr<BlindState> nextState(int& ante) const = 0;
};
```

Tanggung jawab masing-masing blind:
- menentukan target score,
- menentukan reward money,
- menentukan skip reward,
- menentukan state berikutnya.

### 10.3. Contoh State
#### SmallBlindState
- `getTargetScore(int ante)` → `300 * ante`
- `getRewardMoney()` → `3`
- `nextState(int& ante)` → `BigBlindState`

#### BigBlindState
- `getTargetScore(int ante)` → `450 * ante`
- `getRewardMoney()` → `4`
- `nextState(int& ante)` → `BossBlindState`

#### BossBlindState
- `getTargetScore(int ante)` → `600 * ante`
- `getRewardMoney()` → `5`
- `nextState(int& ante)` → increment ante dan kembali ke `SmallBlindState`

Keuntungan State Pattern:
- extensibility mudah,
- logika blind terisolasi per kelas,
- blind progression scalable.

## 11. Skip Reward Command Pattern

### 11.1. Tujuan
Command Pattern digunakan karena skip reward:
- logic berbeda-beda,
- waktu aktivasi berbeda,
- bersifat deferred,
- memiliki efek runtime independen.

### 11.2. Core Idea
Saat blind di-skip:
`BlindState` membuat `RewardCommand` → command disimpan → dieksekusi nanti.

### 11.3. RewardCommand Interface
Contoh:
```cpp
class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void execute(RunSessionState& state) = 0;
};
```

### 11.4. Contoh Command
#### BonusHandCommand
- `getName()` → `Bonus Hand`
- `getDescription()` → `Gain +1 hand next blind.`
- `execute()` → tambah `remainingPlays`

#### FreeRerollCommand
- `getName()` → `Free Reroll`
- `getDescription()` → `Gain 1 free reroll.`
- `execute()` → tambah `freeRerolls`

### 11.5. Deferred Command System
Karena reward tidak selalu langsung aktif, command dibungkus dalam `PendingCommand`.

#### CommandTiming
enum `CommandTiming`:
- `Immediate`
- `NextBlind`
- `NextShop`
- `NextAnte`

#### PendingCommand
```cpp
struct PendingCommand {
    CommandTiming timing;
    bool executed = false;
    std::unique_ptr<RewardCommand> command;
};
```

### 11.6. Kenapa Deferred Command?
Karena beberapa reward:
- aktif nanti,
- tidak langsung dijalankan,
- harus menunggu event tertentu.

Contoh:
- `Gain +1 hand next blind`
- `Free reroll next shop`
- `Gain bonus interest next ante`

### 11.7. BlindState Membuat Command
Contoh:
```cpp
PendingCommand SmallBlindState::createSkipRewardCommand() const {
    return PendingCommand{
        CommandTiming::NextShop,
        false,
        std::make_unique<FreeRerollCommand>()
    };
}
```

### 11.8. Skip Blind Flow
Contoh:
```cpp
void RunSessionService::skipBlind(RunSessionState& state) {
    PendingCommand command = state.currentBlind->createSkipRewardCommand();
    state.pendingCommands.push_back(std::move(command));
    state.currentBlind = state.currentBlind->nextState(state.ante);
    resetBlindResources(state);
}
```

### 11.9. Execute Pending Commands
```cpp
void RunSessionService::executePendingCommands(RunSessionState& state, CommandTiming timing) {
    for (auto& pending : state.pendingCommands) {
        if (!pending.executed && pending.timing == timing) {
            pending.command->execute(state);
            pending.executed = true;
        }
    }
}
```

### 11.10. Integrasi ke Gameplay
Saat blind baru dimulai:
`executePendingCommands(state, CommandTiming::NextBlind);`

Saat shop dibuka:
`executePendingCommands(state, CommandTiming::NextShop);`

Saat ante baru dimulai:
`executePendingCommands(state, CommandTiming::NextAnte);`

### 11.11. RunSessionState
Contoh struktur:
```cpp
struct RunSessionState {
    int ante = 1;
    int totalScore = 0;
    int remainingPlays = 4;
    int remainingDiscards = 3;
    int freeRerolls = 0;
    std::unique_ptr<BlindState> currentBlind;
    std::vector<PendingCommand> pendingCommands;
};
```

## 12. Arsitektur Akhir
Flow akhir:
- `RunSessionService`
- current blind state
- player action
  - `PLAY` → resolve hand normally
  - `SKIP` → BlindState membuat RewardCommand, simpan PendingCommand, pindah state
- nanti execute pending commands
- `RewardCommand::execute()`

## 13. Keuntungan Arsitektur Baru
1. Blind system lebih modular
2. Skip reward lebih scalable
3. Deferred reward natural
4. Future-proof untuk event blind dan efek special
5. Maintainability lebih tinggi

## 14. Kesimpulan
Proposal ini memisahkan:
- blind progression → State Pattern
- reward behavior → Command Pattern
- deferred reward → Deferred Command Queue

---
Dokumen ini adalah Technical Design Document (TDD) untuk Checker Chain Balatro.
Gunakan sebagai referensi arsitektur saat mengembangkan sistem permainan dan fitur baru.
