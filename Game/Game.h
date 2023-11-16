#ifndef GAME__H
#define GAME__H

#include <iostream>
#include <unordered_map>
#include "../Game/Prompt/WordList.h"
#include "../Session/Session.h"
using namespace std;

class Game {

private:
    int total_inputs;
    int total_characters_missed;
    int total_characters_correct;
    int longest_correct_streak;
    double accuracy;
    double letters_per_minute;
    int time_taken;

public:
    Game();
    int getTotalInputs();
    int getTotalCharactersCorrect();
    int getTotalCharactersMissed();
    int getLongestCorrectStreak();
    double getAccuracy();
    double getLettersPerMinute();
    int getTimeTaken();
    void PlayGame(WordList& prompt, Session& session);
    void calculateAccuracy();
    void calculateLettersPerMinute();
    void calculateTimeTaken();



};



#endif