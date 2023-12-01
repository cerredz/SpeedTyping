#ifndef DATABASE__H
#define DATABASE__H

#include <iostream>
#include "../Game/Game.h"
#include <fstream>
#include <string>
#include "json.hpp"
#include <filesystem>
#include "../Game/Game.h"
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
        void appendGameStats(Game& game);
        void updatePlayerStats(Game& game);
};
#endif
