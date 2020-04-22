#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Hand.h"
using namespace std;

//------------------------------------------

class Player
{
public:
	Player();
	Player(string PlayerName) : name(PlayerName) {}
	string getName() const{ return name; };
	Hand getHand() const { return hand; };
	void setHand(Deck& deck); //set a hand of 4 cards
	void setDealer(bool value); //to set player as a dealer
	bool isDealer() const { return dealer; };
	void clearHand();
	bool operator==(const Player& right) const;
	bool haspair();
	bool hasGame();


private:
	string name;
	bool dealer = false;
	Hand hand;
	
};
//---------------------------------------------------
Player::Player(){}
//---------------------------------------------------

void Player::setHand(Deck& deck) {
		hand.drawCards(deck,4);
}
//----------------------------------------
void Player::setDealer(bool value) {
	dealer = value;
}

//------------------------------------------
void Player::clearHand() {
	hand.clear();
}
//-------------------------------------------------------------------------------------
bool Player::operator==(const Player& right) const {
	if ((name == right.getName()) && (dealer == right.isDealer()) && (hand == right.getHand()))
		return true;
	else
		return false;
}
//--------------------------------------------------------------------------------------------------
bool Player::haspair() {
	return hand.hasPair();
}
//---------------------------------------------------------------------------------------------------
bool Player::hasGame() {
	if (hand.sumHand() > 30)
		return true;
	return false;
}
#endif