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
    
    string user_input = "1";

    while(user_input == "1") {
        cout << "Enter The Number 1 to continue playing:: " << endl;
        cin >> user_input;
        string new_prompt = prompt.generatePrompt();
        prompt.convertStringToWordList(new_prompt);

        game.PlayGame(prompt, session);
        game.viewGameStats();
        game.clearGameStats();
        cout << endl;
    }
    
     // report game stats to the session stats
        //clearGameStats();
    // postGameOptions();
    
    
    session.stats();
    session.advancedStats();
    return 0;
}
