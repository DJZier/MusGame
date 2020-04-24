#include <iostream>
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Game.h"

using namespace std;

//-----------------------------
int main() {
    Deck deck;
    Game game;
    game.dealCards(deck);

    while ((game.getScoreTeam(1) < 40) && (game.getScoreTeam(2) < 40)) {
        int highPot;
        string highWin;
        cout << "--------------------------------------------------------begin of the High lap--------------------------------------------------------" << endl;
        highPot = game.betTime();
        if (game.compareHand("high") == game.getTeam(1)) {
            highWin = "Team 1 won the High lap";
            game.getTeam(1).addPoints(highPot);
        }
        else if (game.compareHand("high") == game.getTeam(2)) {
            highWin = "Team 2 won the High lap";
            game.getTeam(2).addPoints(highPot);
        }
        cout << "highPot =" << highPot << endl;
        cout << "--------------------------------------------------------begin of the Low lap--------------------------------------------------------" << endl;
        int lowPot = game.betTime();
        string lowWin;
        if (game.compareHand("low") == game.getTeam(1)) {
            game.getTeam(1).addPoints(lowPot);
            lowWin = "Team 1 won the Low lap";
        }
        else if (game.compareHand("low") == game.getTeam(2)) {
            game.getTeam(2).addPoints(lowPot);
            lowWin = "Team 2 won the Low lap";
        }
        cout << "lowPot =" << lowPot << endl;
        cout << "--------------------------------------------------------begin of the Pair lap--------------------------------------------------------" << endl;        
        int pairPot = game.betPair();
        string pairWin;
        if (pairPot != 0) {
            if (game.compareHand("pair") == game.getTeam(1)) {
                game.getTeam(1).addPoints(pairPot);
                pairWin = "Team 1 won the Pair lap";
            }
            else if (game.compareHand("pair") == game.getTeam(2)) {
                game.getTeam(2).addPoints(pairPot);
                pairWin = "Team 2 won the Pair lap";
            }
        }
        
        cout << "PairPot =" << pairPot << endl;
        cout << "--------------------------------------------------------begin of the Game lap--------------------------------------------------------" << endl;
        int gamePot = game.betGame();
        string gameWin;
        if (gamePot != 0) {
            if (game.compareHand("game") == game.getTeam(1)) {
                game.getTeam(1).addPoints(gamePot);
                gameWin = "Team 1 won the Game lap";
            }
            else if (game.compareHand("game") == game.getTeam(2)) {
                game.getTeam(2).addPoints(gamePot);
                gameWin = "Team 2 won the Game lap";
            }
        }
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