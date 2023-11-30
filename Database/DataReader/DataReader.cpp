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