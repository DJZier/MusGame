#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cstdlib>
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
        system("cls");
        cout << "--------------------------------------------------------begin of the High lap--------------------------------------------------------" << endl;
        Sleep(1000);
        highPot = game.betTime();
        if ((highPot > 99) && (highPot < 200)) {
            game.addPoints(2, highPot - 100);
            highWin = "Team 2 won the high lap because Team 1 fold";
        }
        else if (highPot > 200) {
            game.addPoints(1, highPot - 200);
            highWin = "Team 2 won the high lap because Team 1 fold";
        }
        else if (highPot == 0) {
            if (game.compareHand("high") == game.getTeam(1)) {
                highWin = "Team 1 won the High lap";
                game.addPoints(1, 1);
            }
            else if (game.compareHand("high") == game.getTeam(2)) {
                highWin = "Team 2 won the High lap";
                game.addPoints(2, 1);
            }
        }
        else if (game.compareHand("high") == game.getTeam(1)) {
            highWin = "Team 1 won the High lap";
            game.addPoints(1,highPot);
        }
        else if (game.compareHand("high") == game.getTeam(2)) {
            highWin = "Team 2 won the High lap";
            game.addPoints(2,highPot);
        }
       
        system("cls");
        cout << "--------------------------------------------------------begin of the Low lap--------------------------------------------------------" << endl;
        Sleep(1000);
        int lowPot = game.betTime();
        string lowWin;
        if ((lowPot > 99) && (lowPot < 200)) {
            game.addPoints(2, lowPot - 100);
            lowWin = "Team 2 won the low lap because Team 1 fold";
        }
        else if (lowPot > 200) {
            game.addPoints(1, lowPot - 200);
            lowWin = "Team 1 won the low lap because Team 2 fold";
        }
        else if (lowPot == 0) {
            if (game.compareHand("low") == game.getTeam(1)) {
                lowWin = "Team 1 won the Low lap";
                game.addPoints(1, 1);
            }
            else if (game.compareHand("low") == game.getTeam(2)) {
                lowWin = "Team 2 won the Low lap";
                game.addPoints(2, 1);
            }
        }
        else if (game.compareHand("low") == game.getTeam(1)) {
            game.addPoints(1,lowPot);
            lowWin = "Team 1 won the Low lap";
        }
        else if (game.compareHand("low") == game.getTeam(2)) {
            game.addPoints(2,lowPot);
            lowWin = "Team 2 won the Low lap";
        }

        system("cls");
        cout << "--------------------------------------------------------begin of the Pair lap--------------------------------------------------------" << endl;  
        Sleep(1000);
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
            pairWin = "Team 2 won the pair lap because Team 1 has fold";
        }
        else if (pairPot > 200) {
            game.addPoints(1, pairPot - 200);
            pairWin = "Team 1 won the pair lap because Team 2 has fold";
        }
        else if (pairPot == -100) {
            pairPot = game.getValTotPair(1);
            game.addPoints(1, pairPot);
            pairWin = "Team 1 won the pair lap because ot's the only team with pair";
        }
        else if (pairPot == -200) {
            pairPot = game.getValTotPair(2);
            game.addPoints(2, pairPot);
            pairWin = "Team 2 won the pair lap because ot's the only team with pair";
        }
        else if (pairPot == -300) {
            pairWin = "Nobody has pair";
        }
        if (game.getScoreTeam(1) > 39) {
            cout << "<<<<<<<<<<<<<<<<<END OF THE GAME>>>>>>>>>>>>>>>>>>" << endl;
            game.showScore();
            game.shutDown();
            cout << "Team 1 Won !!!!!!!" << endl;
            return 0;
        }
        else  if (game.getScoreTeam(2) > 39) {
            cout << "<<<<<<<<<<<<<<<<<END OF THE GAME>>>>>>>>>>>>>>>>>>" << endl;
            game.showScore();
            game.shutDown();
            cout << "Team 2 Won !!!!!!!" << endl;
            return 0;
        }
        system("cls");
        cout << "--------------------------------------------------------begin of the Game lap--------------------------------------------------------" << endl;
        Sleep(1000);
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
            gameWin = "Team 2 won the game lap because Team 1 has fold";
        }
        else if (gamePot > 200) {
            game.addPoints(1, gamePot - 200);
            gameWin = "Team 1 won the game lap because Team 2 has fold";
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
            gameWin = "Team 1 won the game lap because it's the only team with game";
        }
        else if (gamePot == -200) {
            gamePot = game.getValTotGame(2);
            game.addPoints(2, gamePot);
            gameWin = "Team 2 won the game lap because it's the only team with game";
        }
        game.shutDown();
        Sleep(500);
        cout << highWin << endl;
        Sleep(500);
        cout << lowWin << endl;
        Sleep(500);
        cout << pairWin << endl;
        Sleep(500);
        cout << gameWin << endl;
        Sleep(500);
        game.showScore(); 
        Sleep(2000);
        delete deckptr;
        cout << "Next hand ? (y/n)" << endl;
        string answer;
        cin >> answer;
        if (answer == "n")
            break;
        else if (answer == "y")
            continue;
        else
            cout << "I don't understand please type y for yes and n for no"<< endl;
        
    }
    cout << "<<<<<<<<<<<<<<<<<END OF THE GAME>>>>>>>>>>>>>>>>>>" << endl;
    game.showScore();
    if (game.getScoreTeam(1) > 39) {
        cout << "Team 1 Won !!!!!!!" << endl;
    }
    else if (game.getScoreTeam(2) > 39) {
        cout << "Team 2 Won !!!!!!!" << endl;
    }

    return 0;
}
//-----------------------------