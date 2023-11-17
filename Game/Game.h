#ifndef GAME__H
#define GAME__H

#include <iostream>
#include <unordered_map>
#include "../Game/Prompt/WordList.h"
#include "../Session/Session.h"
#include <queue>
using namespace std;

class Game {

private:
    int total_inputs;
    int total_characters_missed;
    int total_characters_correct;
    int longest_correct_streak;
    int longest_miss_streak;
    double accuracy;
    double letters_per_minute;
    int time_taken;
    unordered_map<char, pair<int, int>> characters_typed; // first value in pair = correct, second value = incorrect


public:
    Game();
    int getTotalInputs();
    int getTotalCharactersCorrect();
    int getTotalCharactersMissed();
    int getLongestCorrectStreak();
    int getLongestMissedStreak();
    double getAccuracy();
    double getLettersPerMinute();
    int getTimeTaken();
    void printMostFrequentLetters(unordered_map<char, pair<int, int>>& map, int index);
    void PlayGame(WordList& prompt, Session& session);
    void viewGameStats();
    void viewAdvancedGameStats();
    void reportGameStats(Session& session);
    void postGameOptions();
    void clearGameStats();
    

};



#endif