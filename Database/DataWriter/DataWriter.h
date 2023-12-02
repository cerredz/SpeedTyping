#ifndef DATAWRITER__H
#define DATAWRITER__H
#include <iostream>
#include <vector>
#include "../json.hpp"
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "../../Game/Game.h"
using namespace std;
using json = nlohmann::json;


class DataWriter {

    public:
        void initialize(vector<string>& files);
        void add(Game& game, WordList& prompt);
        void write(string filename, json& stats);
};
#endif