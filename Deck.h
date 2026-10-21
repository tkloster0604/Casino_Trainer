#pragma once

struct card {
    const char* suit;
    int suitN;
    int value;
};

class Deck {
    private:
        struct card* stack;
        int numOfDecks;
        int numOfCards;
        bool jokers;
        struct card* init_one();

        const char* suit_names[5] = {"JACK", "CLUB", "HEART", "DIAMOND", "JOKER"};

    public:
        Deck();
        Deck(int numOfDecks, bool jokers);

        ~Deck();

        void init_stack(int numOfDecks, bool jokers);
        void shuffle();
        void print_stack();

        void verify_shuffle();

};