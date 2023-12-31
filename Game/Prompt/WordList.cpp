#include <iostream>
#include <vector>
#include<string>
#include<cstdlib>
#include <unordered_set>
#include <windows.h>
#include "MMSystem.h"

#include "WordList.h"
#include "Sentences.h"
using namespace std;

#pragma comment(lib, "winmm.lib")

// default constructor for a WordList object
WordList::WordList() {
    return_indexes = unordered_set<int>();
    string prompt = generatePrompt();
    size = prompt.length();
    words = 0;
    convertStringToWordList(prompt);

    
}

int WordList::getSize(){
    return size;
}

int WordList::getWords() {
    return words;
}
char WordList::getLetter(int index) {
    if(index >= size) return '\0';
    return prompt_letters[index];
}
// randomly generate a prompt for the user to copy using the sentences contained in sentences.cpp
string WordList::generatePrompt() {
    
    string prompt = "";
    srand((unsigned) time(NULL));
    int sentences_in_prompt = rand() % 4 + 4; // 4-7 sentences in the prompt
    //int sentences_in_prompt = 1; // used for debugging
    int num_topics = sentences.size(); 
    unordered_set<int> used_sentence_topics;

    for(int i = 0; i < sentences_in_prompt; i++) {

        int random_topic = rand() % num_topics;
        while(used_sentence_topics.count(random_topic)) {
            // topic already used in prompt
            random_topic = rand() % num_topics;
        }
        used_sentence_topics.insert(random_topic);
        int num_sentences = sentences[random_topic].size();
        int random_sentences = rand() % num_sentences;
        prompt += sentences[random_topic][random_sentences] + " ";
    }
    return prompt;
}

// converts a string to a list of chars, mainly used to convert generated prompt into WordList object
void WordList::convertStringToWordList(string str) {

    size = str.size();
    prompt_letters = vector<char> (size);
    for(int i = 0; i < size; i++) {
        prompt_letters[i] = str[i];
        if(prompt_letters[i] == ' ') {
            words++;
        }
    }
    
}

// checks a user inputted character to the inputted index of the WordList object
bool WordList::checkCharInput(char c, int index) {
    return c == prompt_letters[index];
}

// prints the WordList object in the form of a string (100 letters per line)
void WordList::printWordList() {
    
    bool go_to_next_line = false;
    cout << endl;
    cout << endl;
    for(int i = 0; i < size; i++) {

        if(i % 100 == 0 && i != 0){
            go_to_next_line = true;
        }

        if(i > 0 && go_to_next_line == true && prompt_letters[i - 1] == ' ') {
            cout << endl;
            return_indexes.insert(i);
            go_to_next_line = false;
        }

        char current_letter = prompt_letters[i];
        cout << current_letter;
    }
    cout << endl;
    cout << endl;
}

void WordList::printLetter(int index) {

    if(return_indexes.count(index)){
        cout << endl;
    }

    cout << prompt_letters[index];
}

vector<char> WordList::getPromptLetters() {
    return prompt_letters;
}







