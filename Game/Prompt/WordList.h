#ifndef WORDLIST__H
#define WORDLIST__H

#include<iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class WordList {
    private:
        vector<char> prompt_letters;
        unordered_set<int> return_indexes; // indexes where we went to the next line
        int size;
        int words;

    public:
        WordList();
        string generatePrompt();
        void convertStringToWordList(string str);
        bool checkCharInput(char c, int index);
        void printWordList();
        void printLetter(int index);
        int getSize();
        int getWords();
        char getLetter(int index);
        vector<char> getPromptLetters();

};

#endif





