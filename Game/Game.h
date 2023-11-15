#ifndef GAME__H
#define GAME__H

#include <iostream>
#include <unordered_map>
#include <Game/Prompt/WordList.h>
#include <Player/Player.h>

class Game {

private:
    int total_inputs;
    int total_characters_missed;
    int longest_correct_streak;
    double accuracy;
    int typing_speed;
    unordered_map<char, int> characters_missed; // count however many times you mistype a letter
    unordered_map<char, int> characters_typed; // count however many times you typed a letter correctly

public:
    Game()
    int getTotalInput();
    int getTotalCharactersMissed();
    int getLongestCorrectStreak();
    pair<char, int> getMostFrequenctLetterMistype();
    pair<char,int> getMostFrequentVowelMistype();
    void incrementTotalInput();
    void incrementTotalCharactersMissed();
    void updateTotalCorrectStreak(int streak);
    void updateMissedCharacter(char c);
    void updateCorrectCharacter(char c);
    void PlayGame(Player& player, WordList& prompt)



}



#endif