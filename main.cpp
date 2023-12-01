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
    speed_typing.play(prompt, game, session, database);
    // g++ Game/Prompt/WordList.cpp Game/Prompt/Sentences.cpp Game/Game.cpp Session/Session.cpp SpeedTyping.cpp Database/Database.cpp Database/DataReader/DataReader.cpp Database/DataWriter/DataWriter.cpp main.cpp -o main
    
    return 0;
}
