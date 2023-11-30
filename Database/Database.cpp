#include <iostream>
#include "Database.h"

using namespace std;
namespace fs = filesystem;


Database::Database() {

    // check if games.json file exists
    string filename = "games.json";
    if(!fs::exists(filename)) {
        json games;
        games["game_data"] = json::array();

        
        ofstream outputFile(filename);
        outputFile << games.dump(4) << endl;
        outputFile.close();
    } 

    // check if the lifetime stats file exists
    string filename = "player_stats.json"
    if(!fs::exists(filename)) {
        json player_stats;

        player_stats["games_played"] = 0;
        player_stats["time_played"] = 0;

    }



}