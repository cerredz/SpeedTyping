#include <iostream>
#include "SpeedTyping.h" 
#include <string>
#include "Game/Game.h"  
#include "Session/Session.h"  
using namespace std;

class Game;  
class Session;  

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

// explains to the user how the play the game
void SpeedTyping::tutorial() {
    
    cout << "\n-------------------------" << endl;
    cout << "How To Play" << endl;
    cout << "-------------------------\n" << endl;

}

// main play function
void SpeedTyping::play(WordList& prompt, Game& game, Session& session) {

    bool playing = true;
    
    while(playing) {
        string choice = "";
        cout << "\nChoose an option: \n" << endl;
        cout << "1) Play a Speed Typing Game" << endl;
        cout << "2) How To Play" << endl;
        cout << "3) View your Current Session Stats" << endl;
        cout << "4) View Your Lifetime Stats" << endl;
        cout << "5) Exit\n" << endl;
        cout << "Enter the Number Corresponding to Your Choice: ";
        cin>>choice;

        while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5") {
            cout << "Invalid Input. Please Enter A Number Between 1-4: ";
            cin>>choice;
        }

        switch(stoi(choice)) {
            case 1: {
                play_game:
                bool play_another_game = false;
                // user wants to play a speed typing game
                string new_prompt = prompt.generatePrompt();
                prompt.convertStringToWordList(new_prompt);
                game.PlayGame(prompt, session);
                game.reportGameStats(session);
                game.postGameOptions(play_another_game);

                if(play_another_game) goto play_game; // we want to stay in this case without going back to the start if the user wants to keep playing continuous games
                break;
            }
            case 2: 
                tutorial();
                break;
            case 3: 
                // user wants to see the session stats
                session.statOptions(game);
                break;
            case 4: 
                cout << "Currently Implementing" << endl;
                break;
            case 5: {
                // user wants to stop playing
                cout << "Thank you for playing speed typing, until next time!!!\n" << endl;
                playing = false;
                break;
            }
                
        }

    }
    

}

