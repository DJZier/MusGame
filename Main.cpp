#include <iostream>
#include <iomanip>
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Game.h"

using namespace std;

//-----------------------------
int main() {
    Deck deck;
    Game game;
    

    while ((game.getScoreTeam(1) < 40) && (game.getScoreTeam(2) < 40)) {
        deck = *(new Deck());
        game.dealCards(deck);
        /*int highPot;
        string highWin;
        cout << "--------------------------------------------------------begin of the High lap--------------------------------------------------------" << endl;
        highPot = game.betTime();
        if (game.compareHand("high") == game.getTeam(1)) {
            highWin = "Team 1 won the High lap";
            game.addPoints(1,highPot);
        }
        else if (game.compareHand("high") == game.getTeam(2)) {
            highWin = "Team 2 won the High lap";
            game.addPoints(2,highPot);
        }
        cout << highWin << endl;
        game.showScore();     


        cout << "--------------------------------------------------------begin of the Low lap--------------------------------------------------------" << endl;
        int lowPot = game.betTime();
        string lowWin;
        if (game.compareHand("low") == game.getTeam(1)) {
            game.addPoints(1,lowPot);
            lowWin = "Team 1 won the Low lap";
        }
        else if (game.compareHand("low") == game.getTeam(2)) {
            game.addPoints(2,lowPot);
            lowWin = "Team 2 won the Low lap";
        }
        cout << lowWin << endl;
        game.showScore();
        cout << "--------------------------------------------------------begin of the Pair lap--------------------------------------------------------" << endl;        
        int pairPot = game.betPair();
        string pairWin;
        if (pairPot >= 0) {
            if (game.compareHand("pair") == game.getTeam(1)) {
                pairPot += game.getValTotPair(1);
                game.addPoints(1,pairPot);
                pairWin = "Team 1 won the Pair lap";
            }
            else if (game.compareHand("pair") == game.getTeam(2)) {
                pairPot += game.getValTotPair(2);
                game.addPoints(2,pairPot);
                pairWin = "Team 2 won the Pair lap";
            }
        }
        else if (pairPot == -1) {
            pairPot = game.getValTotPair(1);
            game.addPoints(1, pairPot);
        }
        else if (pairPot == -2) {
            pairPot = game.getValTotPair(2);
            game.addPoints(2, pairPot);
        }
        cout << pairWin << endl;
        game.showScore();*/
        cout << "--------------------------------------------------------begin of the Game lap--------------------------------------------------------" << endl;
        int gamePot = game.betGame();
        string gameWin;
        if (gamePot > 0) {
            if (game.compareHand("game") == game.getTeam(1)) {
                gamePot += game.getValTotGame(1);
                cout << gamePot << endl;
                game.addPoints(1, gamePot);
                gameWin = "Team 1 won the Game lap";
            }
            else if (game.compareHand("game") == game.getTeam(2)) {
                gamePot += game.getValTotGame(2);
                game.addPoints(2, gamePot);
                gameWin = "Team 2 won the Game lap";
            }
        }
        else if (gamePot == 0) {
            if (game.compareHand("game") == game.getTeam(1)) {
                game.addPoints(1, 1);
                gameWin = "Team 1 won the Game lap";
            }
            else if (game.compareHand("game") == game.getTeam(2)) {
                game.addPoints(2, 1);
                gameWin = "Team 2 won the Game lap";
            }
        }    
        else if (gamePot == -1) {
            gamePot += game.getValTotGame(1);
            game.addPoints(1, gamePot);
        }
        else if (gamePot == -2) {
            gamePot += game.getValTotGame(2);
            game.addPoints(2, gamePot);
        }
                          
        cout << gameWin << endl;
        game.showScore();
        game.shutDown();

        cout << "do you want to quit the game ? (y/n)" << endl;
        string answer;
        cin >> answer;
        if (answer == "y")
            break;
        else if (answer == "n")
            continue;
        else
            cout << "I don't understand please type y for yes and n for no"<< endl;
        
    }
}
//-----------------------------