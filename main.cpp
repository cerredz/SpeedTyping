#include <iostream>
#include "Game/Prompt/WordList.h"
#include "Game/Game.h"
#include "Session/Session.h"
#include "SpeedTyping.h"
#include <csignal>

using namespace std;

int main() {

    WordList prompt;
    Game game;
    Session session;
    SpeedTyping speed_typing;

    speed_typing.welcome();
    speed_typing.play(prompt, game, session);
    
    return 0;
}
