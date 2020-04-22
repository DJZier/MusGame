#ifndef CARD_H
#define CARD_H
#include <iostream>
using namespace std;

enum Rank {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, TEN,
    ELEVEN, TWELVE
};
//-----------------------------
class Card {
public:
    Card(Rank r) : rank(r) {};
    Rank getRank() const ;
    void show() const; //display cards onto the screen
    void swap(Card* ct); //swap two cards
    bool operator==(const Card& right) const;
private:
    Rank rank;
};
//-----------------------------
void Card::show() const {
    switch (rank) {
    case TEN: cout << "10 "; break;
    case ELEVEN: cout << "11 "; break; 
    case TWELVE: cout << "12 "; break;
    default: cout << (char)('0' + rank) << ' '; break;
    }
}
//-----------------------------
void Card::swap(Card* ct) {
    Card temp = *ct;
    *ct = *this;
    *this = temp;
}
//-----------------------------
Rank Card::getRank() const {
    return rank;
}
//---------------------------------------
bool Card::operator==(const Card& right) const {
    if (rank == right.getRank())
        return true;
    else
        return false;
}
#endif