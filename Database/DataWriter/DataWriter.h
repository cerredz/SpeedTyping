#ifndef DATAWRITER__H
#define DATAWRITER__H
#include <iostream>
#include <vector>
#include "../json.hpp"
#include <filesystem>
#include <fstream>
using namespace std;

class DataWriter {

    public:
        void initialize(vector<string>& files);
};
#endif