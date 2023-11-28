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
    vector<pair<int, int>> inputs; // correct, incorrect
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
    void addInput(int correct, int incorrect);
    void addTime(int num);
    void addAccuracy(int num);
    void addLettersPerMinute(int num);
    void addWordsPerMinute(int num);
    void addCharactersTyped(const unordered_map<char, pair<int, int>>& map);
    void addCharacterSpeeds(const unordered_map<char, pair<vector<double>, vector<double>>>& map);
    template <typename T>
    T getAverage(const vector<T>& nums);
    template <typename T>
    T getLowest(const vector<T>& nums);
    template <typename T>
    T getHighest(const vector<T>& nums);
    template <typename T>
    T getMedian(const vector<T>& nums);
    template <typename T>
    T getStandardDeviation(const vector<T>& nums);
    int getTotalInputs();
    int getTotalCorrect();
    int getTotalIncorrect();
    pair<int, int> getTotalTimePlayed();
    double getAccuracy();
    void stats();
    void advancedStats();

    

};

#endif