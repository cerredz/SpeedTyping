#include <iostream>
#include <vector>
#include <unordered_map>

#include "Session.h"
using namespace std;

Session::Session() {
    games_played = 0;
    correct_streaks = vector<int>();
    miss_streaks = vector<int>();
    inputs = vector<pair<int, int>>(); 
    accuracy = vector<double>();
    time = vector<int>();
    letters_per_minute = vector<int>();
    words_per_minute = vector<int>();
    characters_typed = unordered_map<char, pair<int, int>>();
    character_speed = unordered_map<char, pair<vector<double>, vector<double>>>();
}

void Session::incrementGamesPlayed() {
    games_played++;
}

void Session::addCorrectStreak(int num) {
    correct_streaks.push_back(num);
}

void Session::addMissStreak(int num) {
    miss_streaks.push_back(num);
}

void Session::addInput(int correct, int incorrect) {
    inputs.push_back({correct, incorrect});
}

void Session::addAccuracy(int num) {
    accuracy.push_back(num);
}

void Session::addLettersPerMinute(int num) {
    letters_per_minute.push_back(num);
}

void Session::addWordsPerMinute(int num) {
    words_per_minute.push_back(num);
}

// add correct / incorrect character typed data from a game into the sesion
void Session::addCharactersTyped(const unordered_map<char, pair<int,int>>& map) {

    for(const auto& entry : map) {
        char letter = entry.first;
        int correct = entry.second.first;
        int incorrect = entry.second.second;

        if(!characters_typed.count(letter)) {
            characters_typed[letter] = {correct, incorrect};
            continue;
        }

        characters_typed[letter].first += correct;
        characters_typed[letter].second += incorrect;
    }
}

// add correct / incorrect character speed data from a game into a session
void Session::addCharacterSpeeds(const unordered_map<char, pair<vector<double>, vector<double>>>& map) {

    for(const auto& entry : map) {

        char letter = entry.first;
        vector<double> correct = entry.second.first;
        vector<double> incorrect = entry.second.second;

        for(int speed : correct) character_speed[letter].first.push_back(speed);
        for(int speed : incorrect) character_speed[letter].second.push_back(speed);
    }
 }