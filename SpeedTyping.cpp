#include <iostream>
#include "SpeedTyping.h"
#include <string>

void SpeedTyping::welcome() {

    cout << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------\n" << endl;
    cout << "Welcome to Speed Typing, where keystrokes become your biggest ally in a race against time!" << endl;
    cout << "Sharpen your typing skills and embark on an exciting journey to improve your accuracy, speed, and overall keyboard coordination." << endl;
    cout << "Whether you are veteran typist or a beginner, Speed Typing offers an interactive, fun game with real-time feedback. " << endl;
    cout << "Join us in the ultimate quest for typing supremacy – where speed meets precision, and every type is a step towards keyboard mastery." << endl;
    cout << "The challenge awaits; let the typing begin!!!\n" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------\n" << endl;
}


// main play function
void SpeedTyping::play(WordList& prompt, Game& game, Session& session) {

    bool playing = true;
    
    while(playing) {
        int choice = 0;
        cout << "\nChoose an option: \n" << endl;
        cout << "1) Play a Speed Typing Game" << endl;
        cout << "2) View your Current Session Stats" << endl;
        cout << "3) View Your Lifetime Stats" << endl;
        cout << "4) Exit\n" << endl;
        cout << "Enter the Number Corresponding to Your Choice: ";
        cin>>choice;

        while(choice != 1 && choice != 2 && choice != 3 && choice != 4) {
            cout << "Invalid Input. Please Enter A Number Between 1-4: ";
            cin>>choice;
        }

        switch(choice) {
            case 1: {
                // user wants to play a speed typing game
                string new_prompt = prompt.generatePrompt();
                prompt.convertStringToWordList(new_prompt);
                game.PlayGame(prompt, session);
                game.reportGameStats(session);
                //game.postGameOptions();
                break;
            }
            case 2: 
                // user wants to see the session stats
                session.statOptions();
                break;
            case 3: 
                cout << "Currently Implementing" << endl;
                break;
            case 4: {
                // user wants to stop playing
                cout << "Thank you for playing speed typing, until next time!!!\n" << endl;
                playing = false;
                break;
            }
                
        }

    }
    

}

using namespace std;