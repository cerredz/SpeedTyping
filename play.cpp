#include <iostream>
#include "Game/Prompt/WordList.h"
#include "Game/Game.h"
#include "Session/Session.h"
#include <csignal>

using namespace std;

int main() {

    WordList prompt;
    Game game;
    Session session;
    //g++ Game/Prompt/WordList.cpp Game/Prompt/Sentences.cpp Game/Game.cpp Session/Session.cpp play.cpp -o play
    
    string user_input;
    cout << "Enter The Number 1 to continue playing:: " << endl;
    cin >> user_input;
    while(user_input == "1") {
        game.PlayGame(prompt, session);
    }
    
    game.reportGameStats(session); // report game stats to the session stats
    //clearGameStats();
   // postGameOptions();
    
    //game.viewGameStats();
    //game.viewAdvancedGameStats();
    sesison.stats();
    return 0;
}
