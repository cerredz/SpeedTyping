#include <iostream>
#include "../Session/Session.h"
#include "../Game/Prompt/WordList.h"
#include "../Game/Game.h"
#include <unordered_map>
#include <unordered_set>
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
    left_hand_accuracy = 0.0;
    right_hand_accuracy = 0.0;
    average_correct_character_speed = 0.0;
    average_incorrect_character_speed = 0.0;
    letters_per_minute = 0;
    words_per_minute = 0;
    time_taken = 0;
    characters_typed = unordered_map<char,pair<int, int>>();
    character_speed = unordered_map<char, pair<vector<double>,vector<double>>>(); 
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

int Game::getLettersPerMinute() {
    return letters_per_minute;
}

int Game::getWordsPerMinute() {
    return words_per_minute;
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
    while(!max_heap.empty() && i <= index) {
        pair<int, char> character_data = max_heap.top();
        max_heap.pop();

        char letter = character_data.second;
        int frequency = character_data.first;

        cout << i << ") " <<  "'" << letter << "', " << frequency << " total times typed. " << endl; 
        i++;
    }
}


// prints either the most accurate or least accurate letters based on bool value inputted
void Game::printAccuracyOfLetters(unordered_map<char, pair<int, int>>& map, int index, bool b) {
    cout << "---------------------------------------------" << endl;
    priority_queue<pair<double, char>> max_heap;
    priority_queue<pair<double, char>, vector<pair<double, char>>, greater<pair<double, char>>> min_heap;


    for (const auto& entry : map) {
        char letter = entry.first;
        int correct = entry.second.first, incorrect = entry.second.second;
        double accuracy = static_cast<double>(correct) / (correct + incorrect) * 100.0;
        (b) ? max_heap.push({accuracy, letter}) : min_heap.push({accuracy, letter});
    }

    if(b) cout << "Top " << index << " Most Accurate Characters Typed: " << endl;
    if(!b) cout << "Top " << index << " Least Accurate Characters Typed: " << endl;
    
    // print the letter data
    for (int i = 1; i <= index; ++i) {

        pair<double, char> current_letter_data;
        if(b) {
            current_letter_data = max_heap.top();
            max_heap.pop();
        } else {
            current_letter_data = min_heap.top();
            min_heap.pop();
        }

        char letter = current_letter_data.second;
        double accuracy = current_letter_data.first;

        cout <<  i << ") " << letter << ", " << fixed << setprecision(2) << accuracy << "%" << endl;
    }

}

// prints left and right hand accuracy of characters typed
void Game::printHandAccuracy(unordered_map<char, pair<int, int>>& map) {

    unordered_set<char> left_hand_characters = {'!', '@', '#','^','6', '$', '%', '1', '2', '3', '4', '5', 'q', 'w', 'e', 'r', 't', 'g', 'f', 'd', 's', 'a', 'z','x','c','v'};
    unordered_set<char> right_hande_characters = {'b', 'h', 'y', '7', '8', '9', '0', 'u', 'i', 'o', 'p', '[', '{', ']', '}', '&', '*', '(', ')', '|', 'j', 'k', 'l', ';', ':', '"', 'n', 'm', ',', '<', '>', '.', '?'};


    int total_left_inputs = 0, total_left_incorrect = 0;
    int total_right_inputs = 0, total_right_incorrect = 0;

    for(const auto& entry : map) {
        char letter = entry.first;
        int correct = entry.second.first;
        int incorrect = entry.second.second;

        if(left_hand_characters.count(letter)) {
            total_left_inputs += (correct + incorrect);
            total_left_incorrect += incorrect;
            continue;
        } 

        if(right_hande_characters.count(letter)) {
            total_right_inputs += (correct + incorrect);
            total_right_incorrect += incorrect;
            continue;
        }
    }

    left_hand_accuracy = static_cast<double>(total_left_inputs - total_left_incorrect) / total_left_inputs * 100;
    right_hand_accuracy = static_cast<double>(total_right_inputs - total_right_incorrect) / total_right_inputs * 100;

    cout << "---------------------------------------------" << endl;
    cout << "Left Hand Stats: " << endl;
    cout << "Accuracy: " << left_hand_accuracy << "%" << endl;
    cout << endl;
    cout << "Right Hand Stats: " << endl;
    cout  << "Accuracy: " << right_hand_accuracy << "%" << endl;
}

