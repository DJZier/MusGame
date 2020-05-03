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
	void setHand(Rank c1, Rank c2, Rank c3, Rank c4);
	void setDealer(bool value); //to set player as a dealer
	bool isDealer() const { return dealer; };
	void clearHand();
	bool operator==(const Player& right) const;
	bool operator!=(const Player& right) const;
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
//-----------------------------------------------------
void Player::setHand(Rank c1, Rank c2, Rank c3, Rank c4) {
	hand.setHand(c1, c2, c3, c4);
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
bool Player::operator==(const Player& right) const { // two players are equal if they have the same name, hand and status (here only the name would have been enough
	if ((name == right.getName()) && (dealer == right.isDealer()) && (hand == right.getHand()))
		return true;
	else
		return false;
}
//-------------------------------------------------------------------------------------
bool Player::operator!=(const Player& right) const {//if two players have different name are not equal
	if (name != right.getName())
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
	if (hand.sumHand() > 30)//if aplayer has more than 30 he has the game
		return true;
	return false;
}
#endif