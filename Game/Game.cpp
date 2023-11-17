#include <iostream>
#include "../Session/Session.h"
#include "../Game/Prompt/WordList.h"
#include "../Game/Game.h"
#include <unordered_map>
#include <queue>
#include <chrono>
#include <conio.h>
#include <iomanip> 
#include <cctype>



using namespace std;

// default constructor for a Game object
Game::Game() {

    total_inputs = 0;
    total_characters_correct = 0;
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


// prints the most frequent characters the user typed in a game
void Game::printMostFrequentLetters(unordered_map<char, pair<int, int>>& map, int index) {
    cout << "---------------------------------------------" << endl;
    priority_queue<pair<int, char>> max_heap; // sort based off # of times typed
    for(auto entry : map) {
        char letter = entry.first;
        int frequency = entry.second.first + entry.second.second;
        max_heap.push({frequency, letter});
    }

    cout << "Top " << index << " Most Frequent Characters Typed: " << endl;
    int i = 1;
    while(i <= index) {
        pair<int, char> character_data = max_heap.top();
        max_heap.pop();

        char letter = character_data.second;
        int frequency = character_data.first;

        cout << i << ") " <<  "'" << letter << "', " << frequency << " total times typed. " << endl; 
        i++;
    }
    cout << "---------------------------------------------" << endl;
    cout << endl;
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
        
        if (user_input >= 'A' && user_input <= 'Z') {
            // convert to lowercase when inputting in map
            user_input += 32;
        }

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
            if(user_input != 32) characters_typed[user_input].second++;
            
        }
        // dont want to include spaces in character data
        if(user_input != 32) characters_typed[user_input].first++;
        total_inputs++;
        longest_correct_streak = max(longest_correct_streak, correct_streak);
        longest_miss_streak = max(longest_miss_streak, miss_streak);
    }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = stop - start;
    time_taken = duration.count();
    accuracy = static_cast<double>(total_characters_correct) / total_inputs * 100.0;
    letters_per_minute = static_cast<double>((total_inputs / duration.count()) * 60);

}


// print the game results
void Game::viewGameStats() {
    cout << endl;
    cout << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Total Characters Typed: " << total_inputs << endl;
    cout << "Total Characters Correctly Typed: " << total_characters_correct << endl;
    cout << "Total Characters Miss-Typed: " << total_characters_missed << endl;
    cout << "Game Length: " << time_taken << " seconds" << endl;
    cout << "Accuracy: " << fixed << setprecision(2) << accuracy << "%" << endl;
    cout << "Longest Correct Character Streak: " << longest_correct_streak << endl;
    cout << "Longest Incorrect Character Streak: " << longest_miss_streak << endl;
    cout << "Typing Speed: " << letters_per_minute << " letters per minute" << endl;
    cout << "---------------------------------------------" << endl;
}


void Game::viewAdvancedGameStats() {

    cout << endl;
    printMostFrequentLetters(characters_typed, 3);



}



// report the game stats to the current sessions stats
//void Game::reportGameStats(session) {
//    
//}
