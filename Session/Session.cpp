#include <iostream>
#include <vector>
#include <unordered_map>

#include "Session.h"
using namespace std;

Session::Session() {
    games_played = 0;
    total_playtime_seconds = 0;
    correct_streaks = vector<int>();
    total_inputs = vector<int>(); 
    accuracy = vector<double>();
    time_taken = vector<int>();
    characters_typed = unordered_map<char, pair<int, int>>();
}