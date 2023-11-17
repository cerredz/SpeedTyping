#ifndef SESSION__H
#define SESSION__H

#include <iostream>
#include <unordered_map>
using namespace std;

class Session {

private:
    Session();
    int games_played;
    int total_playtime_seconds;
    vector<int> correct_streaks;
    vector<int> total_inputs;
    vector<double> accuracy;
    vector<int> time_taken;
    vector<double> typing_speed;
    unordered_map<char, pair<int, int>> characters_typed; // count however many
    

public:

    void updateCharacterMissed(char c);
    void updateCharacterTyped(char c);

    

};

#endif