#include "Deck.h"
#include "stdlib.h"
#include <cstdlib>
#include <stdio.h>

Deck::Deck() {
    init_stack(1, true);
}

Deck::Deck(int NUMDECKS, bool JOKERS) {
    init_stack(NUMDECKS, JOKERS);
}

Deck::~Deck() {
    free(stack);
}

struct card* Deck::init_one() {
    struct card* oneDeck = (card*)malloc(sizeof(card) * 54);

    int count = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j <= 13; j++) {
            oneDeck[count].suit = suit_names[i];
            oneDeck[count].suitN = i;
            oneDeck[count].value = j;
            ++count;
        }
    }

    oneDeck[52].suit = suit_names[4];
    oneDeck[52].suitN = 4;
    oneDeck[52].value = 0;
    oneDeck[53].suit = suit_names[4];
    oneDeck[53].suitN = 4;
    oneDeck[53].value = 0;

    return oneDeck;
};

void Deck::init_stack(int NUMDECKS, bool JOKERS) {
    numOfDecks = NUMDECKS;
    jokers = JOKERS;

    numOfCards = numOfDecks * ((jokers) ? 54 : 52);
    int size = ((jokers) ? 54 : 52);
    
    struct card* oneDeck = init_one();
    stack = (card*)malloc(sizeof(card) * numOfCards);
    int offset = 0;
    for (int i = 0; i < numOfDecks; i++) {
        for (int j = 0; j < size; j++) {
            stack[j + offset] = oneDeck[j];
        }
        offset += size;
    }
    free(oneDeck);
};

void Deck::shuffle() {
    struct card* shuffledStack = (card*)malloc(sizeof(card) * numOfCards);
    int* hasBeenPlaced = (int*)malloc(sizeof(int) * numOfCards);
    for (int i = 0; i < numOfCards; ++i) { 
        hasBeenPlaced[i] = 0; }

    for (int i = 0; i < numOfCards; ++i) {
        int random;
        do {
            random = rand() % numOfCards;
        } while (hasBeenPlaced[random] != 0);
        
        hasBeenPlaced[random] = 1;
        shuffledStack[random] = stack[i];
    }

    for (int i = 0; i < numOfCards; i++) { 
        stack[i] = shuffledStack[i]; }

    free(shuffledStack);
    free(hasBeenPlaced);
}

void Deck::print_stack() {
    printf("Num of decks: %i, num of cards: %i \n", numOfDecks, numOfCards);
    for (int i = 0; i < numOfCards; ++i) {
        printf("%s, %i \n", stack[i].suit, stack[i].value);
    }
};

void Deck::verify_shuffle() {
    int suitCounts[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < numOfCards; i++) {
        ++suitCounts[stack[i].suitN];
    }

    printf("Suit Distribution, %i, %i, %i, %i, %i \n", suitCounts[0], suitCounts[1], suitCounts[2], suitCounts[3], suitCounts[4]);
};