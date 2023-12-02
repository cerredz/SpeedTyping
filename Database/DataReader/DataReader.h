#ifndef DATAREADER__H
#define DATAREADER__H
#include <iostream>
#include <vector>
#include "../json.hpp"
#include "../../Game/Game.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>
using namespace std;
using json = nlohmann::json;


class DataReader {

    public:
        vector<string> initialize();
        json read(string filename);
        void updateLetterStats(unordered_map<char, pair<int, int>> characters_typed, json& stats);
        

};
#endif