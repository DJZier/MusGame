#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include "Team.h"
using namespace std;

//-----------------------------------

class Game
{
public:
	Game(); //initialize the game
	void dealCards(Deck& deck); //give 4 cards at each player
	void shutDown(); //show the hand of all the players and clear them
	void showScore() const; //show the score of both teams
	void setScore(int numTeam, int newScore);//set a precise score to a team
	void addPoints(int numTeam, int addScore);//add point to the score of one team
	bool teamHasGame(int numTeam);//return true if at least one of the player in the team has the game (more than 30)
	Team getTeam(int numTeam) ;//return a team
	int getScoreTeam(int numTeam);//return the score of a team
	int betTime();//this function permit to bet for the high and the low lap, it returns an int (pot) which is used to count the points
	int getValTotPair(int numteam);//return an int which correspond of number of points for a team at pair lap (for example if a team has a player with a simple card (value=1) and an other with double pair (value=3) it returns 3)
	int getValTotGame(int numteam);//same as getValTotGame but for the game (31=3 and the other are equal to 2)
	Team compareHand(string lap);//permit to define which team won the laps
	void showAllHands() const;//show all the hands of all the players
	int betPair();//same as betTime but for the pairs
	int betGame();//same as betTime but for the game
	
private:
	vector<Player> listPlayer;//this vector contain all the players, with that we can manipulate the players
	vector<Team> team;//this vector contain both teams
};
//------------------------------------------------------------
Game::Game()
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "##             ## ######### ##        ######### ######### ###   ### #########" << endl;
	cout << " ##    ###    ##  ##        ##        ##        ##     ## ## # # ## ##       " << endl;
	cout << "  ##  #####  ##   #####     ##        ##        ##     ## ##  #  ## #####    " << endl;
	cout << "   ####   ####    ##        ##        ##        ##     ## ##     ## ##       " << endl;
	cout << "    ##    ###     ######### ######### ######### ######### ##     ## #########" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "#   ### ### #  ##   ### #   ### # #    #   # #  #   ###                      " << endl;
	cout << "#   ##   #     #    ### #   #=#  #     # # # #  #   #                        " << endl;
	cout << "### ###  #    ##    #   ### # # #      #   # #### ###                        " << endl;

	cout << "Do you want to read the rules before begin to play ?(y/n)" << endl;//in case the player has never played this game, he can display the rules
	string response;	
	while ((response != "N") && (response != "Y")) {
		cin >> response;
		transform(response.begin(), response.end(), response.begin(), ::toupper);//this STL function permit to put the response in uppercase, so the player can enter the answer in lower or uppercase it doesn't matter
		try {
			if (response == "Y") {
				string filename("\\rules.txt");
				ifstream file;
				file.open(filename.c_str());

				if (file.fail()) {
					cout << "file not open !" << endl;
				}
				else {
					cout << "file open !!" << endl;	
					string line;

					while (getline(file, line)) {
						cout << line << endl;
					}
				}
			}
			else if (response == "N") {
				NULL;
			}
			else {
				throw string("ERROR: PLEASE ENTER \"o\",  OR \"y\"");
			}
		}
		catch (string const& error)
		{
			cerr << error << endl;
		}
	}
	cout << endl;
	cout << endl;
	cout << "Let's begin to play ! " << endl;
	cout << endl;
	cout << "Please enter the name of the 4th players (players 1 and 3 will be in Team 1 and players 2 and 4 will be in Team 2" << endl;
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
	Sleep(500);//it's un function in the Windows.h library, permit to have a delay of 500 millisecond
	listPlayer[0].setDealer(true);  //initialization of player 1 as a dealer to set the sense of play
	cout << listPlayer[0].getName() << " is Dealer" << endl;
	Sleep(500);
	cout << listPlayer[1].getName() << " begin" << endl;
	Sleep(500);
		
	
}
//------------------------------------------------------------
void Game::dealCards(Deck& deck){
	deck.shuffle(1000);
	/*for (Player& player : listPlayer) { //we initialize the hand of all the players and sort in desnecdant order
		player.setHand(deck);
		player.getHand().sortHand("high");
	}*/

	listPlayer[0].setHand(TEN, TEN, TEN, ACE);
	listPlayer[0].getHand().showAllCards();
	listPlayer[1].setHand(TEN, TEN, TEN, TEN);
	listPlayer[1].getHand().showAllCards();          //here if you uncomment this and comment the "for" above 
	listPlayer[2].setHand(TEN, ACE, FIVE, TWO);      //you can set the hand of the players as you want (handy to test particular cases)
	listPlayer[2].getHand().showAllCards();
	listPlayer[3].setHand(SEVEN, SEVEN, FIVE, TEN);
	listPlayer[3].getHand().showAllCards();
		

	
}
//------------------------------------------------------------
void Game::shutDown() {
	try {//function try permit to test something and display he error if there is any
		for (Player& player : listPlayer) {
			if (player.getHand().getNumCards() != 4) //verify every players have the same number of cards 
				throw string("/////////// ERROR NO ALL CARDS FOR PLAYER : " + player.getName() + " /////////////// ");
			cout << player.getName() << " :" << endl;//display the name of the player
			player.getHand().sortHand("high");//sort cards in descendant order
			player.getHand().showAllCards();//displays all the cards of the player
			player.clearHand();//then clear the hand of the player for the next hand
		}
	}
	catch (string const& error)
	{
		cerr << error << endl;//if there is an error it will display /////////// ERROR NO ALL CARDS FOR PLAYER : " + player.getName() + " /////////////// 
	}
}


