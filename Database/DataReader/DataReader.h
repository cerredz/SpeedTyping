#ifndef DATAREADER__H
#define DATAREADER__H
#include <iostream>
#include <vector>
#include "../json.hpp"
#include <filesystem>
#include <fstream>
using namespace std;
using json = nlohmann::json;


class DataReader {

    public:
        vector<string> initialize();
        json read(string filename);
        

};
#endif