#include <iostream>
#include "DataReader.h"
using namespace std;
namespace fs = filesystem;



// make sure the json files for output exist
vector<string> DataReader::initialize() {

    vector<string> files;
    // check if games.json file exists
    string filename = "games.json";


    if(!fs::exists(filename)) {
        files.push_back("games.json");
    } 

    // check if the lifetime stats file exists
    filename = "player_stats.json";
    if(!fs::exists(filename)) {
        files.push_back("player_stats.json");
    }

    return files;
}

// returns a json object of a json file where the name of the file is passed in as a parameter
json DataReader::read(string filename) {

    ifstream file(filename);

    if(!file.is_open()) {
        cerr << "Error: unable to open file " << filename << endl;
        return json();
    }

    json data;
    file >> data;
    file.close();
    return data;
}

// adds the characters typed for a game to the letter stats in the player_stats.json file
void DataReader::updateLetterStats(unordered_map<char, pair<int, int>> characters_typed, json& stats) {

    
    for(const auto& entry : characters_typed) {
        char letter = entry.first;

        int game_correct = entry.second.first;
        int game_incorrect = entry.second.second;

        // Check if the character exists in the JSON file
        if (stats["Letter Stats"].count(string(1, letter)) == 0) {
            cout << letter << "does not exist" << endl;
            // If not, create it with "correct" and "incorrect" set to 0
            stats["Letter Stats"][string(1, letter)] = {
                {"correct", 0},
                {"incorrect", 0}
            };
        }

        int total_correct = stats["Letter Stats"][string(1, letter)]["correct"].get<int>();
        int total_incorrect = stats["Letter Stats"][string(1, letter)]["incorrect"].get<int>();

        stats["Letter Stats"][string(1, letter)]["correct"] = total_correct + game_correct;
        stats["Letter Stats"][string(1, letter)]["incorrect"] = total_incorrect + game_incorrect;
    }

}

// return the letter stats in the player_stats json file in the form of a map
unordered_map<char, pair<int, int>> DataReader::letters(json& file) {
    
    json letter_stats = file["Letter Stats"];
    unordered_map<char, pair<int, int>> result;

    for (const auto& entry : letter_stats.items()) {

        try {
            char letter = entry.key()[0]; // Get the letter directly from the key
            int correct = entry.value()["correct"].get<int>();
            int incorrect = entry.value()["incorrect"].get<int>();

            result[letter] = make_pair(correct, incorrect);
        } catch (const exception& e) {
            cerr << "Error processing entry: " << e.what() << endl;
        }
    }


    return result;
}

// given the letter stats, return the accuracy of the letters typed
float DataReader::accuracy(unordered_map<char, pair<int, int>>& map) {

    int total_correct = 0, total_incorrect = 0;

    for(const auto& entry : map) {

        int correct = entry.second.first;
        int incorrect = entry.second.second;

        total_correct += correct;
        total_incorrect += incorrect;
    }

    double acc = (static_cast<double>(total_correct) / static_cast<double>(total_correct + total_incorrect)) * 100;
    float res = round(acc * 100) / 100;
    return res;
}

// returns the most accurate character and its accuracy in a map
pair<double, char> DataReader::accurate(unordered_map<char, pair<int, int>>& map) {

    priority_queue<pair<double, char>> heap;

    for(const auto& entry : map) {
        
        char letter = entry.first;
        int correct = entry.second.first;
        int incorrect = entry.second.second;
        if(correct == 0 && incorrect == 0){
            continue;
        }

        double accuracy = static_cast<double>(correct) / static_cast<double>(correct + incorrect);
        heap.push({accuracy, letter});
    }

    cout << heap.top().first << ": " << heap.top().second << endl;
    return heap.top();
}

// return the most frequent character and its inputs in a map
pair<int, char> DataReader::frequent(unordered_map<char, pair<int, int>>& map) {
    priority_queue<pair<int, char>> heap;

    for(const auto& entry : map) {
        char letter = entry.first;
        int correct = entry.second.first;
        int incorrect = entry.second.second;
        heap.push({correct + incorrect, letter});
    }

    cout << heap.top().first << ": " << heap.top().second << endl;

    return heap.top();
}