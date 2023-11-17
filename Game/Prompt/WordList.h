#ifndef WORDLIST__H
#define WORDLIST__H

#include<iostream>
#include <vector>
#include <string>
using namespace std;

class WordList {
    private:
        vector<char> prompt_letters;
        int size;

    public:
        WordList();
        string generatePrompt();
        void convertStringToWordList(vector<char>& prompt, string str);
        bool checkCharInput(char c, int index);
        void printWordList();
        void printLetter(int index);
        int getSize();
        char getLetter(int index);

};

#endif





