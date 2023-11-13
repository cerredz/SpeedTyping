#ifndef __PROMPT__H
#define __PROMPT_H

#include<iostream>
#include <vector>
#include <string>
using namespace std;


class WordList {
    private:
        vector<vector<char>> prompt;
        int size;

    public:
        WordList(vector<vector<char>> prompt);
        string generatePrompt();
        void convertStringToWordList();

}

#endif





