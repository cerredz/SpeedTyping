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
    game.PlayGame(prompt, session);
    
    
    return 0;
}
