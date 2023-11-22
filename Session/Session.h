#ifndef SESSION__H
#define SESSION__H

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Session {

private:
    
    int games_played;
    vector<int> correct_streaks;
    vector<int> miss_streaks;
    vector<int> inputs;
    vector<int> time;
    vector<double> accuracy;
    vector<int> letters_per_minute;
    vector<int> words_per_minute;
    unordered_map<char, pair<int, int>> characters_typed; 
    unordered_map<char, pair<vector<double>, vector<double>>> character_speed;
    

public:
    Session();
    void incrementGamesPlayed();
    void addCorrectStreak(int num);
    void addMissStreak(int num);
    void addInput(int num);
    void addTime(int num);
    void addAccuracy(int num);
    void addLettersPerMinute(int num);
    void addWordsPerMinute(int num);
    

    

};

#endif