//---------------------------------------------------------------------------------------------------------------------------------
void Game::showScore() const {
	cout << "scores :" << endl;
	cout << "----------------" << endl;
	cout << "| Team 1 | " << setw(4) << team[0].getScore() << "|" << endl;
	cout << "----------------" << endl;
	cout << "| Team 2 | " << setw(4) << team[1].getScore() << "|" << endl;
	cout << "----------------" << endl;
}
void Game::setScore(int numTeam, int newScore)
{
	try {
		if (numTeam == 1)
			team[0].setScore(newScore);//set score to team1
		else if (numTeam == 2)
			team[1].setScore(newScore);//set score to team2
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
			team[0].addPoints(addScore);//add score to team1
		else if (numTeam == 2)
			team[1].addPoints(addScore);//add score to team2
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
bool Game::teamHasGame(int numTeam) {
	try {
		if (numTeam == 1)
			return team[0].hasGame();//return true if team1 has the game, false if not
		else if (numTeam == 2)
			team[1].hasGame();//return true if team1 has the game, false if not
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
			return (team[0]);//return team1
		else if (numTeam == 2)
			return (team[1]);//return team2
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------
int Game::getScoreTeam(int numTeam) {
	try {
		if (numTeam == 1)
			return team[0].getScore();//return team1's score
		else if (numTeam == 2)
			return team[1].getScore();//return team2's score
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
int Game::betTime() {
	int pot = 0;//is the value returned, permite to compute the scores
	int it = 0;//an iterator used to find the actual player
	int indiceActualPlayer=-1;//variable in which the index of the actual player will be stored
	bool endBet = false;//permit to end the loop of bet, it end the BetTime
	int nbpass = 0;//this variable is increased each time someone pass
	team[0].setBetBool(false); //initialization/reset of the parameters
	team[1].setBetBool(false);//we just say : Team1 and Team2 hasn't bet, and the value of their bet = 0
	team[0].setActualBet(0);//because the bet time hasn't began yet
	team[1].setActualBet(0);//
	for (Player& player : listPlayer) { //we find the Actual player, it's the player right after the dealer
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
	while (endBet == false) { //once we have the actual player we begin the loop for bet
		if (indiceActualPlayer == 4) { //indiceActualPlayer will be increased every lap of the loop, there is 4 players (0,1,2,3) , 
			indiceActualPlayer = 0;    //so the player after the 4th player(here 3) is the first one (here 0)
		}
		if ((listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))) { //verify if actual player is in team1
			if (team[1].hasBet()) {	//if yes, if opposing team has already bet, make a choice : raise see or fold			
				system("cls");//this Windows.h libarary's function permit to clear the console so you can't see the hand of other players
				cout << "pot : " << pot << endl;	//we display the pot so the player knows the value of the pot and can make a choice			
				cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
				listPlayer[indiceActualPlayer].getHand().showAllCards();//we display his hand
				cout << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;//and we ask him to make a choice
				string answer;				
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);//transform the answer in uppercase
				try {
					if (answer == "SEE") {
						endBet = true;//the loop will end, in fact it's not really necessary because we return something
						cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);//we reset the attribute of team1
						return pot;//and return the pot
					}
					else if (answer == "FOLD") {//we do the same as for SEE
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);
						return pot+100;//we return the value of pot+100, you will understand in the main
					}
					else if (answer == "RAISE") {
						cout << "How much do you want to raise ?" << endl;
						int betRaise;
						cin >> betRaise;
						try //we use a try to be sure the value of raising is correct (not negative and not too large)
						{
							if ((betRaise > 0) && (betRaise < 40)) {//if the value is correct
								pot += betRaise;// we add the value to the pot
								team[0].setActualBet(betRaise);//set the value into the attrivute of team 1
								cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;//the end of this lap so we increase to be the next player's turn
								team[0].setBetBool(true);//so team 1 has bet
								team[1].setBetBool(false);//and team 2 not
							}
							else {
								throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
							}
						}
						catch (string const& error)
						{
							cerr << error << endl;
							Sleep(2000);
						}
						
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
			else if (!team[1].hasBet()) {//if team 2 has not bet
				system("cls");//we clear the console
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";//dispaly the hand
				listPlayer[indiceActualPlayer].getHand().showAllCards();
				cout << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/pass)" << endl;//tean 2 has not bet so only 2 choices raise of pass
				string answer;
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "PASS") {
						indiceActualPlayer++;
						nbpass++;
						if (nbpass == 4) {//if all the players have passed we end the loop and we will return a value at the end
							nbpass = 0;
							endBet = true;//end of the loop
						}
					}
					else if (answer == "RAISE") {//no change here
						cout << "How much do you want to bet ?" << endl;
						int betRaise;
						cin >> betRaise;
						try
						{
							if ((betRaise > 0) && (betRaise < 40)) {
								pot += betRaise;
								team[0].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[0].setBetBool(true);
								team[1].setBetBool(false);
							}
							else {
								throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
							}
						}
						catch (string const& error)
						{
							cerr << error << endl;
							Sleep(2000);
						}
						
					}
					else
						throw string("ERROR: PLEASE ENTER \"Raise\" OR \"Pass\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}
				
			}
		}
		else if ((listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[1].getPlayer(2)))) { //verify if actual player is in team2
				if (team[0].hasBet()) {	//if yes, if opposing team has already bet, make a choice : raise see or fold
					system("cls");// and we do exactly the same as above, but with team2
					cout << "pot : " << pot << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
					listPlayer[indiceActualPlayer].getHand().showAllCards();
					cout << endl;
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
							return pot+200;
						}
						else if (answer == "RAISE") {
							cout << "How much do you want to raise ?" << endl;
							int betRaise;
							cin >> betRaise;
							try
							{
								if ((betRaise > 0) && (betRaise < 40)) {
									pot += betRaise;
									team[1].setActualBet(betRaise);
									cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
									cout << "The pot is now : " << pot << endl;
									indiceActualPlayer++;
									team[1].setBetBool(true);
									team[0].setBetBool(false);
								}
								else {
									throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
								}
							}
							catch (string const& error)
							{
								cerr << error << endl;
								Sleep(2000);
							}
							
						}
						else
							throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					

				}
				else if (!team[0].hasBet()) {
					system("cls");
					cout << "nobody has bet yet" << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
					listPlayer[indiceActualPlayer].getHand().showAllCards();
					cout << endl;
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
							try
							{
								if ((betRaise > 0) && (betRaise < 40)) {
									pot += betRaise;
									team[1].setActualBet(betRaise);
									cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
									cout << "The pot is now : " << pot << endl;
									indiceActualPlayer++;
									team[1].setBetBool(true);
									team[0].setBetBool(false);
								}
								else {
									throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
								}
							}
							catch (string const& error)
							{
								cerr << error << endl;
								Sleep(2000);
							}
							
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
int Game::getValTotPair(int numteam) {
	try {
		if (numteam == 1)
			return team[0].getValTotPair();//return value of pairs of team 1
		else if (numteam == 2)
			return team[1].getValTotPair();//return value of pairs of team 2
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
int Game::getValTotGame(int numteam) {
	try {
		if (numteam == 1)
			return team[0].getValTotGame();//return value of games of team 1
		else if (numteam == 2)
			return team[1].getValTotGame();//return value of games of team 2
		else
			throw string("ERROR: NUMBER OF TEAM INVALID, PLEASE ENTER 1 OR 2");
	}
	catch (string const& error) {
		cerr << error << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
Team Game::compareHand(string lap) {
	vector<Player> ranking = listPlayer;//we create a vector equal to listPlayer, we can manipulate the order
	for (int i = 0; i < 4; i++) {//we sort it in descendant order with Bubble/sinking sort
		for (int j = 0; j < 3; j++) {
			if (ranking[j + 1].getHand() >= ranking[j].getHand()) {//here we can do that because we overloaded the >= operator in class hand
				Player temp = ranking[j + 1];
				ranking[j + 1] = ranking[j];
				ranking[j] = temp;
			}
		}
	}


	if (lap == "high") {//for the high lap we just return the first element of the ranking vector
		if (ranking[0].operator==(team[0].getPlayer(1)) || ranking[0].operator==(team[0].getPlayer(2)))//if the first one is in team1 
			return team[0];//we return team 1
		else {
			return team[1];//otherwise we return team 2
		}
	}
	else if (lap == "low") {
		for (const Player& P : ranking)//we sort all the hand of the players in ascendant order
			P.getHand().sortHand("low");
		for (int i = 0; i < 4; i++) {//and we sort the players in ascendant order we Bubble/sinking sort
			for (int j = 0; j < 3; j++) {
				if (ranking[j + 1].getHand() < ranking[j].getHand()) { 
					Player temp = ranking[j + 1];
					ranking[j + 1] = ranking[j];
					ranking[j] = temp;
				}
			}
		}
		if (ranking[0].operator==(team[0].getPlayer(1)) || ranking[0].operator==(team[0].getPlayer(2)))//same as above
			return team[0];
		else {
			return team[1];
		}
	}


	else if (lap == "pair") {
		int itmax = 0;//iterator to find the index of the winner
		int it2ndmax = 0;//other one
		Rank secondpair1 = ACE;
		Rank secondpair2 = ACE;// they are in case of equality
		vector<Player> listPair;//this vector will contains all the players with pairs
		vector<int> pairValue;//this vector will contain the value of pairs of the players ine the vector listPair
		vector<Player> bestPair;//this vector will contains all the players with the best pairs
		for (Player& player : listPlayer) { //we put all players with pairs in a vector
			if (player.haspair())
				listPair.push_back(player);
		}
		for (Player& player : listPair) {            //in this for loop we create a vector of int corresponding to the value of the player's pair : 
			int pairVal = 0;						 //2 = normal pair, 4 = double pair, 6 = three cards, 12 = double pair(4same cards)
			for (int i = 0; i < 4; i++) {            //the first value of this vector is the pair of the first player in listPair and so on...
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
			
			if ((pairVal == 4) || (pairVal == 12)) {  // if there is double pair, we attribute a higher value than simple pair and three same, because double pair is better than the others
				pairVal = 8;
			}
			pairValue.push_back(pairVal);
		}
		int max = 0;//will store the value of the best kinf of pair
		int nbmax = 0;//will store the number of players with the best kind of pair
		int it = 0;
		int count = 0;
		for (int& val : pairValue) {      //we find the best kind of pair in he game and how many players get it. for example if 3 persons have pair, 1 has a normal pair and 2 have 
			if (val > max) {			  // three same cards max will be equal to 6 (corresponding to three same cards) ans nbmax equal to 2 (two persons have three same cards)
				max = val;
				nbmax = 1;
				it = count;
			}
			else if (val == max) {
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
			for (int i = 0; i < pairValue.size(); i++) {  //if several people have the best kind of pair, we create a vector with those players and we have to compare the pairs
				if (pairValue[i] == max)
					cout << listPair[i].getName() << endl;
					bestPair.push_back(listPair[i]);
			}

			int count = 0;
			Rank maxrank = ACE;//permit to know the better pair
			Rank maxrank2 = ACE;//permit to know the second better pair
			if (max == 2 || max == 6) {      // if Best kind of pair is normal or three same, we find each pair of the players and we compare the value to know which one is the best				
				for (Player& player : bestPair) {//for all the players
					for (int j = 0; j < 4; j++) {//we browse 4 time the hand
						for (int k = 0; k < 4; k++) {//we time we browse the hand we browse all the cards+
							if (j == k)
								NULL;
							else {//each time 2 cards are same we increase a counter
								if (player.getHand().getCard(j)->getRank() == player.getHand().getCard(k)->getRank()) {//two cards are equal
									if (player.getHand().getCard(j)->getRank() > maxrank) {//if the actual card is better than maxrank
										maxrank2 = maxrank;//the old max rank become the second max 
										maxrank = player.getHand().getCard(j)->getRank();//the card become the new max
										it2ndmax = itmax;//store the index of the seconde best player
										itmax = count;//store the index of the best player
									}
									else if (player.getHand().getCard(j)->getRank() == maxrank) {//if the actual card is equal to maxrank
										if (bestPair[itmax] != player) {//and it's not the same player (because we browse several time the hand of players)
											maxrank2 = maxrank;//we do the same as above
											maxrank = player.getHand().getCard(j)->getRank();
											it2ndmax = itmax;
											itmax = count;
										}
									}									

									
								}
							}
						}
					}
					count++;
				}
				if (maxrank == maxrank2) {//in case of equality
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
					//we have the index of the best players with the best equal pairs in the bestPair range
					//now we need to know their index in the listPlayer range to know which one is the closest from the dealer in the sense of the game
					for (int i = 0; i < 4; i++) { //from the dealer we find the first one with the best pair and we return his team (--> he won the lap)
						if ((listPlayer[indiceActualPlayer] == bestPair[itmax]) || (listPlayer[indiceActualPlayer] == bestPair[it2ndmax])) {
							if (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1)) || listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2))) {
								return team[0];
							}
								
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
				if ((secondpair1 == maxrank) && (secondpair2 == maxrank2)) {//in case of equality
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
					for (int i = 0; i < 4; i++) { //from the dealer we find the first one with the best pair and we return his team (--> he won the lap)
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
		int indiceActualPlayer;
		int indicePlayer;
		int itdeal = 0;
		int bestGame=0;
		int indexBestGame;
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
		for (int i = 0; i < 4; i++){//the order of the best games are : 31,32 and then 40,39,38,....,33
			int sum;
			if (listPlayer[indiceActualPlayer].getHand().sumHand() == 31) {//so we assign a greater value is the game is 31
				sum = 100;
			}
			else if (listPlayer[indiceActualPlayer].getHand().sumHand() == 32) {//same for 32 plus lower than 31 because 31 is the best
				sum = 50;
			}
			else {
				sum = listPlayer[indiceActualPlayer].getHand().sumHand();
			}
			if (sum > bestGame) {//find the best game and the index of the player
				bestGame = sum;
				indexBestGame = indiceActualPlayer;
			}
			indiceActualPlayer++;//not to be out of range
			if (indiceActualPlayer == 4) {
				indiceActualPlayer = 0;
			}
		}
		if (indexBestGame == 0 || indexBestGame == 2) {//if th eindex is 0 or 2 the player is in team1 otherwise in team2
			return team[0];
		}
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
			Sleep(500);
		}
		else {
			cout << player.getName() << " doesn't have a pair" << endl;
			Sleep(500);
		}
	}
	

	if (team[0].hasPair() || team[1].hasPair()) {						// if one team or both have....
		if (!(team[0].hasPair() && team[1].hasPair())) {				// if only team1 has pair it return -100 (it's to calculate in the main)
			if (team[0].hasPair()) {
				cout << "only Team 1 has pair" << endl;
				Sleep(2000);
				return -100;
			}
			if (team[1].hasPair()) {								// if only team2 has pair it return -200 (it's to calculate in the main)
				cout << "only Team 2 has pair" << endl;
				Sleep(2000);
				return -200;
			}				
		}
		cout << "both teams have pairs let's bet.." << endl;		// if both of them have pair....
		cout << "loading bet time" << endl;
		Sleep(3000);
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
			//here is the same principle of betTime
				if ((listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(1))) || (listPlayer[indiceActualPlayer].operator==(team[0].getPlayer(2)))) { //verify if actual player is in team1
					if (team[1].hasBet()) {																													  //if yes, if opposing team has already bet, make a choice : raise see or fold				
						system("cls");
						cout << "pot : " << pot << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
						listPlayer[indiceActualPlayer].getHand().showAllCards();
						cout << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
						string answer;
						cin >> uppercase >> answer;
						transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
						try {
							if (answer == "SEE") {	//<-------------- if player want to see, we end the loop and we return the pot
								endBet = true;
								cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
								cout << "end bet time" << endl;
								team[0].setBetBool(false);
								return pot;
							}
							else if (answer == "FOLD") {//<---------- if player want to fold, we end the loop and we return the pot
								endBet = true;
								cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
								cout << "end bet time" << endl;
								team[0].setBetBool(false);
								return pot+100;
							}
							else if (answer == "RAISE") {//<--------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
								cout << "How much do you want to raise ?" << endl;
								int betRaise;
								cin >> betRaise;
								try
								{
									if ((betRaise > 0) && (betRaise < 40)) {
										pot += betRaise;
										team[0].setActualBet(betRaise);
										cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
										cout << "The pot is now : " << pot << endl;
										indiceActualPlayer++;
										team[0].setBetBool(true);
										team[1].setBetBool(true);
									}
									else {
										throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
									}
								}
								catch (string const& error)
								{
									cerr << error << endl;
									Sleep(2000);
								}
								
							}
							else
								throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
						}
						catch (string const& error) {
							cerr << error << endl;
						}
									

					}
					else if (!team[1].hasBet()) {					//if the opponsing team has not bet yet, we have two choices raise or pass
						system("cls");
						cout << "nobody has bet yet" << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
						listPlayer[indiceActualPlayer].getHand().showAllCards();
						cout << endl;
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
							else if (answer == "RAISE") {//<-------if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
								cout << "How much do you want to bet ?" << endl;
								int betRaise;
								cin >> betRaise;
								try
								{
									if ((betRaise > 0) && (betRaise < 40)) {
										pot += betRaise;
										team[0].setActualBet(betRaise);
										cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
										cout << "The pot is now : " << pot << endl;
										indiceActualPlayer++;
										team[0].setBetBool(true);
										team[1].setBetBool(true);
									}
									else {
										throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
									}
								}
								catch (string const& error)
								{
									cerr << error << endl;
									Sleep(2000);
								}
								

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
						system("cls");
						cout << "pot : " << pot << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
						listPlayer[indiceActualPlayer].getHand().showAllCards();
						cout << endl;
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
								return pot+200;
							}
							else if (answer == "RAISE") {
								cout << "How much do you want to raise ?" << endl;
								int betRaise;
								cin >> betRaise;
								try
								{
									if ((betRaise > 0) && (betRaise < 40)) {
										pot += betRaise;
										team[1].setActualBet(betRaise);
										cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
										cout << "The pot is now : " << pot << endl;
										indiceActualPlayer++;
										team[1].setBetBool(true);
										team[0].setBetBool(true);
									}
									else {
										throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
									}
								}
								catch (string const& error)
								{
									cerr << error << endl;
									Sleep(2000);
								}
								
							}
							else
								throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
						}
						catch (string const& error) {
							cerr << error << endl;
						}							
					}
					else if (!team[0].hasBet()) {
						system("cls");
						cout << "nobody has bet yet" << endl;
						cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
						listPlayer[indiceActualPlayer].getHand().showAllCards();
						cout << endl;
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
								try
								{
									if ((betRaise > 0) && (betRaise < 40)) {
										pot += betRaise;
										team[1].setActualBet(betRaise);
										cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
										cout << "The pot is now : " << pot << endl;
										indiceActualPlayer++;
										team[1].setBetBool(true);
										team[0].setBetBool(true);
									}
									else {
										throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
									}
								}
								catch (string const& error)
								{
									cerr << error << endl;
									Sleep(2000);
								}
								
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
	Sleep(2000);
	return -300;
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
			cout << player.getName() << " has a Game" << endl;					//a first lap to know who has game
			nbgame++;
			Sleep(500);
		}
		else {
			cout << player.getName() << " doesn't have a Game" << endl;
			Sleep(500);
		}
	}
	if (team[0].hasGame() || team[1].hasGame()) {						// if one team or both have....
		if (!(team[0].hasGame() && team[1].hasGame())) {				// if only team 1 has game it return -100
			if (team[0].hasGame()) {
				cout << "only Team 1 has Game" << endl;
				Sleep(2000);
				return -100;
			}
			if (team[1].hasGame()) {
				cout << "only Team 2 has Game" << endl;
				Sleep(2000);
				return -200;
			}
		}
		cout << "both teams have Games let's bet.." << endl;		// if both of them have game....
		cout << "loading bet time" << endl;
		Sleep(3000);
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

			while (listPlayer[indiceActualPlayer].hasGame() == false) {		//if actual player doesn't have game, go to the next player
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
					system("cls");
					cout << "pot : " << pot << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
					listPlayer[indiceActualPlayer].getHand().showAllCards();
					cout << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
					string answer;
					cin >> uppercase >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
					try {
						if (answer == "SEE") {	//<------------ if player want to see, we end the loop and we return the pot
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot;
						}
						else if (answer == "FOLD") {//<----------- if player want to fold, we end the loop and we return the pot
							endBet = true;
							cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
							cout << "end bet time" << endl;
							team[0].setBetBool(false);
							return pot+100; 
						}
						else if (answer == "RAISE") {//<------ if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
							cout << "How much do you want to raise ?" << endl;
							int betRaise;
							cin >> betRaise;
							try
							{
								if ((betRaise > 0) && (betRaise < 40)) {
									pot += betRaise;
									team[0].setActualBet(betRaise);
									cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
									cout << "The pot is now : " << pot << endl;
									indiceActualPlayer++;
									team[0].setBetBool(true);
									team[1].setBetBool(true);
								}
								else {
									throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
								}
							}
							catch (string const& error)
							{
								cerr << error << endl;
								Sleep(2000);
							}
							
						}
						else
							throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					

				}
				else if (!team[1].hasBet()) {					//if the opponsing team has not bet yet, we have two choices raise or pass
					system("cls");
					cout << "nobody has bet yet" << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
					listPlayer[indiceActualPlayer].getHand().showAllCards();
					cout << endl;
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
						else  if (answer == "RAISE") {//<------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
							cout << "How much do you want to bet ?" << endl;
							int betRaise;
							cin >> betRaise;
							try
							{
								if ((betRaise > 0) && (betRaise < 40)) {
									pot += betRaise;
									team[0].setActualBet(betRaise);
									cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
									cout << "The pot is now : " << pot << endl;
									indiceActualPlayer++;
									team[0].setBetBool(true);
									team[1].setBetBool(true);
								}
								else {
									throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
								}
							}
							catch (string const& error)
							{
								cerr << error << endl;
								Sleep(2000);
							}
							
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
					system("cls");
					cout << "pot : " << pot << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
					listPlayer[indiceActualPlayer].getHand().showAllCards();
					cout << endl;
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
							return pot+200;
						}
						else if (answer == "RAISE") {
							cout << "How much do you want to raise ?" << endl;
							int betRaise;
							cin >> betRaise;
							try
							{
								if ((betRaise > 0) && (betRaise < 40)) {
									pot += betRaise;
									team[1].setActualBet(betRaise);
									cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
									cout << "The pot is now : " << pot << endl;
									indiceActualPlayer++;
									team[1].setBetBool(true);
									team[0].setBetBool(true);
								}
								else {
									throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
								}
							}
							catch (string const& error)
							{
								cerr << error << endl;
								Sleep(2000);
							}
							
						}
						else
							throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
					}
					catch (string const& error) {
						cerr << error << endl;
					}
					
					

				}
				else if (!team[0].hasBet()) {
					system("cls");
					cout << "nobody has bet yet" << endl;
					cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
					listPlayer[indiceActualPlayer].getHand().showAllCards();
					cout << endl;
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
							try
							{
								if ((betRaise > 0) && (betRaise < 40)) {
									pot += betRaise;
									team[1].setActualBet(betRaise);
									cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
									cout << "The pot is now : " << pot << endl;
									indiceActualPlayer++;
									team[1].setBetBool(true);
									team[0].setBetBool(true);
								}
								else {
									throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
								}
							}
							catch (string const& error)
							{
								cerr << error << endl;
								Sleep(2000);
							}
							
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
	Sleep(2000);
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
				system("cls");
				cout << "pot : " << pot << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
				listPlayer[indiceActualPlayer].getHand().showAllCards();
				cout << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " what do you do ? (raise/see/fold)" << endl;
				string answer;
				cin >> uppercase >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				try {
					if (answer == "SEE") {	//<--------------if player want to see, we end the loop and we return the pot
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " want to see at the end of the hand" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);
						return pot;
					}
					else if (answer == "FOLD") {//<---------if player want to fold, we end the loop and we return the pot
						endBet = true;
						cout << listPlayer[indiceActualPlayer].getName() << " is fold" << endl;
						cout << "end bet time" << endl;
						team[0].setBetBool(false);
						return pot+100; 
					}
					else if (answer == "RAISE") {//<-------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
						cout << "How much do you want to raise ?" << endl;
						int betRaise;
						cin >> betRaise;
						try
						{
							if ((betRaise > 0) && (betRaise < 40)) {
								pot += betRaise;
								team[0].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[0].setBetBool(true);
								team[1].setBetBool(false);
							}
							else {
								throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
							}
						}
						catch (string const& error)
						{
							cerr << error << endl;
							Sleep(2000);
						}
						
					}
					else
						throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}
				
				

			}
			else if (!team[1].hasBet()) {					//if the opponsing team has not bet yet, we have two choices raise or pass
				system("cls");
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
				listPlayer[indiceActualPlayer].getHand().showAllCards();
				cout << endl;
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
					else if (answer == "RAISE") {//<-------- if player want to raise, we ask how much, store the value in variable, add this value to the pot, and go to the next player and we say "now the team1 has bet and not the team2"
						cout << "How much do you want to bet ?" << endl;
						int betRaise;
						cin >> betRaise;
						try
						{
							if ((betRaise > 0) && (betRaise < 40)) {
								pot += betRaise;
								team[0].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[0].setBetBool(true);
								team[1].setBetBool(false);
							}
							else {
								throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
							}
						}
						catch (string const& error)
						{
							cerr << error << endl;
							Sleep(2000);
						}
						
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
				system("cls");
				cout << "pot : " << pot << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
				listPlayer[indiceActualPlayer].getHand().showAllCards();
				cout << endl;
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
						return pot+200;
					}
					else if (answer == "RAISE") {
						cout << "How much do you want to raise ?" << endl;
						int betRaise;
						cin >> betRaise;
						try
						{
							if ((betRaise > 0) && (betRaise < 40)) {
								pot += betRaise;
								team[1].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " raised " << betRaise << " more " << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[1].setBetBool(true);
								team[0].setBetBool(false);
							}
							else {
								throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
							}
						}
						catch (string const& error)
						{
							cerr << error << endl;
							Sleep(2000);
						}
						
					}
					else
						throw string("ERROR: PLEASE ENTER \"See\", \"Raise\" OR \"fold\"");
				}
				catch (string const& error) {
					cerr << error << endl;
				}
				
				

			}
			else if (!team[0].hasBet()) {
				system("cls");
				cout << "nobody has bet yet" << endl;
				cout << listPlayer[indiceActualPlayer].getName() << " here your hand : ";
				listPlayer[indiceActualPlayer].getHand().showAllCards();
				cout << endl;
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
						try
						{
							if ((betRaise > 0) && (betRaise < 40)) {
								pot += betRaise;
								team[1].setActualBet(betRaise);
								cout << listPlayer[indiceActualPlayer].getName() << " bet " << betRaise << endl;
								cout << "The pot is now : " << pot << endl;
								indiceActualPlayer++;
								team[1].setBetBool(true);
								team[0].setBetBool(false);
							}
							else {
								throw string("ERROR: PLEASE ENTER AN INTEGER BETWEEN 0 AND 40");
							}
						}
						catch (string const& error)
						{
							cerr << error << endl;
							Sleep(2000);
						}
						
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
	cout << "pot = " << pot << endl;
	cout << "end bet time" << endl;
	return pot;
}
#endif