#include <iostream>
#include "../Session/Session.h"
#include "../Game/Prompt/WordList.h"
#include "../Game/Game.h"
#include <unordered_map>
#include <priority_queue>
#include <chrono>
#include <conio.h>



using namespace std;

// default constructor for a Game object
Game::Game() {

    total_inputs = 0;
    total_characters_missed = 0;
    longest_correct_streak = 0;
    longest_miss_streak = 0;
    accuracy = 0.0;
    letters_per_minute = 0;
    time_taken = 0;
    characters_typed = unordered_map<char,pair<int, int>>();

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

int Game::getLongestMissedStreak() {
    return longest_miss_streak;
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

// print the correct / incorrect letter data
void Game::printLetterFrequencies() {

    struct CompareChars {
    bool operator()(const pair<char, pair<int, int>>& lhs, const pair<char, pair<int, int>>& rhs) const {
        return lhs.first > rhs.first;  // Change > to < for min heap
        }
    };

    priority_queue<pair<char, pair<int, int>>, vector<pair<char, pair<int, int>>>, CompareChars> sorted_letters;
    
    // sort the letters alphabetically
    for(auto entry : characters_typed) {

        char letter = entry.first;
        int correct = entry.second.first;
        int incorrect = entry.second.second;

        sorted_letters.push({letter, {correct, incorrect}});
    }

    cout << "| Character | Correctly Typed | Incorrectly Typed | " << endl;
    // print the letter data
    while(!sorted_letters.empty()) {
        pair<char, pair<int, int>> current_letter_data;
        sorted_letters.pop();

        char letter = current_letter_data.first;
        int correct = current_letter_data.second.first;
        int incorrect = correc_letter_data.second.second;
    }

    

}

// actual user playing the game function
void Game::PlayGame(WordList& prompt, Session& session) {

    auto start = chrono::high_resolution_clock::now();
    prompt.printWordList();

    int index = 0;
    int correct_streak = 0, miss_streak = 0;

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
            miss_streak = 0;
            prompt.printLetter(index);
            index++;
            

        } else {
            // incorrect user input
            correct_streak = 0;
            miss_streak += 1;
            total_characters_missed += 1;
            characters_typed[user_input].second++;
        }

        characters_typed[user_input].first++;
        total_inputs++;
        longest_correct_streak = max(longest_correct_streak, correct_streak);
        longest_miss_streak = max(longest_miss_streak, miss_streak);
    }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = stop - start;
    time_taken = duration.count();
    accuracy = static_cast<double>(total_characters_correct) / total_inputs; 
    letters_per_minute = static_cast<double>((total_inputs / duration.count()) * 60);

}


// print the game results
void Game::viewGameStats() {
    cout << endl;
    cout << "Total Characters Typed: " << total_inputs << endl;
    cout << "-------------------------------" << endl;
    cout << "Total Characters Correctly Typed: " << total_characters_correct << endl;
    cout << "Total Characters Miss-Typed: " << total_characters_missed << endl;
    cout << "-------------------------------" << endl;
    cout << "Game Length: " << time_taken << " seconds" << endl;
    cout << "Accuracy: " << accuracy << endl;
    cout << "Longest Correct Streak: " << longest_correct_streak << endl;
    cout << "Longest Miss-Type Streak: " << longest_miss_streak << endl;
    cout << "Typing Speed: " << letters_per_minute << " letters per minute" << endl;
}


void Game::viewAdvancedGameStats() {

}



// report the game stats to the current sessions stats
void Game::reportGameStats(session) {
    
}
