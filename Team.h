#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include "Player.h"
using namespace std;

class Team
{
public:
	//Team();
	Team(Player& Player1, Player& Player2) : P1(Player1), P2(Player2) {};
	void setPlayer(Player& P, int numPlayer); //to modify the player 1 or 2 in the team
	Player getPlayer(int numPlayer) const;  //return the player 1 or 2
	void addPoints(int addScore);  //add points for the team
	int getScore() const; //return the score of the team
	void setScore(int newScore);  //modify the score of the team
	bool hasBet() const{ return bet; };
	void setBetBool(bool value);
	int getActualBet() const { return actualBet; };
	void setActualBet(int betValue);
	void setDealer(int numPlayer, bool value);
	bool operator==(const Team& right) const;
	bool hasPair();


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
bool Team::operator==(const Team& right) const {
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
#endif
