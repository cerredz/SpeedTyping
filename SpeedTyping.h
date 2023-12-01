#ifndef SpeedTyping__H
#define SpeedTyping__H
#include <iostream>
#include "Game/Game.h"
#include "Game/Prompt/WordList.h"
#include "Session/Session.h"
#include "Database/Database.h"

using namespace std;

class SpeedTyping {


    public:
        void welcome();
        void play(WordList& prompt, Game& game, Session& session, Database& database);
        void tutorial(bool& go_to_game);
};








#endif