#include <iostream>
#include <vector>
#include<string>
#include<cstdlib>
using namespace std;


// generates a prompt for the user to copy
string generatePrompt(vector<string>* sentences) {

    int range = sentences.size();
    unordered_set<int> used_indexes;
    string prompt = "";
    srand((unsigned) time(NULL));

    for(int i = 0; i < min(range, 5); i++) {

        int randomIndex = rand() % range;
    }



}

// initializes a vector of hundreds of different sentences
vector<string> sentences = {"The Man that was different than the others. ", "Today was a good day."};



