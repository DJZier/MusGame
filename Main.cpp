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
    Deck* deckptr;
    Game game;
    

    while ((game.getScoreTeam(1) < 40) && (game.getScoreTeam(2) < 40)) {
        deckptr = new Deck();
        deck = *(deckptr);
        game.dealCards(deck);
        int highPot;
        string highWin;
        cout << "--------------------------------------------------------begin of the High lap--------------------------------------------------------" << endl;
        highPot = game.betTime();
        if ((highPot > 99) && (highPot < 200)) {
            game.addPoints(2, highPot - 100);
        }
        else if (highPot > 200) {
            game.addPoints(1, highPot - 200);
        }
        else if (game.compareHand("high") == game.getTeam(1)) {
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
        if ((lowPot > 99) && (lowPot < 200)) {
            game.addPoints(2, lowPot - 100);
        }
        else if (lowPot > 200) {
            game.addPoints(1, lowPot - 200);
        }
        else if (game.compareHand("low") == game.getTeam(1)) {
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
        if ((pairPot >= 0)&&(pairPot<41)) {
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
        else if ((pairPot > 99) && (pairPot < 200)) {
            game.addPoints(2, pairPot - 100);
        }
        else if (pairPot > 200) {
            game.addPoints(1, pairPot - 200);
        }
        else if (pairPot == -100) {
            pairPot = game.getValTotPair(1);
            game.addPoints(1, pairPot);
        }
        else if (pairPot == -200) {
            pairPot = game.getValTotPair(2);
            game.addPoints(2, pairPot);
        }
        cout << pairWin << endl;
        game.showScore();
        cout << "--------------------------------------------------------begin of the Game lap--------------------------------------------------------" << endl;
        int gamePot = game.betGame();
        string gameWin;
        if ((gamePot > 0) && (gamePot<41)) {
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
        else if ((gamePot > 99) && (gamePot < 200)) {
            game.addPoints(2, gamePot-100);
        }
        else if (gamePot > 200) {
            game.addPoints(1, gamePot - 200);
        }
        else if (gamePot == 0) {
            if (game.teamHasGame(1) || game.teamHasGame(2)) {
                if (game.compareHand("game") == game.getTeam(1)) {
                    gamePot = game.getValTotGame(1);
                    game.addPoints(1, gamePot);
                    gameWin = "Team 1 won the Game lap";
                }
                else if (game.compareHand("game") == game.getTeam(2)) {
                    gamePot = game.getValTotGame(2);
                    game.addPoints(2, gamePot);
                    gameWin = "Team 2 won the Game lap";
                }
            }
            else {
                if (game.compareHand("game") == game.getTeam(1)) {
                    game.addPoints(1, 1);
                    gameWin = "Team 1 won the Game lap";
                }
                else if (game.compareHand("game") == game.getTeam(2)) {
                    game.addPoints(2, 1);
                    gameWin = "Team 2 won the Game lap";
                }
            }           
        }    
        else if (gamePot == -100) {
            gamePot = game.getValTotGame(1);
            game.addPoints(1, gamePot);
        }
        else if (gamePot == -200) {
            gamePot = game.getValTotGame(2);
            game.addPoints(2, gamePot);
        }
                          
        cout << gameWin << endl;
        game.showScore();
        game.shutDown();
        delete deckptr;
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
        return 0;
}
//-----------------------------