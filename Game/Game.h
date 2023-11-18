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
    double left_hand_accuracy;
    double right_hand_accuracy;
    int letters_per_minute;
    int words_per_minute;
    int time_taken;
    unordered_map<char, pair<int, int>> characters_typed; // first value in pair = correct, second value = incorrect
    unordered_map<char, pair<vector<double>,vector<double>>> character_speed; 
    

public:
    Game();
    int getTotalInputs();
    int getTotalCharactersCorrect();
    int getTotalCharactersMissed();
    int getLongestCorrectStreak();
    int getLongestMissedStreak();
    double getAccuracy();
    int getLettersPerMinute();
    int getWordsPerMinute();
    int getTimeTaken();
    void printMostFrequentLetters(unordered_map<char, pair<int, int>>& map, int index);
    void printAccuracyOfLetters(unordered_map<char, pair<int, int>>& map, int index, bool b);
    void printHandAccuracy(unordered_map<char, pair<int, int>>& map);
    void PlayGame(WordList& prompt, Session& session);
    void viewGameStats();
    void viewAdvancedGameStats();
    void reportGameStats(Session& session);
    void postGameOptions();
    void clearGameStats();

    

};



#endif