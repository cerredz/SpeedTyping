#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "Session.h"
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

    for(const auto& entry : map) {

        char letter = entry.first;
        vector<double> correct = entry.second.first;
        vector<double> incorrect = entry.second.second;

        for(int speed : correct) character_speed[letter].first.push_back(speed);
        for(int speed : incorrect) character_speed[letter].second.push_back(speed);
    }
 }

// get the average of a list of numbers
template<typename T>
T Session::getAverage(const vector<T>& nums) {
    T sum = 0;
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

    return highest;
}

// get the median of a list of numbers
template<typename T>
T Session::getMedian(const vector<T>& nums) {

    int size = nums.size();
    sort(nums.begin(), nums.end());
    return (nums[size - 1] / 2);
}

// get the standard deviation of a list of numbers
template <typename T>
T Session::getStandardDeviation(const vector<T>& nums) {

    T mean = getAverage(nums), standard_deviation = 0.0;
    
    for(auto num : nums) {
        standard_deviation += pow(num - mean, 2);
    }

    return sqrt(standard_deviation, static_cast<T>(nums.size() - 1));
}

// gets the total amount of character inputs during a session
int Session::getTotalInputs() {
    int total = 0;
    for(auto i : inputs)
        total += (i.first + i.second);
    return total;
}

// gets the total amount of correct character inputs during a session
int Session::getTotalInputs() {
    int total = 0;
    for(auto i : inputs)
        total += (i.first);
    return total;
}

// gets the total amount of incorrect character inputs during a session
int Session::getTotalInputs() {
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
    cout << "Total Time Played: " << total_time_played.first  << " minutes" << total_time_played.second << " seconds" << endl;
    

}