#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Team.h"
#include <algorithm>
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
private:
	vector<Player> listPlayer;
	vector<Team> team;
	//Deck gameDeck;
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
	for (Player& player : listPlayer) {
		player.setHand(deck);
		player.getHand().showAllCards();
		player.getHand().sortHand("high");
		player.getHand().showAllCards();
	}
		
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
				if (answer == "see") {
					endBet = true;
					cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
					cout << "end bet time" << endl;
					team[0].setBetBool(false);
					return pot;
				}
				if (answer == "fold") {
					endBet = true;
					cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
					cout << "end bet time" << endl;
					team[0].setBetBool(false);
					return pot;
				}
				if (answer == "raise") {
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
				
			}
			else if (!team[1].hasBet()) {
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
				string answer;
				cin >> uppercase >> answer;
				if (answer == "pass") {
					indiceActualPlayer++;
					nbpass++;
					if (nbpass == 4) {
						nbpass = 0;
						endBet = true;
					}
				}
				if (answer == "raise") {
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
			}
		}
		else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { //verify if actual player is in team1
				if (team[0].hasBet()) {																				  //if yes, if opposing team has already bet, make a choice : raise see or fold
					cout << "opposing team has bet : " << team[0].getActualBet() << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
					string answer;
					cin >> uppercase >> answer;
					if (answer == "see") {
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
						cout << "end bet time" << endl;
						team[1].setBetBool(false);
						return pot;
					}
					if (answer == "fold") {
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
						cout << "end bet time" << endl;
						team[1].setBetBool(false);
						return pot;
					}
					if (answer == "raise") {
						cout << "How much do you want to raise ?" << endl;
						int betRaise;
						cin >> betRaise;
						pot += betRaise;
						cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
						cout << "The pot is now : " << pot << endl;
						indiceActualPlayer++;
team[1].setBetBool(true);
team[0].setBetBool(false);
					}

				}
				else if (!team[0].hasBet()) {
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
				string answer;
				cin >> uppercase >> answer;
				if (answer == "pass") {
					indiceActualPlayer++;
					nbpass++;
					if (nbpass == 4) {
						nbpass = 0;
						endBet = true;
					}
				}
				if (answer == "raise") {
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
				}
		}
	}
	cout << "end bet time" << endl;
	return pot;

}
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

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				if (ranking[j + 1].getHand() >= ranking[j].getHand()) {
					Player temp = ranking[j + 1];
					ranking[j + 1] = ranking[j];
					ranking[j] = temp;
				}
			}
		}
		cout << "classement des main au grand" << endl;
		for (const Player& P : ranking)
			P.getHand().showAllCards();
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
		cout << "classement des main au petit" << endl;
		for (const Player& P : ranking)
			P.getHand().showAllCards();
		if (ranking[0].operator==(team[0].getPlayer(1)) || ranking[0].operator==(team[0].getPlayer(2)))
			return team[0];
		else {
			return team[1];
		}
	}
	else if (lap == "pair") {
		vector<Player> listPair;
		vector<int> pairValue;
		for (Player& player : ranking) {
			if (player.haspair())
				listPair.push_back(player);
		}
		for (Player& player : listPair) {
			int pairVal = 0;
			for (int i = 0; i < 4 ; i++){
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
		int count=0;
		for (int& val : pairValue) {
			if (val > max) {
				max = val;
				nbmax = 1;
				it = count;
			}
			else if (val = max) {
				nbmax++;
			}
			count++;
		}

		if (nbmax == 1) {
			if (listPair[it].operator==(team[0].getPlayer(1)) || listPair[it].operator==(team[0].getPlayer(2)))
				return team[0];
			else {
				return team[1];
			}
		}
		else {
			// si pairValue[it] = 2, 4 ou 6, arriver a sortir les paires de chacun et les comparer
			// idée 1 : recréer un vecteur avec seulement les joueurs avec les mains à comparer ( ou supprimer ceux éliminés dans listPair)
			//			si paire simple -> trouver paire avec 2 boucles for, stocker valeur dans un vecteur
			//			trouver val max dans le vecteur (réutiliser pairValue), sortir l'indice et le mettre dans it
			//			si med -> de meme
			//			si double pair, faire pareil mais sortir 2 valeurs, comparer la plus grande de chaque, sinon la deuxieme
			// attention, penser à gérer les égalités !!!
		}
			

		
		if (listPair[it].operator==(team[0].getPlayer(1)) || listPair[it].operator==(team[0].getPlayer(2)))
			return team[0];
		else {
			return team[1];
		}

	}
		
}
//---------------------------------------------------------------------------------------------------------------
void Game::showAllHands() const {
	for (const Player& player : listPlayer) {
		cout << player.getName() << " :" << endl;
		player.getHand().showAllCards();
	}
}
//---------------------------------------------------------------------------------------------------------------
int Game::betPair() {
	int nbpair = 0;
	for (Player& player : listPlayer) {
		if (player.haspair()) {
			cout << player.getName() << " has a pair" << endl;
			nbpair++;
		}
		else {
			cout << player.getName() << " doesn't have a pair" << endl;
		}
	}

	if (team[0].hasPair() || team[1].hasPair()) {
		if (!(team[0].hasPair() && team[1].hasPair())) {
			if (team[0].hasPair()) {
				cout << "only Team 1 has pair" << endl;
				return -1;
			}
			if (team[1].hasPair()) {
				cout << "only Team 2 has pair" << endl;
				return -1;
			}				
		}
		cout << "both teams have pairs let's bet.." << endl;
		cout << "loading bet time" << endl;
		int pot = 0;
		int it = 0;
		int indiceActualPlayer = -1;
		bool endBet = false;
		int nbpass = 0;
		for (Player& player : listPlayer) {
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
		while (endBet == false) {
			while (listPlayer[indiceActualPlayer].haspair() == false) {
				if (it < 4) {
					indiceActualPlayer = it++;
				}

				else {
					indiceActualPlayer = 0;
					it = 0;
				}
			}
			
				if ((listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))) { //verify if actual player is in team1
					if (team[1].hasBet()) {																													  //if yes, if opposing team has already bet, make a choice : raise see or fold				
						cout << "opposing team has bet : " << team[1].getActualBet() << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
						string answer;
						cin >> uppercase >> answer;
						if (answer == "see") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot;
						}
						if (answer == "fold") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot;
						}
						if (answer == "raise") {
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

					}
					else if (!team[1].hasBet()) {
						cout << "nobody has bet yet" << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
						string answer;
						cin >> uppercase >> answer;
						if (answer == "pass") {
							indiceActualPlayer++;
							nbpass++;
							if (nbpass == nbpair) {
								nbpass = 0;
								endBet = true;
							}
						}
						if (answer == "raise") {
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
					}
				}
				else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { //verify if actual player is in team1
					if (team[0].hasBet()) {																				  //if yes, if opposing team has already bet, make a choice : raise see or fold
						cout << "opposing team has bet : " << team[0].getActualBet() << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
						string answer;
						cin >> uppercase >> answer;
						if (answer == "see") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
							cout << "end bet time" << endl;
							team[1].setBetBool(false);
							return pot;
						}
						if (answer == "fold") {
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
							cout << "end bet time" << endl;
							team[1].setBetBool(false);
							return pot;
						}
						if (answer == "raise") {
							cout << "How much do you want to raise ?" << endl;
							int betRaise;
							cin >> betRaise;
							pot += betRaise;
							cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
							cout << "The pot is now : " << pot << endl;
							indiceActualPlayer++;
							team[1].setBetBool(true);
							team[0].setBetBool(false);
						}

					}
					else if (!team[0].hasBet()) {
						cout << "nobody has bet yet" << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
						string answer;
						cin >> uppercase >> answer;
						if (answer == "pass") {
							indiceActualPlayer++;
							nbpass++;
							if (nbpass == nbpair ) {
								nbpass = 0;
								endBet = true;
							}
						}
						if (answer == "raise") {
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
					}
				}
			
		}
		cout << "end bet time" << endl;
		return pot;
	}
	cout << "nobody has pair let's play Game Lap" << endl;
	return 0;
}
#endif