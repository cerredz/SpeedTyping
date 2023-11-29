#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iomanip>

#include "Session.h"
#include "../Game/Game.h"
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

void Session::addTime(int num) {
    time.push_back(num);
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
    for (const auto& entry : map) {
        char letter = entry.first;
        vector<double> correct = entry.second.first;
        vector<double> incorrect = entry.second.second;

        // Check if the letter already exists in the map
        if (character_speed.find(letter) == character_speed.end()) {
            // If not, create a new entry with empty vectors
            character_speed[letter] = { {}, {} };
        }

        // Append speeds to the existing vectors
        character_speed[letter].first.insert(character_speed[letter].first.end(), correct.begin(), correct.end());
        character_speed[letter].second.insert(character_speed[letter].second.end(), incorrect.begin(), incorrect.end());
    }
}

// get the average of a list of numbers
template<typename T>
T Session::getAverage(const vector<T>& nums) {
    T sum = 0;
    int size = nums.size();
    if(nums.empty()) return sum;

    for(auto num : nums) 
        sum += static_cast<T>(num);

    return sum / static_cast<T>(size);
}

// get the minimum of a list of numbers
template<typename T>
T Session::getLowest(const vector<T>& nums) {

    T lowest = 1e9; 
    if(nums.empty()) return -1;

    for(auto num : nums) 
        lowest = min(lowest, num);
    
    return lowest;
}

// get the maximum of a list of numbers
template <typename T>
T Session::getHighest(const vector<T>& nums) {
    T highest = -1;
    if(nums.empty()) return -1;

    for(auto num : nums)
        highest = max(highest, num);

    return static_cast<T>(highest);
}

// get the median of a list of numbers
template<typename T>
T Session::getMedian(const vector<T>& nums) {

    int size = nums.size();
    sort(nums.begin(), nums.end());
    return static_cast<T>(nums[size - 1] / 2);
}

// get the standard deviation of a list of numbers
template <typename T>
T Session::getStandardDeviation(const vector<T>& nums) {

    T mean = getAverage(nums), standard_deviation = 0.0;
    
    for(auto num : nums) {
        standard_deviation += pow(num - mean, 2);
    }

    return static_cast<T>(sqrt(standard_deviation, static_cast<T>(nums.size() - 1)));
}

// gets the total amount of character inputs during a session
int Session::getTotalInputs() {
    int total = 0;
    for(auto i : inputs)
        total += (i.first + i.second);
    return total;
}

// gets the total amount of correct character inputs during a session
int Session::getTotalCorrect() {
    int total = 0;
    for(auto i : inputs)
        total += (i.first);
    return total;
}

// gets the total amount of incorrect character inputs during a session
int Session::getTotalIncorrect() {
    int total = 0;
    for(auto i : inputs)
        total += (i.second);
    return total;
}

// gets the total amount of time played from a session
pair<int, int> Session::getTotalTimePlayed() {
    int total = 0;
    for(int i : time)
        total += i;

    int minutes = total / 60;   // Calculate minutes
    int seconds = total % 60;   // Calculate remaining seconds

    return {minutes, seconds};
    
}

// gets the accuracy of the session
double Session::getAccuracy() {

    int total_correct = 0, total_incorrect = 0;

    for(auto entry : inputs) {
        total_correct += entry.first;
        total_incorrect += entry.second;
    }

    return static_cast<double>(total_correct) / static_cast<double>(total_correct + total_incorrect);
}

// print the stats for a session
void Session::stats() {

    cout << "-------------------------------------------------------\n" << endl;
    cout << "Session Stats\n" << endl;
    cout << "-------------------------------------------------------\n" << endl;

    cout << "Games Played: " << games_played << endl;
    pair<int, int> total_time_played = getTotalTimePlayed();
    cout << "Total Time Played: " << total_time_played.first  << " minutes " << total_time_played.second << " seconds" << endl;
    cout << "Total Characters Typed: " << getTotalInputs() << endl;
    cout << "Accuracy: " << fixed << setprecision(2) << getAccuracy() * 100 << "%" << endl;
    cout << "Longest Correct Character Streak: " << getHighest(correct_streaks) << endl;
    cout << "Longest Incorrect Character Streak: " << getHighest(miss_streaks) << endl;
    cout << "Letters Per Minute: " << getAverage(letters_per_minute) << endl;
    cout << "Words Per Minute: " << getAverage(words_per_minute) << endl;
    cout << "\n-----------------------------------------------------\n" << endl;
    cout << endl;
}

// print the advanced stats for a session
void Session::advancedStats() {

    unordered_set<char> left_hand_characters = {'!', '@', '#','^','6', '$', '%', '1', '2', '3', '4', '5', 'q', 'w', 'e', 'r', 't', 'g', 'f', 'd', 's', 'a', 'z','x','c','v'};
    unordered_set<char> right_hand_characters = {'b', 'h', 'y', '7', '8', '9', '0', 'u', 'i', 'o', 'p', '[', '{', ']', '}', '&', '*', '(', ')', '|', 'j', 'k', 'l', ';', ':', '"', 'n', 'm', ',', '<', '>', '.', '?'};
    Game temp; // need functions from Game Class
    

    cout << "-------------------------------------------------------\n" << endl;
    cout << "Advanced Session Stats\n" << endl;
    cout << "-------------------------------------------------------\n" << endl;
    temp.displayMostFrequentLetters(characters_typed, 3);
    temp.printAccuracyOfLetters(characters_typed, 3, true);
    temp.printAccuracyOfLetters(characters_typed, 3, false);

    cout << "-------------------------------------------------------\n" << endl;
    cout << "Speed Stats\n" << endl;
    cout << "-------------------------------------------------------\n" << endl;
    temp.printSpeedStats(character_speed);

    cout << "-------------------------------------------------------\n" << endl;
    cout << "Hand Stats\n" << endl;
    cout << "-------------------------------------------------------\n" << endl;
    temp.printHandStats(characters_typed, character_speed);
    
}


// handles the logic behind whether the user wants to view the general or advanced stats
void Session::statOptions() {

    start:
    int choice = 0;
    bool isExiting = false;
    
    cout << "-------------------------------------------------------" << endl;
    cout << "What type of stats would you prefer to see?\n" << endl;
    cout << "1) General Session Stats " << endl;
    cout << "2) Advanced Session Stats " << endl;
    cout << "3) Both (1 and 2) " << endl;
    cout << "4) Back\n" << endl;
    cout << "Enter the Number Corresponding to Your Choice: ";
    cin>>choice;
    cout << endl;

    while(choice != 1 && choice != 2 && choice != 3 && choice != 4) {
        cout << "Invalid Input. Please Enter A Number Between 1-4: ";
        cin>>choice;
    }

    switch(choice) {
        case 1:
            
            stats();
            break;
        case 2: 
            advancedStats();
            break;
        case 3: 
            stats();
            advancedStats();
            break;
        case 4:
            cout << "Exiting the Session Stats. You Selected to exit. ";
            isExiting = true;
            break;
    }

    if(!isExiting) {
        // user might want to keep viewing session stats
        string user_input;
        cout << "Do you want to see more session stats? (yes, no)" << endl;
        cout << "Enter your answer here: ";
        cin>> user_input;

        while(user_input != "yes" && user_input != "no") {
            cout << "\nInvalid Answer, please type 'yes' or 'no' " << endl;
            cout << "Enter your answer here: ";
            cin>> user_input;
        }   
        if(user_input == "yes") goto start;
        
        cout << "-------------------------------" << endl;
        cout << "Exiting the Session Stats" << endl;
        cout << "-------------------------------" << endl;
    }
    

}