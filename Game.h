#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <algorithm>
#include "Team.h"
using namespace std;
//-----------------------------------
enum Choice {
	SEE, RAISE, FOLD
};
//-----------------------------------

class Game
{
public:
	Game(); //initialize the game
	void dealCards(Deck& deck); //give 4 cards at each player
	void shutDown(); //show the hand of all the players et clear them
	void showScore() const; 
	void setScore(int numTeam, int newScore);
	void addPoints(int numTeam, int addScore);
	Team getTeam(int numTeam) ;
	int getScoreTeam(int numTeam);
	int betTime();
	Team compareHand(string lap);
	void showAllHands() const;
	int betPair();
	int betGame();
	
private:
	vector<Player> listPlayer;
	vector<Team> team;
};
//------------------------------------------------------------
Game::Game()
{
	//gameDeck = deck;
	string J1, J2, J3, J4;
	cout << "Type the player 1's name :" << endl;
	cin >> J1;
	listPlayer.push_back(Player(J1));
	cout << "Type the player 2's name :" << endl;       // Creation of the 4 players in a vector
	cin >> J2;
	listPlayer.push_back(Player(J2));
	cout << "Type the player 3's name :" << endl;
	cin >> J3;
	listPlayer.push_back(Player(J3));
	cout << "Type the player 4's name :" << endl;
	cin >> J4;
	listPlayer.push_back(Player(J4));


	team.push_back(Team(listPlayer[0], listPlayer[2]));
	team.push_back(Team(listPlayer[1], listPlayer[3]));

	listPlayer[0].setDealer(true);  //initialization of player 1 as a dealer to set the sense of play
	cout << listPlayer[0].getName() << " is Dealer" << endl;
	cout << listPlayer[1].getName() << " begin" << endl;
		
	
}
//------------------------------------------------------------
void Game::dealCards(Deck& deck){
	deck.shuffle(1000);
	cout << "distribution des cartes..." << endl;
	/*for (Player& player : listPlayer) {
		player.setHand(deck);
		//player.getHand().showAllCards();
		player.getHand().sortHand("high");
		player.getHand().showAllCards();
	}*/

	listPlayer[0].setHand(TWO, FOUR, TWELVE, TEN);
	listPlayer[0].getHand().showAllCards();
	listPlayer[1].setHand(TWO, THREE, ELEVEN, TEN);
	listPlayer[1].getHand().showAllCards();
	listPlayer[2].setHand(TWO, TWO, FOUR, FIVE);
	listPlayer[2].getHand().showAllCards();
	listPlayer[3].setHand(TWO, TWO, FOUR, TEN);
	listPlayer[3].getHand().showAllCards();
		
	team.pop_back();
	team.pop_back();
	team.push_back(Team(listPlayer[0], listPlayer[2]));
	team.push_back(Team(listPlayer[1], listPlayer[3]));
	
}
//------------------------------------------------------------
void Game::shutDown() {
	try {
		for (Player& player : listPlayer) {
			if (player.getHand().getNumCards() != 4)
				throw string("/////////// ERROR NO ALL CARDS FOR PLAYER : " + player.getName() + " /////////////// ");
			cout << player.getName() << " :" << endl;
			player.getHand().sortHand("high");
			player.getHand().showAllCards();
			player.clearHand();
		}
	}
	catch (string const& error)
	{
		cerr << error << endl;
	}
}


