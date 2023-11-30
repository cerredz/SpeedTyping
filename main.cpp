#include <iostream>
#include "Game/Prompt/WordList.h"
#include "Game/Game.h"
#include "Session/Session.h"
#include "SpeedTyping.h"
#include "Database/Database.h"
#include <csignal>

using namespace std;

int main() {

    WordList prompt;
    Game game;
    Session session;
    Database database;
    SpeedTyping speed_typing;

    speed_typing.welcome();
    speed_typing.play(prompt, game, session);
    
    return 0;
}
