#include <iostream>
#include "../Session/Session.h"
#include "../Game/Prompt/WordList.h"
#include "../Game/Game.h"
#include <unordered_map>
#include <chrono>
#include <conio.h>



using namespace std;

// default constructor for a Game object
Game::Game() {

    total_inputs = 0;
    total_characters_missed = 0;
    longest_correct_streak = 0;
    accuracy = 0.0;
    letters_per_minute = 0;
    time_taken = 0;
}


// helper functions
int Game::getTotalInputs() {
    return total_inputs;
}

int Game::getTotalCharactersCorrect() {
    return total_characters_correct;
}
int Game::getTotalCharactersMissed() {
    return total_characters_missed;
}

int Game::getLongestCorrectStreak() {
    return longest_correct_streak;
}

double Game::getAccuracy() {
    return accuracy;
}

double Game::getLettersPerMinute() {
    return letters_per_minute;
}

int Game::getTimeTaken() {
    return time_taken;
}

// actual user playing the game function
void Game::PlayGame(WordList& prompt, Session& session) {

    auto start = chrono::high_resolution_clock::now();
    prompt.printWordList();

    int index = 0;
    int correct_streak = 0;

    // while user have not typed all letters
    while(index < prompt.getSize()) {

        
        char user_input;
        user_input = _getch();
        bool correct_character_input = prompt.checkCharInput(user_input, index);
        
        if(correct_character_input) 
        {
            // correct user input
            total_characters_correct += 1;
            correct_streak += 1;
            prompt.printLetter(index);
            index++;

        } else {
            // incorrect user input
            correct_streak = 0;
            total_characters_missed += 1;
        }

        total_inputs++;
        longest_correct_streak = max(longest_correct_streak, correct_streak);
    }
    
}

