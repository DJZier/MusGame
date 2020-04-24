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
        cout << "--------------------------------------------------------begin of the High lap--------------------------------------------------------" << endl;
        highPot = game.betTime();
        if (game.compareHand("high") == game.getTeam(1)) {
            cout << "Team 1 won the High lap" << endl;
        }
        else if (game.compareHand("high") == game.getTeam(2)) {
            cout << "Team 2 won the High lap" << endl;
        }
        cout << "highPot =" << highPot << endl;
        cout << "--------------------------------------------------------begin of the Low lap--------------------------------------------------------" << endl;
        int lowPot = game.betTime();
        if (game.compareHand("low") == game.getTeam(1)) {
            cout << "Team 1 won the Low lap" << endl;
        }
        else if (game.compareHand("low") == game.getTeam(2)) {
            cout << "Team 2 won the Low lap" << endl;
        }
        cout << "lowPot =" << lowPot << endl;
        cout << "--------------------------------------------------------begin of the Pair lap--------------------------------------------------------" << endl;        
        int pairPot = game.betPair();
        cout << "bien retourné quelque chose" << endl;
        if (pairPot != 0) {
            if (game.compareHand("pair") == game.getTeam(1)) {
                cout << "Team 1 won the Pair lap" << endl;
            }
            else if (game.compareHand("pair") == game.getTeam(2)) {
                cout << "Team 2 won the Pair lap" << endl;
            }
        }
        
        cout << "PairPot =" << pairPot << endl;
        cout << "--------------------------------------------------------begin of the Game lap--------------------------------------------------------" << endl;
        int Gamepot = game.betGame();
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