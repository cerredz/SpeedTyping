#ifndef DATAREADER__H
#define DATAREADER__H
#include <iostream>
#include <vector>
#include "../json.hpp"
#include "../../Game/Game.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <queue>
#include <iomanip>  

using namespace std;
using json = nlohmann::json;


class DataReader {

    public:
        vector<string> initialize();
        json read(string filename);
        void updateLetterStats(unordered_map<char, pair<int, int>> characters_typed, json& stats);
        unordered_map<char, pair<int, int>> letters( json& file);
        float accuracy(unordered_map<char, pair<int, int>>& map);
        pair<double, char> accurate(unordered_map<char, pair<int, int>>& map);
        pair<int, char> frequent(unordered_map<char, pair<int, int>>& map);
        void general();
};
#endif