//---------------------------------------------------------------------------------------------------------------------------------
void Game::showScore() const {
	cout << "Team 1's score : " << team[0].getScore() << endl;
	cout << "Team 2's score : " << team[1].getScore() << endl;
}
void Game::setScore(int numTeam, int newScore)
{
	try {
		if (numTeam == 1)
			team[0].setScore(newScore);
		else if (numTeam == 2)
			team[1].setScore(newScore);
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void Game::addPoints(int numTeam, int addScore) {
	try {
		if (numTeam == 1)
			team[0].addPoints(addScore);
		else if (numTeam == 2)
			team[1].addPoints(addScore);
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------
Team Game::getTeam(int numTeam){
	try {
		if (numTeam == 1)
			return team[0];
		else if (numTeam == 2)
			return team[1];
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------
int Game::getScoreTeam(int numTeam) {
	try {
		if (numTeam == 1)
			return team[0].getScore();
		else if (numTeam == 2)
			return team[1].getScore();
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
int Game::betTime() {
	cout << "loading bet time" << endl;
	int pot = 0;
	int it = 0;
	int indiceActualPlayer=-1;
	bool endBet = false;
	int nbpass = 0;
	team[0].setBetBool(false);
	team[1].setBetBool(false);
	team[0].setActualBet(0);
	team[1].setActualBet(0);
	for (Player& player : listPlayer) {
		it++;
		if (player.isDealer()) 
			if (it < 4) {
				indiceActualPlayer = it;
			}
			else {
				indiceActualPlayer = 0;
				it = 0;
			}		
	}
	while (endBet == false) {
		cout << "----------begin bet time---------" << endl;
		if (indiceActualPlayer == 4) {
			indiceActualPlayer = 0;
		}
		if ((listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))) { //verify if actual player is in team1
			if (team[1].hasBet()) {																													  //if yes, if opposing team has already bet, make a choice : raise see or fold				
				cout << "opposing team has bet : " << team[1].getActualBet() << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
				string answer;				
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "SEE") {
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);
						return pot;
					}
					else if (answer == "FOLD") {
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);
						return pot;
					}
					else if (answer == "RAISE") {
						cout << "How much do you want to raise ?" << endl;
						int betRaise;
						cin >> betRaise;
						pot += betRaise;
						team[0].setActualBet(betRaise);
						cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
						cout << "The pot is now : " << pot << endl;
						indiceActualPlayer++;
						team[0].setBetBool(true);
						team[1].setBetBool(false);
					}
					else {
						throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
					}
				}
				catch (string const& error)
				{
					cerr << error << endl;
				}
				
				
			}
			else if (!team[1].hasBet()) {
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
				string answer;
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "PASS") {
						indiceActualPlayer++;
						nbpass++;
						if (nbpass == 4) {
							nbpass = 0;
							endBet = true;
						}
					}
					else if (answer == "RAISE") {
						cout << "How much do you want to bet ?" << endl;
						int betRaise;
						cin >> betRaise;
						pot += betRaise;
						team[0].setActualBet(betRaise);
						cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
						cout << "The pot is now : " << pot << endl;
						indiceActualPlayer++;
						team[0].setBetBool(true);
						team[1].setBetBool(false);
					}
					else
						throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}
				
			}
		}
		else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { //verify if actual player is in team1
				if (team[0].hasBet()) {																				  //if yes, if opposing team has already bet, make a choice : raise see or fold
					cout << "opposing team has bet : " << team[0].getActualBet() << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
					string answer;
					cin >> uppercase >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
					try {
						if (answer == "SEE") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
							cout << "end bet time" << endl;
							team[1].setBetBool(false);
							return pot;
						}
						else if (answer == "FOLD") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
							cout << "end bet time" << endl;
							team[1].setBetBool(false);
							return pot;
						}
						else if (answer == "RAISE") {
							cout << "How much do you want to raise ?" << endl;
							int betRaise;
							cin >> betRaise;
							pot += betRaise;
							team[1].setActualBet(betRaise);
							cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
							cout << "The pot is now : " << pot << endl;
							indiceActualPlayer++;
							team[1].setBetBool(true);
							team[0].setBetBool(false);
						}
						else
							throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					

				}
				else if (!team[0].hasBet()) {
					cout << "nobody has bet yet" << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
					string answer;
					cin >> uppercase >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
					try {
						if (answer == "PASS") {
							indiceActualPlayer++;
							nbpass++;
							if (nbpass == 4) {
								nbpass = 0;
								endBet = true;
							}
						}
						else if (answer == "RAISE") {
							cout << "How much do you want to bet ?" << endl;
							int betRaise;
							cin >> betRaise;
							pot += betRaise;
							team[1].setActualBet(betRaise);
							cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
							cout << "The pot is now : " << pot << endl;
							indiceActualPlayer++;
							team[1].setBetBool(true);
							team[0].setBetBool(false);
						}
						else
						throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
				
				
				}
		}
	}
	cout << "end bet time" << endl;
	return pot;

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------------------
Team Game::compareHand(string lap) {
	vector<Player> ranking = listPlayer;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (ranking[j + 1].getHand() >= ranking[j].getHand()) {
				Player temp = ranking[j + 1];
				ranking[j + 1] = ranking[j];
				ranking[j] = temp;
			}
		}
	}


	if (lap == "high") {

		/*for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				if (ranking[j + 1].getHand() >= ranking[j].getHand()) {
					Player temp = ranking[j + 1];
					ranking[j + 1] = ranking[j];
					ranking[j] = temp;
				}
			}
		}*/
		if (ranking[0].operator==(team[0].getPlayer(1)) || ranking[0].operator==(team[0].getPlayer(2)))
			return team[0];
		else {
			return team[1];
		}
	}
	else if (lap == "low") {
		for (const Player& P : ranking)
			P.getHand().sortHand("low");
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				if (ranking[j + 1].getHand() < ranking[j].getHand()) {
					Player temp = ranking[j + 1];
					ranking[j + 1] = ranking[j];
					ranking[j] = temp;
				}
			}
		}
		if (ranking[0].operator==(team[0].getPlayer(1)) || ranking[0].operator==(team[0].getPlayer(2)))
			return team[0];
		else {
			return team[1];
		}
	}


	else if (lap == "pair") {
		int itmax = 0;
		int it2ndmax = 0;
		Rank secondpair1 = ACE;
		Rank secondpair2 = ACE;// they are in case of equality
		vector<Player> listPair;
		vector<int> pairValue;
		vector<Player> bestPair;
		for (Player& player : ranking) {             //we put all players with pairs in a vector
			if (player.haspair())
				listPair.push_back(player);
		}
		for (Player& player : listPair) {            //we create a vector of int corresponding to the value of the player's pair : 2=normal pair, 4=double pair, 6=three cards
			int pairVal = 0;						 //the first value of this vector is the pair of the first player in listPair and so on...
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (j == i)
						NULL;
					else {
						if (player.getHand().getCard(i)->getRank() == player.getHand().getCard(j)->getRank()) {
							pairVal++;
						}
					}
				}
			}
			pairValue.push_back(pairVal);
		}
		int max = 0;
		int nbmax = 0;
		int it = 0;
		int count = 0;
		for (int& val : pairValue) {      //we find the best kind of pair in he game and how many palyers get it. for example if 3 persons have pair, 1 has a normal pair and 2 have 
			if (val > max) {			  // three same cards max will be equal to 6 (corresponding to three same cards) ans nbmax equal to 2 (two persons have three same cards)
				max = val;
				nbmax = 1;
				it = count;
			}
			else if (val = max) {
				nbmax++;
			}
			count++;
		}

		if (nbmax == 1) {					// if only 1 person has the best kind of pair in this hand, he will automatically win so we return his team
			if (listPair[it].operator==(team[0].getPlayer(1)) || listPair[it].operator==(team[0].getPlayer(2)))
				return team[0];
			else {
				return team[1];
			}
		}
		else {
			// attention, penser à gérer les égalités !!!

			for (int i = 0; i < pairValue.size(); i++) {  //if several people have the best kind of pair, we create a vector with those players and we have to compare the pairs
				if (pairValue[i] == max)
					bestPair.push_back(listPair[i]);
			}

			int count = 0;
			Rank maxrank = ACE;
			Rank maxrank2 = ACE;
			if (max == 2 || max == 6) {      // if Best kind of pair is normal or three same, we find each pair of the players and we compare the value to know which one is the best				
				cout << "pairs are normal or three same" << endl;
				for (Player& player : bestPair) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							if (j == k)
								NULL;
							else {
								if (player.getHand().getCard(j)->getRank() == player.getHand().getCard(k)->getRank()) {
									cout << "we found the pair" << endl;
									if (player.getHand().getCard(j)->getRank() > maxrank) {
										maxrank2 = maxrank;
										maxrank = player.getHand().getCard(j)->getRank();
										it2ndmax = itmax;
										itmax = count;
									}
									else if (player.getHand().getCard(j)->getRank() == maxrank) {
										if (bestPair[itmax] != player) {
											maxrank2 = maxrank;
											maxrank = player.getHand().getCard(j)->getRank();
											it2ndmax = itmax;
											itmax = count;
										}
										cout << "maxrank = " << maxrank << ", maxrank2 = " << maxrank2 << endl;
									}									

									
								}
							}
						}
					}
					count++;
				}
				if (maxrank == maxrank2) {
					cout << "maxrank == maxrank2" << endl;
					int itdeal=0;
					int indiceActualPlayer;
					for (Player& player : listPlayer) {				//first we find the index of the dealer						
						itdeal++;
						if (player.isDealer())
							if (itdeal < 4) {
								indiceActualPlayer = itdeal;
							}
							else {
								indiceActualPlayer = 0;
								itdeal = 0;
							}
					}
					cout << "actual player is " << listPlayer[indiceActualPlayer].getName() << endl;
					//we have the index of the best players with the best equal pairs in the bestPair range
					//now we need to know their index in the listPlayer range to know which one is the closest from the dealer in the sense of the game
					for (int i = 0; i < 4; i++) { //from the dealer we find the first one whith the best pair and we return his team (--> he won the lap)
						cout << "on rentre dans le for" << endl;
						if ((listPlayer[indiceActualPlayer] == bestPair[itmax]) || (listPlayer[indiceActualPlayer] == bestPair[it2ndmax])) {
							cout << "premier if" << endl;
							if (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1)) || listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2))) {
								cout << "on retourne team1" << endl;
								return team[0];
							}
								
							else {
								cout << "on retourne team2" << endl;
								return team[1];
							}
						}
						indiceActualPlayer++;
						if (indiceActualPlayer == 4) {
							indiceActualPlayer = 0;
						}
					}
				}
			}

			else {
				
				for (Player& player : bestPair) {					// if best kind of pair is double pair, for all players...
					Rank pair1 = ACE;
					Rank pair2 = ACE;

					if (player.getHand().getCard(0)->getRank() == player.getHand().getCard(1)->getRank()) {		// ... if two first cards are equals, so value of the first pair is the value of the first cards and value of the second pair is value of the 3rd card
						if (player.getHand().getCard(0)->getRank() > player.getHand().getCard(2)->getRank()) {	// if two first cards are different,so value of the first pair is the value of the first card and value of the second pair is value of the second card

							pair1 = player.getHand().getCard(0)->getRank();										// we put the best best in pair one to compare the pairs of the players easily
							pair2 = player.getHand().getCard(2)->getRank();
						}
						else {
							pair2 = player.getHand().getCard(0)->getRank();
							pair1 = player.getHand().getCard(2)->getRank();
						}
					}
					if (pair1 > maxrank) {				// if the value of the best pair of the player is better than the actual max, so we replace the max by this value
						secondpair1 = maxrank;
						secondpair2 = maxrank2;
						maxrank = pair1;
						maxrank2 = pair2;
						it2ndmax = itmax;
						itmax = count;					// and we store the index's value of the player in itmax
					}
					else if (pair1 == maxrank) {		// if best pair of the player equal to the maxrank so we compare the second pair
						if (pair2 >= maxrank2) {
							secondpair2 = maxrank2;
							maxrank2 = pair2;
							it2ndmax = itmax;
							itmax = count;
						}
					}
					count++;
				}
				if ((secondpair1 == maxrank) && (secondpair2 == maxrank2)) {
					int itdeal=0;
					int indiceActualPlayer;
					for (Player& player : listPlayer) {				//first we find the index of the dealer
						itdeal++;
							if (player.isDealer())
								if (itdeal < 4) {
									indiceActualPlayer = itdeal;
								}
								else {
									indiceActualPlayer = 0;
									itdeal = 0;
								}
					}
					//we have the index of the best players with the best equal pairs in the bestPair range
					//now we need to know their index in the listPlayer range to know which one is the closest from the dealer in the sense of the game
					for (int i = 0; i < 4; i++) { //from the dealer we find the first one whith the best pair and we return his team (--> he won the lap)
						if ((listPlayer[indiceActualPlayer] == bestPair[itmax]) || (listPlayer[indiceActualPlayer] == bestPair[it2ndmax])) {
							if (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1)) || listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))
								return team[0];
							else {
								return team[1];
							}
						}
						indiceActualPlayer++;
						if (indiceActualPlayer == 4) {
							indiceActualPlayer = 0;
						}
					}
				}
			}
			if (bestPair[it].operator==(team[0].getPlayer(1)) || bestPair[it].operator==(team[0].getPlayer(2))) {
				return team[0];
			}				
			else {
				return team[1];
			}
		}
	}

	if (lap == "game") {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				if (ranking[j + 1].getHand().sumHand() > ranking[j].getHand().sumHand()) {
					Player temp = ranking[j + 1];
					ranking[j + 1] = ranking[j];
					ranking[j] = temp;
				}
			}
		}
		if (ranking[0].operator==(team[0].getPlayer(1)) || ranking[0].operator==(team[0].getPlayer(2)))
			return team[0];
		else {
			return team[1];
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::showAllHands() const {
	for (const Player& player : listPlayer) {
		cout << player.getName() << " :" << endl;
		player.getHand().showAllCards();
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Game::betPair() {
	int nbpair = 0;
	team[0].setBetBool(false);
	team[1].setBetBool(false);
	team[0].setActualBet(0);
	team[1].setActualBet(0);
	for (Player& player : listPlayer) {
		if (player.haspair()) {
			cout << player.getName() << " has a pair" << endl;					//a first lap to know who has pair
			nbpair++;
		}
		else {
			cout << player.getName() << " doesn't have a pair" << endl;
		}
	}

	if (team[0].hasPair() || team[1].hasPair()) {						// if one team or both have....
		if (!(team[0].hasPair() && team[1].hasPair())) {				// if only one team has pair it return -1
			if (team[0].hasPair()) {
				cout << "only Team 1 has pair" << endl;
				return -1;
			}
			if (team[1].hasPair()) {
				cout << "only Team 2 has pair" << endl;
				return -2;
			}				
		}
		cout << "both teams have pairs let's bet.." << endl;		// if both of them have pair....
		cout << "loading bet time" << endl;
		int pot = 0;
		int it = 0;
		int indiceActualPlayer = -1;
		bool endBet = false;
		int nbpass = 0;
		for (Player& player : listPlayer) {			// we initialize the actual player
			it++;
			if (player.isDealer()) {
				if (it < 4) {
					indiceActualPlayer = it;
				}
				else {
					indiceActualPlayer = 0;
					it = 0;
				}
			}				
		}
		while (endBet == false) {			//we begin a loop for betting time
			if (indiceActualPlayer == 4) {
				indiceActualPlayer = 0;
			}

			while (listPlayer[indiceActualPlayer].haspair() == false) {			//if actual player doesn't have pair, go to the next player
				if (indiceActualPlayer < 3) {
					indiceActualPlayer++;
				}
				else {
					indiceActualPlayer = 0;
					cout << listPlayer[indiceActualPlayer].getName()<< "est le joueur acuel" << endl;
				}
			}
			
				if ((listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))) { //verify if actual player is in team1
					if (team[1].hasBet()) {																													  //if yes, if opposing team has already bet, make a choice : raise see or fold				
						//cout << "opposing team has bet : " << team[1].getActualBet() << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
						string answer;
						cin >> uppercase >> answer;
						transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
						try {
							if (answer == "SEE") {	//<-------------------------------------------------------------------------------------- if player want to see, we end the loop and we return the pot
								endBet = true;
								cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
								cout << "end bet time" << endl;
								team[0].setBetBool(false);
								return pot;
							}
							else if (answer == "FOLD") {//<-------------------------------------------------------------------------------------- if player want to fold, we end the loop and we return the pot
								endBet = true;
								cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
								cout << "end bet time" << endl;
								team[0].setBetBool(false);
								return pot; // ATTENTION IL FAUDRA PEUT ETRE CREER UNE CLASSE POT POUR POUVOIR RETOURNER LEQUIPE GAGNANTE, ICI FOLD FAIT PAS PERDRE LEQUIPE
							}
							else if (answer == "RAISE") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
								cout << "How much do you want to raise ?" << endl;
								int betRaise;
								cin >> betRaise;
								pot += betRaise;
								team[0].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[0].setBetBool(true);
								team[1].setBetBool(true);
							}
							else
								throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
						}
						catch (string const& error) {
							cerr << error << endl;
						}
									

					}
					else if (!team[1].hasBet()) {					//if the opponsing team has not bet yet, we have two choices raise or pass
						cout << "nobody has bet yet" << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
						string answer;
						cin >> uppercase >> answer;
						transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
						try {
							if (answer == "PASS") {					//if the player want to pass, we just go to the next player and we increase a counter to know how many players have already pass
								indiceActualPlayer++;
								nbpass++;
								if (nbpass == nbpair) {
									nbpass = 0;
									endBet = true;
								}
							}
							else if (answer == "RAISE") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
								cout << "How much do you want to bet ?" << endl;
								int betRaise;
								cin >> betRaise;
								pot += betRaise;
								team[0].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[0].setBetBool(true);
								team[1].setBetBool(true);

							}
							else
								throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
						}
						catch (string const& error) {
							cerr << error << endl;
						}
						
						
					}
				}
				else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { // we do the same thing for team2
					if (team[0].hasBet()) {
						//cout << "opposing team has bet : " << team[0].getActualBet() << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
						string answer;
						cin >> uppercase >> answer;
						transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
						try {
							if (answer == "SEE") {
								endBet = true;
								cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
								cout << "end bet time" << endl;
								team[1].setBetBool(false);
								return pot;
							}
							else if (answer == "FOLD") {
								endBet = true;
								cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
								cout << "end bet time" << endl;
								team[1].setBetBool(false);
								return pot;
							}
							else if (answer == "RAISE") {
								cout << "How much do you want to raise ?" << endl;
								int betRaise;
								cin >> betRaise;
								pot += betRaise;
								team[1].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[1].setBetBool(true);
								team[0].setBetBool(true);
							}
							else
								throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
						}
						catch (string const& error) {
							cerr << error << endl;
						}							
					}
					else if (!team[0].hasBet()) {
						cout << "nobody has bet yet" << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
						string answer;
						cin >> uppercase >> answer;
						transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
						try {
							if (answer == "PASS") {
								indiceActualPlayer++;
								nbpass++;
								if (nbpass == nbpair) {
									nbpass = 0;
									endBet = true;
								}
							}
							else if (answer == "RAISE") {
								cout << "How much do you want to bet ?" << endl;
								int betRaise;
								cin >> betRaise;
								pot += betRaise;
								team[1].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[1].setBetBool(true);
								team[0].setBetBool(true);
							}
							else
								throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
						}
						catch (string const& error) {
							cerr << error << endl;
						}
						
					}
				}
			
		}
		cout << "end bet time" << endl;
		return pot;
	}
	cout << "nobody has pair let's play Game Lap" << endl;
	return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Game::betGame() {
	int nbgame = 0;
	team[0].setBetBool(false);
	team[1].setBetBool(false);
	team[0].setActualBet(0);
	team[1].setActualBet(0);

	for (Player& player : listPlayer) {
		if (player.hasGame()) {
			cout << player.getName() << " has a Game" << endl;					//a first lap to know who has pair
			nbgame++;
		}
		else {
			cout << player.getName() << " doesn't have a Game" << endl;
		}
	}
	if (team[0].hasGame() || team[1].hasGame()) {						// if one team or both have....
		if (!(team[0].hasGame() && team[1].hasGame())) {				// if only one team has pair it return -1
			if (team[0].hasGame()) {
				cout << "only Team 1 has Game" << endl;
				return -1;
			}
			if (team[1].hasGame()) {
				cout << "only Team 2 has Game" << endl;
				return -1;
			}
		}
		cout << "both teams have Games let's bet.." << endl;		// if both of them have pair....
		cout << "loading bet time" << endl;

		int pot = 0;
		int it = 0;
		int indiceActualPlayer = -1;
		bool endBet = false;
		int nbpass = 0;
		for (Player& player : listPlayer) {			// we initialize the actual player
			it++;
			if (player.isDealer()) {
				if (it < 4) {
					indiceActualPlayer = it;
				}
				else {
					indiceActualPlayer = 0;
					it = 0;
				}
			}
		}
		while (endBet == false) {			//we begin a loop for betting time
			if (indiceActualPlayer == 4) {
				indiceActualPlayer = 0;
			}

			while (listPlayer[indiceActualPlayer].hasGame() == false) {		//if actual player doesn't have pair, go to the next player
				if (indiceActualPlayer < 3) {
					indiceActualPlayer++;
				}
				else {
					indiceActualPlayer = 0;
					it = 0;
				}
			}

			if ((listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))) { //verify if actual player is in team1
				if (team[1].hasBet()) {																													  //if yes, if opposing team has already bet, make a choice : raise see or fold				
					//cout << "opposing team has bet : " << team[1].getActualBet() << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
					string answer;
					cin >> uppercase >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
					try {
						if (answer == "SEE") {	//<-------------------------------------------------------------------------------------- if player want to see, we end the loop and we return the pot
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot;
						}
						else if (answer == "FOLD") {//<-------------------------------------------------------------------------------------- if player want to fold, we end the loop and we return the pot
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot; // ATTENTION IL FAUDRA PEUT ETRE CREER UNE CLASSE POT POUR POUVOIR RETOURNER LEQUIPE GAGNANTE, ICI FOLD FAIT PAS PERDRE LEQUIPE
						}
						else if (answer == "RAISE") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
							cout << "How much do you want to raise ?" << endl;
							int betRaise;
							cin >> betRaise;
							pot += betRaise;
							team[0].setActualBet(betRaise);
							cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
							cout << "The pot is now : " << pot << endl;
							indiceActualPlayer++;
							team[0].setBetBool(true);
							team[1].setBetBool(true);
						}
						else
							throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					

				}
				else if (!team[1].hasBet()) {					//if the opponsing team has not bet yet, we have two choices raise or pass
					cout << "nobody has bet yet" << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
					string answer;
					cin >> uppercase >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
					try {
						if (answer == "PASS") {					//if the player want to pass, we just go to the next player and we increase a counter to know how many players have already pass
							indiceActualPlayer++;
							nbpass++;
							if (nbpass == nbgame) {
								nbpass = 0;
								endBet = true;
							}
						}
						else  if (answer == "RAISE") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
							cout << "How much do you want to bet ?" << endl;
							int betRaise;
							cin >> betRaise;
							pot += betRaise;
							team[0].setActualBet(betRaise);
							cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
							cout << "The pot is now : " << pot << endl;
							indiceActualPlayer++;
							team[0].setBetBool(true);
							team[1].setBetBool(true);
						}
						else
							throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					
				}
			}
			else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { // we do the same thing for team2
				if (team[0].hasBet()) {
					//cout << "opposing team has bet : " << team[0].getActualBet() << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
					string answer;
					cin >> uppercase >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
					try {
						if (answer == "SEE") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
							cout << "end bet time" << endl;
							team[1].setBetBool(false);
							return pot;
						}
						else if (answer == "FOLD") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
							cout << "end bet time" << endl;
							team[1].setBetBool(false);
							return pot;
						}
						else if (answer == "RAISE") {
							cout << "How much do you want to raise ?" << endl;
							int betRaise;
							cin >> betRaise;
							pot += betRaise;
							team[1].setActualBet(betRaise);
							cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
							cout << "The pot is now : " << pot << endl;
							indiceActualPlayer++;
							team[1].setBetBool(true);
							team[0].setBetBool(true);
						}
						else
							throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					

				}
				else if (!team[0].hasBet()) {
					cout << "nobody has bet yet" << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
					string answer;
					cin >> uppercase >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
					try {
						if (answer == "PASS") {
							indiceActualPlayer++;
							nbpass++;
							if (nbpass == nbgame) {
								nbpass = 0;
								endBet = true;
							}
						}
						else if (answer == "RAISE") {
							cout << "How much do you want to bet ?" << endl;
							int betRaise;
							cin >> betRaise;
							pot += betRaise;
							team[1].setActualBet(betRaise);
							cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
							cout << "The pot is now : " << pot << endl;
							indiceActualPlayer++;
							team[1].setBetBool(true);
							team[0].setBetBool(true);
						}
						else
							throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					
				}
			}

		}
		cout << "end bet time" << endl;
		return pot;
	}


	cout << "nobody has Game let's play Small Game Lap" << endl;
	cout << "loading bet time" << endl;
	int pot = 0;
	int it = 0;
	int indiceActualPlayer = -1;
	bool endBet = false;
	int nbpass = 0;
	for (Player& player : listPlayer) {		// we initialize the actual player
		it++;
		if (player.isDealer()) {
			if (it < 4) {
				indiceActualPlayer = it;
				break;
			}
			else {
				indiceActualPlayer = 0;
				it = 0;
			}
		}
	}
	while (endBet == false) {			//we begin a loop for betting time
		cout << "----------begin bet time---------" << endl;
		if (indiceActualPlayer == 4) {
			indiceActualPlayer = 0;
		}


		if ((listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))) { //verify if actual player is in team1
			if (team[1].hasBet()) {																													  //if yes, if opposing team has already bet, make a choice : raise see or fold				
				//cout << "opposing team has bet : " << team[1].getActualBet() << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
				string answer;
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "SEE") {	//<-------------------------------------------------------------------------------------- if player want to see, we end the loop and we return the pot
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);
						return pot;
					}
					else if (answer == "FOLD") {//<-------------------------------------------------------------------------------------- if player want to fold, we end the loop and we return the pot
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);
						return pot; // ATTENTION IL FAUDRA PEUT ETRE CREER UNE CLASSE POT POUR POUVOIR RETOURNER LEQUIPE GAGNANTE, ICI FOLD FAIT PAS PERDRE LEQUIPE
					}
					else if (answer == "RAISE") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
						cout << "How much do you want to raise ?" << endl;
						int betRaise;
						cin >> betRaise;
						pot += betRaise;
						team[0].setActualBet(betRaise);
						cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
						cout << "The pot is now : " << pot << endl;
						indiceActualPlayer++;
						team[0].setBetBool(true);
						team[1].setBetBool(false);
					}
					else
						throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}
				
				

			}
			else if (!team[1].hasBet()) {					//if the opponsing team has not bet yet, we have two choices raise or pass
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
				string answer;
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "PASS") {					//if the player want to pass, we just go to the next player and we increase a counter to know how many players have already pass
						indiceActualPlayer++;
						nbpass++;
						if (nbpass == 4) {
							nbpass = 0;
							endBet = true;
						}
					}
					else if (answer == "RAISE") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
						cout << "How much do you want to bet ?" << endl;
						int betRaise;
						cin >> betRaise;
						pot += betRaise;
						team[0].setActualBet(betRaise);
						cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
						cout << "The pot is now : " << pot << endl;
						indiceActualPlayer++;
						team[0].setBetBool(true);
						team[1].setBetBool(false);
					}
			else
				throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}
				
				
			}
		}
		else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { // we do the same thing for team2
			if (team[0].hasBet()) {
				//cout << "opposing team has bet : " << team[0].getActualBet() << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
				string answer;
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "SEE") {
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
						cout << "end bet time" << endl;
						team[1].setBetBool(false);
						return pot;
					}
					else if (answer == "FOLD") {
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
						cout << "end bet time" << endl;
						team[1].setBetBool(false);
						return pot;
					}
					else if (answer == "RAISE") {
						cout << "How much do you want to raise ?" << endl;
						int betRaise;
						cin >> betRaise;
						pot += betRaise;
						team[1].setActualBet(betRaise);
						cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
						cout << "The pot is now : " << pot << endl;
						indiceActualPlayer++;
						team[1].setBetBool(true);
						team[0].setBetBool(false);
					}
					else
						throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}
				
				

			}
			else if (!team[0].hasBet()) {
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
				string answer;
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "PASS") {
						indiceActualPlayer++;
						nbpass++;
						if (nbpass == 4) {
							nbpass = 0;
							endBet = true;
						}
					}
					else if (answer == "RAISE") {
						cout << "How much do you want to bet ?" << endl;
						int betRaise;
						cin >> betRaise;
						pot += betRaise;
						team[1].setActualBet(betRaise);
						cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
						cout << "The pot is now : " << pot << endl;
						indiceActualPlayer++;
						team[1].setBetBool(true);
						team[0].setBetBool(false);
					}
					else
						throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}								
			}
		}
	}
	cout << "end bet time" << endl;
	return pot;
}
#endif