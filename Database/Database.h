#ifndef DATABASE__H
#define DATABASE__H

#include <iostream>
#include "../Game/Game.h"
#include <fstream>
#include <string>
#include "json.hpp"
#include <filesystem>
#include "DataReader/DataReader.h"
#include "DataWriter/DataWriter.h"

using namespace std;
using json = nlohmann::json;

class Database {
    private:
        DataReader reader;
        DataWriter writer;

    public:
        Database(); 
};
#endif
