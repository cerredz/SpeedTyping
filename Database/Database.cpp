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
void Database::appendGameStats(Game& game) {
    writer.add(game);
}

// update the player_stats.json file after a game is played
void Database::updatePlayerStats(Game& game) {
    
    json player_stats = reader.read("player_stats.json");
}