## Speed Typing Overview 🚄

Speed Typing is a game designed to help players increase their typing speed and accuracy. Developed using c++, Speed Typing tracks essential typing data (characters typed, speed of typing, accuracy, etc) when you are playing. This data, after every game played, is stored in a JSON file; serving as a database and a way for user progress to be saved.This stored information is then used for to generate both general and advanced performance related metrics. Whether you're interested in game stats, session stats, or lifetime stats, Speed Typing has the capabiltiy of providing a detailed analysis of all three.

## Setup

1. Clone the Speed Typing repository
2. In the directory you cloned the repository, run the following command in the terminal:

```bash
g++ Game/Prompt/WordList.cpp Game/Prompt/Sentences.cpp Game/Game.cpp Session/Session.cpp SpeedTyping.cpp Database/Database.cpp Database/DataReader/DataReader.cpp Database/DataWriter/DataWriter.cpp main.cpp -o main
```

3. After running the above command, run the following command in the terminal:

```bash
./main
```

**Note:**After completing all of the above steps and exiting the program, whenever you want to start the program again all u have to do is complete step 3 and dont worry about steps 1 and 2 \*

## Features

**Real-Time Feedback:** Capability to view realtime feeback on accuracy, speed, and all other overall typing stats after playing a game to help improve your typing skills.
**Comprehensive Stats:**Ability to see both general and advanced stats ranging from accuracy, most frequent character, games played, words per minute to speed stats, most / least accurate characters, left vs right hand typing stats, and many more.
**Database Management:**Data from all games played is stored in a JSON file, functioning as a database to save user progress and enable a seamless continuation of a users typing journey.
**Interactive Menu System:**User-friendly interface with interactive menus for easy navigation between playing games, viewing tutorials, looking at stats, and exiting the program.
