#include <iostream>
#include "Database.h"

using namespace std;
namespace fs = filesystem;

// create database files if they do not exist
Database::Database() {

    vector<string> files_to_create = reader.initialize();
    if(!files_to_create.size() == 0) {
        // files missing
        writer.initialize(files_to_create);
    }
}

// add the post-game stats to the games.json file
void Database::appendGameStats(Game& game, WordList& prompt) {
    writer.add(game, prompt);
}

// update the player_stats.json file after a game is played
void Database::updatePlayerStats(Game& game, WordList& prompt) {
    
    json player_stats = reader.read("player_stats.json");

    // update letter stats
    reader.updateLetterStats(game.getCharsTyped(), player_stats);
    
    // update general stats
    int games_played = player_stats["General Stats"]["games_played"].get<int>();
    player_stats["General Stats"]["games_played"] = games_played + 1;
    
    int time_played = player_stats["General Stats"]["time_played"].get<int>();
    player_stats["General Stats"]["time_played"] = time_played + game.getTimeTaken();
    
    int total_inputs = player_stats["General Stats"]["total_characters_typed"].get<int>();
    player_stats["General Stats"]["total_characters_typed"] = total_inputs + game.getTotalInputs();
    
    int words_typed = player_stats["General Stats"]["words_typed"].get<int>();
    player_stats["General Stats"]["words_typed"] = words_typed + prompt.getWords();

    int letters_per_minute = (player_stats["General Stats"]["total_characters_typed"].get<int>() / player_stats["General Stats"]["time_played"].get<int>()) * 60;
    player_stats["General Stats"]["letters_per_minute"] = letters_per_minute;

    int words_per_minute = (player_stats["General Stats"]["words_typed"].get<int>() / player_stats["General Stats"]["time_played"].get<int>()) * 60;
    player_stats["General Stats"]["words_per_minute"] = words_per_minute;

    int average_game_length = (player_stats["General Stats"]["time_played"].get<int>() / player_stats["General Stats"]["games_played"].get<int>());
    player_stats["General Stats"]["average_game_length"] = average_game_length;

    unordered_map<char, pair<int, int>> letter_stats = reader.letters(player_stats);
    float accuracy = reader.accuracy(letter_stats);
    player_stats["General Stats"]["accuracy"] = accuracy;
    
    pair<double, char> most_acc_char= reader.accurate(letter_stats);
    player_stats["General Stats"]["most_accurate_character"]["accuracy"] = most_acc_char.first * 100;
    player_stats["General Stats"]["most_accurate_character"]["character"] = string(1, most_acc_char.second);

    pair<int, char> most_freq_char = reader.frequent(letter_stats);
    player_stats["General Stats"]["most_frequent_character"]["inputs"] = most_freq_char.first;
    player_stats["General Stats"]["most_frequent_character"]["character"] = string(1, most_freq_char.second);

    // update high scores
    double most_accurate = max(player_stats["High Scores"]["accuracy"].get<double>(), game.getAccuracy());
    player_stats["High Scores"]["accuracy"] = most_accurate;

    int slowest_game = max(player_stats["High Scores"]["slowest_game"].get<int>(), game.getTimeTaken());
    player_stats["High Scores"]["slowest_game"] = slowest_game;

    int fastest_game = min(player_stats["High Scores"]["fastest_game"].get<int>(), game.getTimeTaken());
    player_stats["High Scores"]["fastest_game"] = fastest_game;

    int correct_streak = max(player_stats["High Scores"]["correct_character_streak"].get<int>(), game.getLongestCorrectStreak());
    player_stats["High Scores"]["correct_character_streak"] = correct_streak;

    int incorrect_streak = max(player_stats["High Scores"]["incorrect_character_streak"].get<int>(), game.getLongestMissedStreak());
    player_stats["High Scores"]["incorrect_character_streak"] = incorrect_streak;

    int highest_lpm = max(player_stats["High Scores"]["letters_per_minute"].get<int>(), game.getLettersPerMinute());
    player_stats["High Scores"]["letters_per_minute"] = highest_lpm;

    int highest_wpm = max(player_stats["High Scores"]["words_per_minute"].get<int>(), game.getWordsPerMinute());
    player_stats["High Scores"]["words_per_minute"] = highest_wpm;

    int highest_inputs = max(player_stats["High Scores"]["total_inputs"].get<int>(), game.getTotalInputs());
    player_stats["High Scores"]["total_inputs"] = highest_inputs;


    writer.write("player_stats.json", player_stats);
    

    
}