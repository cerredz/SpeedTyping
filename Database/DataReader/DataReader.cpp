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