#ifndef SESSION__H
#define SESSION__H

#include <iostream>
#include <unordered_map>
using namespace std;

class Session {

private:
    
    int games_played;
    int highest_accuracy;
    int worst_accuracy;
    int fastest_game_completed;
    int slowest_game_completed;
    double average_typing_speed;
    unordered_map<char, int> characters_missed; // count however many times you mistype a letter
    unordered_map<char, int> characters_typed; // count however many
    



public:

    void updateCharacterMissed(char c);
    void updateCharacterTyped(char c);

    

};

#endif