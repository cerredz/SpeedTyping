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
            games["game_data"] = json::array();

            
            ofstream outputFile(files[i]);
            outputFile << games.dump(4) << endl;
            outputFile.close();
        } else if (files[i] == "player_stats.json") {
            // create player stats file
            json player_stats;

            player_stats["games_played"] = 0;
            player_stats["time_played"] = 0;
            ofstream outputFile(files[i]);
            outputFile << player_stats.dump(4) << endl;
            outputFile.close();
        }
    }
}

