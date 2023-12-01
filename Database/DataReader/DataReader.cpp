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