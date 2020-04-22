#ifndef GAME_H
#define GAME_H
#include <iostream>
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
		vector<Player> bestPair;
		for (Player& player : ranking) {             //we put all players with pairs in a vector
			if (player.haspair())
				listPair.push_back(player);
		}
		for (Player& player : listPair) {            //we create a vector of int corresponding to the value of the player's pair : 2=normal pair, 4=double pair, 6=three cards
			int pairVal = 0;						 //the first value of this vector is the pair of the first player in listPair and so on...
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
		for (int& val : pairValue) {      //we find the best kind of pair in he game and how many palyers get it. for example if 3 persons have pair, 1has a normal pair and 2 have 
			if (val > max) {			  // three same cards max will be equal to 6 (corresponding to three same cards) ans nbmax equal to 2 (to persons have three same cards)
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
			// si pairValue[it] = 2, 4 ou 6, arriver a sortir les paires de chacun et les comparer
			// id�e 1 : recr�er un vecteur avec seulement les joueurs avec les mains � comparer ( ou supprimer ceux �limin�s dans listPair)
			//			si paire simple -> trouver paire avec 2 boucles for, stocker valeur dans un vecteur
			//			trouver val max dans le vecteur (r�utiliser pairValue), sortir l'indice et le mettre dans it
			//			si med -> de meme
			//			si double pair, faire pareil mais sortir 2 valeurs, comparer la plus grande de chaque, sinon la deuxieme(juste une boucle si = continuer si diff terminer sortir les 2 valeurs
			// attention, penser � g�rer les �galit�s !!!

			for (int i = 0; i < pairValue.size(); i++) {  //if several people have the best kind of pair, we create a vector with those players and we have to compare the pairs
				if (pairValue[i] == max)
					bestPair.push_back(listPair[i]);
			}
			int itmax = 0;				// we keep the index of the best player in itmax
			int count = 0;
			Rank maxrank = ACE;
			if (max == 2 || max ==6) {      // if Best king of pair is normal or three same, we find each pair of the players and we compare the value to know which one is the best				
				for (Player& player : bestPair) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							if (j == k)
								NULL;
							else {
								if (player.getHand().getCard(j)->getRank() == player.getHand().getCard(k)->getRank()) {
									if (player.getHand().getCard(j)->getRank() > maxrank) {
										maxrank = player.getHand().getCard(j)->getRank();
										itmax = count;

									}
								}
							}
						}
					}
					count++;
				}
			}
			else {
				int maxrank2 = 1;
				for (Player& player : bestPair) {					// if best kind of pair is double pair, for all players...
					Rank pair1= ACE;
					Rank pair2=ACE;
					if (player.getHand().getCard(0)->getRank() == player.getHand().getCard(1)->getRank()) {		// ... if two first cards are equals, so value of the first pair is the value of the first cards and value of the second pair is value of the 3rd card
						if (player.getHand().getCard(0)->getRank() > player.getHand().getCard(1)->getRank()) {	// if two first cards are different,so value of the first pair is the value of the first card and value of the second pair is value of the second card
							pair1 = player.getHand().getCard(0)->getRank();										// we put the best best in pair one to compare the pairs of the players easily
							pair2 = player.getHand().getCard(2)->getRank();
						}
						else {
							pair2 = player.getHand().getCard(0)->getRank();
							pair1 = player.getHand().getCard(1)->getRank();
						}						
					}
					if (pair1 > maxrank) {				// if the value og the best pair of the player is better than the actual max, so we replace the max by this value
						maxrank = pair1;
						maxrank2 = pair2;
						itmax = count;					// and we store the index's value of the player in itmax
					}
					else if (pair1 == maxrank) {		// if best pair of the player equal to the maxrank so we compare the second pair
						if (pair2 > maxrank2) {
							maxrank2 = pair2;
							itmax = count;
						}
					}
					count++;
				}
			}
			if (bestPair[it].operator==(team[0].getPlayer(1)) || bestPair[it].operator==(team[0].getPlayer(2)))
				return team[0];
			else {
				return team[1];
			}
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
				return -1;
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

			if (it < 4) {					// careful not to be out of range 
				indiceActualPlayer = it;
			}
			else {
				indiceActualPlayer = 0;
				it = 0;
			}

			while (listPlayer[indiceActualPlayer].haspair() == false) {		//if actual player doesn't have pair, go to the next player
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
						if (answer == "see") {	//<-------------------------------------------------------------------------------------- if player want to see, we end the loop and we return the pot
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot;
						}
						if (answer == "fold") {//<-------------------------------------------------------------------------------------- if player want to fold, we end the loop and we return the pot
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot; // ATTENTION IL FAUDRA PEUT ETRE CREER UNE CLASSE POT POUR POUVOIR RETOURNER LEQUIPE GAGNANTE, ICI FOLD FAIT PAS PERDRE LEQUIPE
						}
						if (answer == "raise") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
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
					else if (!team[1].hasBet()) {					//if the opponsing team has not bet yet, we have two choices raise or pass
						cout << "nobody has bet yet" << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;
						string answer;
						cin >> uppercase >> answer;
						if (answer == "pass") {					//if the player want to pass, we just go to the next player and we increase a counter to know how many players have already pass
							indiceActualPlayer++;
							nbpass++;
							if (nbpass == nbpair) {
								nbpass = 0;
								endBet = true;
							}
						}
						if (answer == "raise") {//<-------------------------------------------------------------------------------------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
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
				else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { // we do the same thing for team2
					if (team[0].hasBet()) {
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