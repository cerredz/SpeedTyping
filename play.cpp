#include <iostream>
#include "Game/Prompt/WordList.h"
using namespace std;

int main() {

    WordList prompt;
    prompt.printWordList();
    //g++ Game/Prompt/WordList.cpp Game/Prompt/Sentences.cpp play.cpp -o play -lwinmm
    return 0;
}
