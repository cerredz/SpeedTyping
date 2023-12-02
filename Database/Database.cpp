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




    // update high scores
    writer.write("player_stats.json", player_stats);
    

    
}