// prints the speed stats of a game
void Game::printSpeedStats(const unordered_map<char, pair<vector<double>, vector<double>>>& map) {

    priority_queue<pair<double, char>> slowest_characters; 
    priority_queue<pair<double, char>, vector<pair<double, char>>, greater<pair<double, char>>> fastest_characters;
    
    double total_correct_time = 0.0, total_incorrect_time = 0.0; // time of chars
    int total_correct = 0, total_incorrect = 0; // # of chars

    double total_left_correct_time = 0.0, total_left_incorrect_time = 0.0, total_right_correct_time  = 0.0, total_right_incorrect_time = 0;

    for(const auto& entry : map) {
        // compute average speed of correct and incorrect characters
        char letter = entry.first;
        vector<double> correct_times = entry.second.first;
        vector<double> incorrect_times = entry.second.second;

        total_correct += correct_times.size();
        total_incorrect += incorrect_times.size();

        double total_time_character_typed = 0.0;

        for(double time : correct_times) {
            total_correct_time += time;
            total_time_character_typed += time;
        }

        for(double time : incorrect_times) {
            total_incorrect_time += time;
            total_time_character_typed += time;
        }

        // sort fastest and slowest character speeds
        int num_times_character_typed = correct_times.size() + incorrect_times.size();
        double average_time_character_typed = static_cast<double>(total_time_character_typed) / num_times_character_typed;
        slowest_characters.push({average_time_character_typed, letter});
        fastest_characters.push({average_time_character_typed, letter});
    }

    average_correct_character_speed = static_cast<double> (total_correct_time) / total_correct;
    average_incorrect_character_speed = static_cast<double> (total_incorrect_time) / total_incorrect;
    cout << "---------------------------------------------" << endl;
    cout << "Average Correct Character Typing Speed: " << average_correct_character_speed * 1000 << " milliseconds" << endl;
    cout << "Average Incorrect Character Typing Speed: " << average_incorrect_character_speed * 1000 << " milliseconds" << endl;
    cout << "Longest Time Without Mistyping a Character: " << longest_correct_streak_time << " seconds" << endl;
    cout << "Longest Time Without Typing a Character Correctly: " << longest_incorrect_streak_time << " seconds" << endl; 
    cout << endl;
    cout << "Fastest Average Character Typing Speeds (Milliseconds):  " << endl;
    for(int i = 1; i <= 3 && !fastest_characters.empty(); i++) {
        pair<double, char> current_fastest_character = fastest_characters.top();
        fastest_characters.pop();
        char letter = current_fastest_character.second;
        double speed = current_fastest_character.first;
        cout << i << ") " << letter << ", " << speed * 1000 << endl;
    }
    cout << endl;
    cout << "Slowest Average Character Typing Speeds (Milliseconds):  " << endl;
    for(int i = 1; i <= 3 && !fastest_characters.empty(); i++) {
        pair<double, char> current_fastest_character = slowest_characters.top();
        slowest_characters.pop();
        char letter = current_fastest_character.second;
        double speed = current_fastest_character.first;
        cout << i << ") " << letter << ", " << speed * 1000 << endl;
    }

    
}


// actual user playing the game function
void Game::PlayGame(WordList& prompt, Session& session) {

    auto start = chrono::high_resolution_clock::now();
    prompt.printWordList();

    int index = 0;
    int correct_streak = 0, miss_streak = 0;
    double correct_steak_time = 0.0, incorrect_streak_time = 0.0; 

    // while user have not typed all letters
    while(index < prompt.getSize()) {

        char user_input;
        auto input_start = chrono::high_resolution_clock::now(); 
        user_input = _getch();
        auto input_stop = chrono::high_resolution_clock::now(); 
        double input_duration = chrono::duration<double>(input_stop - input_start).count();

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
            correct_steak_time += input_duration;
            incorrect_streak_time = 0.0;
            prompt.printLetter(index);
            index++;
                // dont want to include spaces in character data
            if(user_input != 32) {
                characters_typed[user_input].first++;
                character_speed[user_input].first.push_back(input_duration);
            }
            

        } else {
            // incorrect user input
            correct_streak = 0;
            miss_streak += 1;
            total_characters_missed += 1;
            correct_steak_time = 0.0;
            incorrect_streak_time += input_duration;
            if(user_input != 32)  {
                characters_typed[prompt.getLetter(index)].second++;
                character_speed[prompt.getLetter(index)].second.push_back(input_duration);
            }
            
            
            
        }
        
        total_inputs++;
        longest_correct_streak = max(longest_correct_streak, correct_streak);
        longest_miss_streak = max(longest_miss_streak, miss_streak);
        longest_correct_streak_time = max(longest_correct_streak_time, correct_steak_time);
        longest_incorrect_streak_time = max(longest_incorrect_streak_time, incorrect_streak_time);
    }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = stop - start;
    time_taken = duration.count();
    accuracy = static_cast<double>(total_characters_correct) / total_inputs * 100.0;
    letters_per_minute = (total_inputs / duration.count()) * 60;
    words_per_minute = (prompt.getWords() / duration.count()) * 60;

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
    cout << "Letters Per Minute: " << letters_per_minute << endl;
    cout << "Words Per Minute: " << words_per_minute << endl;
    cout << "---------------------------------------------" << endl;

    
}


void Game::viewAdvancedGameStats() {

    cout << endl;
    cout << "General Advanced Stats: " << endl;
    printMostFrequentLetters(characters_typed, 3);
    printAccuracyOfLetters(characters_typed, 3, true);
    printAccuracyOfLetters(characters_typed, 3, false);

    cout << endl;
    cout << "Typing Speed Advanced Stats: " << endl;
    printSpeedStats(character_speed);

    cout << endl;
    cout << "Left vs Right Hand Stats: " << endl;
    printHandAccuracy(characters_typed);
    

}



// report the game stats to the current sessions stats
//void Game::reportGameStats(session) {
//    
//}
