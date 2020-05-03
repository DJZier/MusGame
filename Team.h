#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include "Player.h"
using namespace std;

class Team
{
public:
	//Team();
	Team(Player& Player1, Player& Player2) : P1(Player1), P2(Player2) {};//constructor which initialize P1 and P2
	void setPlayer(Player& P, int numPlayer); //to modify the player 1 or 2 in the team
	Player getPlayer(int numPlayer) const;  //return the player 1 or 2
	void addPoints(int addScore);  //add points for the team
	int getScore() const; //return the score of the team
	void setScore(int newScore);  //modify the score of the team
	bool hasBet() const{ return bet; };//return true if at least one player of the team has bet
	void setBetBool(bool value);//set bet as true or false
	int getActualBet() const { return actualBet; };
	void setActualBet(int betValue);
	void setDealer(int numPlayer, bool value);//define a player as a dealer
	bool operator==(const Team& right) const;
	bool hasPair();//return true if at least one player has a pair
	bool hasGame();//return true if at least one player has a game
	int getValTotPair();//return the value of the pairs of the player
	int getValTotGame();//return the value of the games of the player


private:
	int score = 0;
	Player& P1;
	Player& P2;
	bool bet = false;
	int actualBet = 0;
};

//------------------------------------------------------------------------------------------
void Team::setPlayer(Player& P, int numPlayer) {
	try {
		if (numPlayer == 1)
			P1 = P;
		else if (numPlayer == 2)
			P2 = P;
		else
			throw string("ERROR: NUMBER OF PLAYER INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}

}
//------------------------------------------------------------------------------------------
Player Team::getPlayer(int numPlayer) const {
	try {
		if (numPlayer == 1)
			return P1;
		else if (numPlayer == 2)
			return P2;
		else
			throw string("ERROR: NUMBER OF PLAYER INVALID, PLEASE ENTER 1 OR 2"); 
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//-----------------------------------------------------------------------------------------
void Team::addPoints(int addScore) {
	score += addScore;
}
//-------------------------------------------------------------------------------------------
int Team::getScore() const {
	return score;
}
//-------------------------------------------------------------------------------------------
void Team::setScore(int newScore) {
	score = newScore;
}
//--------------------------------------------------------------------------------------------
void Team::setBetBool(bool value) {
	if (value == true)
		bet = true;
	else if (value == false)
		bet = false;
}
//--------------------------------------------------------------------------------------------
void Team::setActualBet(int betValue) {
	actualBet = betValue;
}
//---------------------------------------------------------------------------------------------
void Team::setDealer(int numPlayer, bool value) {
	try {
		if (numPlayer == 1)
			P1.setDealer(value);
		else if (numPlayer == 2)
			P2.setDealer(value);
		else
			throw string("ERROR: NUMBER OF PLAYER INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//-----------------------------------------------------------------------------------------------
bool Team::operator==(const Team& right) const {//two teams are equal only if theirs players are the same
	if (P1.operator==(right.getPlayer(1)) && P2.operator==(right.getPlayer(2)))
		return true;
	else
		return false;
}
//----------------------------------------------------------------------------------------------
bool Team::hasPair() {
	if (P1.haspair() || P2.haspair())
		return true;
	return false;
}
//----------------------------------------------------------------------------------------------
bool Team::hasGame() {
	if (P1.hasGame() || P2.hasGame())
		return true;
	return false;
}
//----------------------------------------------------------------------------------------------
int Team::getValTotPair() {
	int ValPair=0;
	if (P1.haspair()) { //same principle as compare hand for pairs in game class
		int pairValP1 = 0;//each team we find two cards with the same value we increase a counter here pairValP1
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (j == i)
					NULL;
				else {
					if (P1.getHand().getCard(i)->getRank() == P1.getHand().getCard(j)->getRank()) {
						pairValP1++;
					}
				}
			}
		}
		if (pairValP1 == 2) { //if pairValP1 = 2 it's a simple pair and his value is 1 so we increase ValPair of 1
			ValPair ++;
		}
		else if (pairValP1 == 6) {//if pairValP1 = 6 it's a three same cards pair and his value is 2 so we increase ValPair of 2
			ValPair += 2;
		}
		else if ((pairValP1 == 4)|| (pairValP1 == 12)) {//if pairValP1 = 4 or 12 it's a double pair and his value is 3 so we increase ValPair of 3
			ValPair += 3;
		}
		
	}
	if (P2.haspair()) {
		int pairValP2 = 0;						 //same as P1
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (j == i)
					NULL;
				else {
					if (P2.getHand().getCard(i)->getRank() == P2.getHand().getCard(j)->getRank()) {
						pairValP2++;
					}
				}
			}
		}
		if (pairValP2 == 2) {
			ValPair++;
		}
		else if (pairValP2 == 6) {
			ValPair += 2;
		}
		else if ((pairValP2 == 4) || (pairValP2 == 12)) {
			ValPair += 3;
		}
	}
	return ValPair;
}

//----------------------------------------------------------------------------------------------
int Team::getValTotGame(){
	int ValGame = 0;
	if (P1.hasGame()) {//if P1 has game and has 31 we increase ValGame of 3 and 2 otherwise
		if (P1.getHand().sumHand() == 31) {
			ValGame += 3;
		}
		else {
			ValGame += 2;
		}
	}
	if (P2.hasGame()) {
		if (P2.getHand().sumHand() == 31) {
			ValGame += 3;
		}
		else {
			ValGame += 2;
		}
	}
	return ValGame;
}


#endif
