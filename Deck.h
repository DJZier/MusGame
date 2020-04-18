#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Card.h"

using namespace std;
//-----------------------------
class Deck {
public:
    Deck(); //create spanish 40-card deck
    int getNumCards() const; //return the number of cards in the deck
    Card* drawCard(); //draw the top card
    void shuffle(int nbswap); //shuffle the deck
    void clear(); //clear all cards in deck

private:
    vector<Card*> cards; //list of cards
    void swapCards(int i, int j);
};
//-----------------------------
Deck::Deck() {
    cout << "creation of a Deck..." << endl;
    for (int r = 10; r >= 1; --r)
        for (int s = 3; s >= 0; --s)
            cards.push_back(new Card((Rank)r));
}
//-----------------------------
int Deck::getNumCards() const {
    return cards.size();
}
//-----------------------------
Card* Deck::drawCard() {
    Card* cardPtr = cards.back();
    cards.pop_back();
    return cardPtr;
}
//-----------------------------
void Deck::shuffle(int nbswap) {
    cout << "shuffling Deck..." << endl;
    srand(time(NULL));
    for (int i = 0; i < nbswap; i++) {
        int tot = 39;
        swapCards(1 + (int)((float)rand() / 32767 * tot), 1 + (int)((float)rand() / 32767 * tot));
    }
}
//-----------------------------
void Deck::swapCards(int i, int j) {
    Card* temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
}
//-----------------------------
void Deck::clear() {
    cout << "Clear deck:\n";
    while (cards.size() > 0) {
        //(cards.back())->show();
        delete cards.back();
        cards.pop_back();
    }
    cout << "\n\n";
}
//-----------------------------
#endif