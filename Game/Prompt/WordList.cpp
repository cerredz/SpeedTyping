#include <iostream>
#include <vector>
#include<string>
#include<cstdlib>

#include "WordList.h"
#include "Sentences.h"
using namespace std;


WordList::WordList() {
    string prompt = generatePrompt();
    size = prompt.length();
    prompt_letters = vector<char> (size);
    convertStringToWordList(prompt_letters, prompt);
    
}

// randomly generate a prompt for the user to copy using the sentences contained in sentences.cpp
string WordList::generatePrompt() {
    
    string prompt = "";
    srand((unsigned) time(NULL));

    for(int i = 0 ; i < 100; i++) {
        int randomNumber = rand();
        cout << randomNumber << endl;
    }


   

}

void WordList::convertStringToWordList(vector<char>& prompt, string str) {

}






