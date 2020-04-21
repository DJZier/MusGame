#ifndef HAND_H
#define HAND_H
#include <iostream>
#include <vector>
#include "Deck.h"
using namespace std;
//-----------------------------
class Hand {
public:
    void drawCards(Deck& deck, int num); //draw n cards
    void showAllCards() const; //show all cards in hand
    void clear(); //clear all cards in hand
    int getNumCards() const; //get the number of cards in the hand
    bool operator==(const Hand& right) const;
    bool operator>=(const Hand & right) const;
    bool operator<(const Hand& right) const;
    Card* getCard(int numCard) const { return cards[numCard]; };
    void sortHand(string order);
    bool hasPair();
private:
    vector<Card*> cards;
};
//-----------------------------
void Hand::drawCards(Deck& deck, int num) {
    for (int n = 0; n < num; ++n) {
        if (deck.getNumCards() > 0)
            cards.push_back(deck.drawCard());
    }
}

//-----------------------------
void Hand::showAllCards() const {
    for (size_t i = 0; i < cards.size(); ++i) {
        cards[i]->Card::show();
    }
    cout << "\n";
}
//-----------------------------
void Hand::clear() {
    //cout << "Clear hand:\n";
    while (cards.size() > 0) {
        //(cards.back())->show();
        delete cards.back();
        cards.pop_back();
    }
    //cout << "\n\n";
}
//-----------------------------
int Hand::getNumCards() const {
    return cards.size();
}
//----------------------------------------------------
bool Hand::operator==(const Hand& right) const {
    bool sameHand = false;
    for (int i = 0; i < 4; i++) {
        if (cards[i] == right.getCard(i)) 
            sameHand = true;
        else {
            sameHand = false;
            return sameHand;
        }
    }
    return sameHand;
}
//------------------------------------------------------
void Hand::sortHand(string order) {
    if (order == "high") {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (cards[j]->getRank() < cards[j + 1]->getRank())
                    cards[j]->swap(cards[j + 1]);
            }
        }
    }
    else if (order == "low") {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (cards[j]->getRank() > cards[j + 1]->getRank())
                    cards[j]->swap(cards[j + 1]);
            }
        }
    }
    
}
//------------------------------------------------------
bool Hand::operator>=(const Hand& right) const {
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i]->getRank() > right.getCard(i)->getRank())
            return true;
        if (cards[i]->getRank() < right.getCard(i)->getRank())
            return false;
    }    
}
//---------------------------------------------------------
bool Hand::operator<(const Hand& right) const {
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i]->getRank() < right.getCard(i)->getRank())
            return true;
        if (cards[i]->getRank() > right.getCard(i)->getRank())
            return false;
    }
}
//-----------------------------------------------------------
bool Hand::hasPair() {
    for (size_t i = 0; i < cards.size(); ++i) {
        for (size_t j = 0; j < cards.size(); j++) {
            if (i != j) {
                if (cards[i]->getRank() == cards[j]->getRank())
                    return true;
            }
        }
    }
    return false;
}
#endif