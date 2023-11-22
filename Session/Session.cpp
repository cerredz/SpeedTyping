#include <iostream>
#include <vector>
#include <unordered_map>

#include "Session.h"
using namespace std;

Session::Session() {
    games_played = 0;
    correct_streaks = vector<int>();
    miss_streaks = vector<int>();
    inputs = vector<int>(); 
    accuracy = vector<double>();
    time = vector<int>();
    letters_per_minute = vector<int>();
    words_per_minute = vector<int>();
    characters_typed = unordered_map<char, pair<int, int>>();
    character_speed = unordered_map<char, pair<vector<double>, vector<double>>>();
}

