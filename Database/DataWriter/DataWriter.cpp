#include <iostream>
#include "DataWriter.h"
using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;


// create specific files used for database managament if not already created
void DataWriter::initialize(vector<string>& files) {

    int n = files.size();
    for(int i = 0; i < n; i++) {
        
        if(files[i] == "games.json") {
            // create games data file
            json games;
            games["games_data"] = json::array();
            
            ofstream outputFile(files[i]);
            outputFile << games.dump(4) << endl;
            outputFile.close();

        } else if (files[i] == "player_stats.json") {
            // create player stats file
            json player_stats;
            player_stats["General Stats"] = json::object();
            player_stats["High Scores"] = json::object();
            player_stats["Letter Stats"] = json::object();

            // add the general player stats to the file
            player_stats["General Stats"]["games_played"] = 0;
            player_stats["General Stats"]["time_played"] = 0;
            player_stats["General Stats"]["average_game_length"] = 0.0;
            player_stats["General Stats"]["total_characters_typed"] = 0;
            player_stats["General Stats"]["accuracy"] = 0;
            player_stats["General Stats"]["letters_per_minute"] = 0;
            player_stats["General Stats"]["words_per_minute"] = 0;
            player_stats["General Stats"]["most_frequent_character"] = {
                {"character", ""},
                {"inputs", 0}
            };
            player_stats["General Stats"]["most_accurate_character"] = {
                {"character", ""},
                {"accuracy", 0.0}
            };
            player_stats["General Stats"]["words_typed"] = 0;


            // add the high scores to the file
            player_stats["High Scores"]["total_inputs"] = 0;
            player_stats["High Scores"]["fastest_game"] = 10000;
            player_stats["High Scores"]["slowest_game"] = 0;
            player_stats["High Scores"]["accuracy"] = 0;
            player_stats["High Scores"]["correct_character_streak"] = 0;
            player_stats["High Scores"]["incorrect_character_streak"] = 0;
            player_stats["High Scores"]["letters_per_minute"] = 0;
            player_stats["High Scores"]["words_per_minute"] = 0;

            // add the character stats to the file
            for (char c = 'a'; c <= 'z'; ++c) {
                player_stats["Letter Stats"][string(1, c)] = {
                    {"correct", 0},
                    {"incorrect", 0}
                };
            }

            for (char c = '0'; c <= '9'; ++c) {
                player_stats["Letter Stats"][string(1, c)] = {
                    {"correct", 0},
                    {"incorrect", 0}
                };
            }

            // Add common special characters
            const string special_characters = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/";
            for (char c : special_characters) {
                player_stats["Letter Stats"][string(1, c)] = {
                    {"correct", 0},
                    {"incorrect", 0}
                };
            }


            ofstream outputFile(files[i]);
            outputFile << player_stats.dump(4) << endl;
            outputFile.close();
        }
    }
}


// add the stats from a game to the games.json file
void DataWriter::add(Game& game, WordList& prompt) {

    string filename = "games.json";

    // Create a JSON object to represent the game data
    json gameData;
    gameData["total_inputs"] = game.getTotalInputs();
    gameData["total_correct"] = game.getTotalCharactersCorrect();
    gameData["total_incorrect"] = game.getTotalCharactersMissed();
    gameData["correct_streak"] = game.getLongestCorrectStreak();
    gameData["incorrect_streak"] = game.getLongestMissedStreak();
    gameData["accuracy"] = game.getAccuracy();
    gameData["letters_per_minute"] = game.getLettersPerMinute();
    gameData["words_per_minute"] = game.getWordsPerMinute();
    gameData["time_taken"] = game.getTimeTaken();
    gameData["words_typed"] = prompt.getWords();


    // add characters typed
    json chars_typed;
    for(const auto& entry : game.getCharsTyped()) {
        char letter = entry.first;
        int correct = entry.second.first;
        int incorrect = entry.second.second;
        json char_data = {
            {"correct", correct},
            {"incorrect", incorrect}
        };
        chars_typed[string(1, letter)] = char_data;
    }
    gameData["typed_char_data"] = chars_typed;

    // add character speeds
    json speed_stats;

    for (const auto& entry : game.getCharSpeeds()) {
        char letter = entry.first;
        vector<double> correct = entry.second.first;
        vector<double> incorrect = entry.second.second;

        // Check if either the correct or incorrect vectors have data
        if (!correct.empty() || !incorrect.empty()) {
            json char_data;
            
            // Add data only if the vector is not empty
            if (!correct.empty()) {
                char_data["correct"] = json::array();
                for (double speed : correct) {
                    char_data["correct"].push_back(speed);
                }
            }

            // Add data only if the vector is not empty
            if (!incorrect.empty()) {
                char_data["incorrect"] = json::array();
                for (double speed : incorrect) {
                    char_data["incorrect"].push_back(speed);
                }
            }

            speed_stats[string(1, letter)] = char_data;
        }
    }

    gameData["speed_char_data"] = speed_stats;


    // add gameData to the end of the json file
    ifstream inputFile(filename);
    json games_data;
    inputFile >> games_data;
    inputFile.close();

    games_data["games_data"].push_back(gameData);
    ofstream outputFile(filename);
    outputFile << games_data << endl;
    outputFile.close();
}


// takes the inputted json object and ouputs it to the inputted json file name
void DataWriter::write(string filename, json& stats) {

    ofstream file(filename);


    if(!file.is_open()) {
        // file not found
        cerr << "Error: Unable to Open Player Stats Output File (restart program)" << endl;
        return;
    }

    file << stats.dump(4) << endl;
    file.close();
}