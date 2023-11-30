#ifndef SpeedTyping__H
#define SpeedTyping__H
#include <iostream>
#include "Game/Game.h"
#include "Game/Prompt/WordList.h"
#include "Session/Session.h"

using namespace std;

class SpeedTyping {


    public:
        void welcome();
        void play(WordList& prompt, Game& game, Session& session);
        void tutorial();

};








#endif