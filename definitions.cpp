#include "header.h"
#include <chrono>
#include <thread>
#include <cstdlib> // rand()

Player j(3);
Player::AirplanePlane PO, PR;
Player::AirplaneAttackPlane PAO, PAR;
Human o(j);
Robot robo(j);
Airplane A1, A2, A3;

string menuSelector, soundSettings, finished, chosenOption = "Start", tmp1 = "| ", tmp2 = " ", tmp3 = " |",
    Volume = "On", airplaneMatrix[3][10], letters[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"}, 
    humanAirplaneVertices[3];

bool passed1 = false, passed2 = false, finishedAirplane1 = false, finishedAirplane2 = false,
     finishedAirplane3 = false, attackPhase = false, stopReading = false, guardian = false,
     continueAttacking = false, destroyedAirplane[3] = {false, false, false}, hasAttackedAgain[10][10];

short int randomness = 1+rand()%5, superCounter = 0; // randomness - between 1 and 5
int ApXPlaneIndex = 0, ApYPlaneIndex = 0, airplaneSetup = 1, config = 1;
vector <string> hit, dodged, rememberAfterDestroyingPositions;

void Selector();
void Sound();
void ShowScreen();
void ShowButtons();
void AfterDestruction();

//Display the main menu


void ShowScreen() {
    //Font name: Rectangles
    cout<<R"(
                                                   _____ _         _                 
                                                  |  _  |_|___ ___| |___ ___ ___ ___ 
                                                  |     | |  _| . | | .'|   | -_|_ -|
                                                  |__|__|_|_| |  _|_|__,|_|_|___|___|
                                                              |_|                    
    )";
    cout<<endl<<"                                                         (Terminal Edition)"<<endl;
    cout<<R"(
       
                                                                 |
                                                           --====|====--
                                                                 |  
                                    
                                                             .-"""""-. 
                                                           .'_________'. 
                                                          /_/_|__|__|_\_\
                                                         ;'-._       _.-';
                                    ,--------------------|    `-. .-'    |--------------------,
                                     ``""--..__    ___   ;       '       ;   ___    __..--""``
                                               `"-// \\.._\             /_..// \\-"`
                                                  \\_//    '._       _.'    \\_//
                                                   `"`        ``---``        `"`
    )";
    cout<<endl<<R"(
                                               __  __                                 
                                              F  \/  ]     ____     _ ___     _    _  
                                             J |\__/| L   F __ J   J '__ J   J |  | L 
                                             | |`--'| |  | _____J  | |__| |  | |  | | 
                                             F L    J J  F L___--. F L  J J  F L__J J 
                                            J__L    J__LJ\______/FJ__L  J__LJ\____,__L
                                            |__L    J__| J______F |__L  J__| J____,__F
    )";
    //Font name: Henry 3D
}



//Function that displays currently selected option in the menu

void ShowButtons() {
    if (chosenOption == "Start") {
        //Font name: Graceful
        cout<<endl<<endl<<R"(
                                                     ____  ____  __   ____  ____ 
                                              -->   / ___)(_  _)/ _\ (  _ \(_  _)
                                              -->   \___ \  )( /    \ )   /  )(  
                                                    (____/ (__)\_/\_/(__\_) (__)  
    )"<<endl<<endl<<R"(
                                                 __  ____  ____  __  __   __ _  ____ 
                                                /  \(  _ \(_  _)(  )/  \ (  ( \/ ___)
                                               (  O )) __/  )(   )((  O )/    /\___ \
                                                \__/(__)   (__) (__)\__/ \_)__)(____/
    )"<<endl<<endl<<endl<<R"(
                            >>============================================================================<<
                            ||                                                                            ||
                            ||              Game: Terminal Airplanes (Battleships variation)              ||
                            ||              Made by: WhosWho                                              ||
                            ||              Github: https://github.com/WhosWho32                          ||
                            ||                                                                            ||
                            >>============================================================================<<
    )"<<endl;
    } else if (chosenOption == "Options") {
        cout<<endl<<endl<<R"(
                                                     ____  ____  __   ____  ____ 
                                                    / ___)(_  _)/ _\ (  _ \(_  _)
                                                    \___ \  )( /    \ )   /  )(  
                                                    (____/ (__)\_/\_/(__\_) (__)  
    )"<<endl<<endl<<endl<<R"(
                                                 __  ____  ____  __  __   __ _  ____ 
                                          -->   /  \(  _ \(_  _)(  )/  \ (  ( \/ ___)
                                          -->  (  O )) __/  )(   )((  O )/    /\___ \
                                                \__/(__)   (__) (__)\__/ \_)__)(____/
    )"<<endl<<endl<<R"(
                            >>============================================================================<<
                            ||                                                                            ||
                            ||              Game: Terminal Airplanes (Battleships variation)              ||
                            ||              Made by: WhosWho                                              ||
                            ||              Github: https://github.com/WhosWho32                          ||
                            ||                                                                            ||
                            >>============================================================================<<
    )"<<endl;
    }
}



//This reads the user input in the main menu screen

void Selector() {
    if (!stopReading) {
         std::getline(cin, menuSelector);
    if (menuSelector.empty()) {
        if (chosenOption == "Start") {
            delete verifyCode;
            cout<<"[*] The game will soon begin."<<endl;
            const char rotator[] = {'/', '|', '-', '\\', '_'};
            const int rotatorSize = sizeof(rotator)/sizeof(rotator[0]);
            cout<<"Loading ";
            for (int i = 0; i < 10+rand()%51; i++) {
                cout<<"\r[*] Loading "<<rotator[i%rotatorSize]<<std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            cout<<"\rFinished!        "<<endl;
            system("cls");
            stopReading = true;
            Player::ShowTable();

        } else if (chosenOption == "Options") {
            system("cls");
            cout<<R"(
                                                 __  ____  ____  __  __   __ _  ____ 
                                                /  \(  _ \(_  _)(  )/  \ (  ( \/ ___)
                                               (  O )) __/  )(   )((  O )/    /\___ \
                                                \__/(__)   (__) (__)\__/ \_)__)(____/
            )"<<"\n\n[*] Volume: [ "<<(Volume == "On" ? "ON" : "OFF")<<" ]\n"<<
            "[*] If you wish to test the sound, type \"test\" (no quotation marks). If you wish to turn the volume off, type \"off\".\n";
            cout<<"[*] Furthermore, if you wish to see a list of all available commands, use \"help\".\n\n";
            Sound();
        }

    }
    if (menuSelector == "s" && chosenOption == "Start") {
        chosenOption = "Options";
        system("cls");
        ShowScreen();
        ShowButtons();
        cout<<"\n\nIf you wish to access the Options menu, press Enter. Otherwise, type 'w' to return to Start.\n"<<"                                                            ";
        Selector();
    } else if (menuSelector == "wwssadadba") {
        if (!*verifyCode) {
            cout<<"[!] Secret code has been identified successfully. You have unlocked a special menu.\n";
            *verifyCode = true;
            o.SetCheatMode(true);
        } else 
            cout<<"[X] Code has already been entered!\n";
        SpecialMenu menu;
        cout<<"(Press Enter to continue)\n";
        string sAux;
        std::getline(cin, sAux);
        while(!sAux.empty()) {
            cout<<"[X] Only press Enter. Do not attempt to do anything else.\n";
            std::getline(cin, sAux);
        }
        system("cls");
        ShowScreen();
        ShowButtons();
        cout<<"\n\nIf you wish to start the game, press Enter. Otherwise, if you wish to modify some settings, type 's' to move to the Options menu, and press Enter to access it.\n"<<"                                                            ";
        Selector();
    } else if (menuSelector == "w" && chosenOption == "Options") {
        system("cls");
        chosenOption = "Start";
        ShowScreen();
        ShowButtons();
        cout<<"\n\nIf you wish to start the game, press Enter. Otherwise, if you wish to modify some settings, type 's' to move to the Options menu, and press Enter to access it.\n"<<"                                                            ";
        Selector();
    } else {
        if (chosenOption != "Sound") {
            cout<<"\n[?] Unknown command. Please follow the on-screen instructions thoroughly. Only use s or w to navigate through the menu, and press Enter to confirm your choice.";
            cout<<"\n\nIf you wish to start the game, press Enter. Otherwise, if you wish to modify some settings, type 's' to move to the Options menu, and press Enter to access it.\n"<<"                                                            ";
            Selector();
        }
    }
    } 
   
}

void Sound() {
    chosenOption = "Sound";
    cout<<">>";
    std::getline(cin, soundSettings);
    if (soundSettings == "test") {
        if (Volume == "On") {
            cout<<"\a                                           Volume : [ ON ]\n\n";
            cout<<"[*] If you wish to return to the main menu, simply type \"exit\", otherwise type \"help\" to see a list of all available commands.\n\n";
            Sound();
        } else if (Volume == "Off") {
            cout<<"                                           Volume : [ Off ]\n\n";
            cout<<"[!] Volume is currently turned off! In order to be able to hear sounds, try to turn it on by typing \"on\". Don't forget to use \"help\" if you are stuck with the syntax of a command.\n";
            Sound();
        }
    } else if (soundSettings == "off") {
        if (Volume != "Off") {
            Volume = "Off";
            cout<<"\n[!] Volume has been turned [ OFF ]. If you wish to turn it back on, use \"on\" (no quotation marks). If you wish to leave it off instead, simply type \"exit\" to return to the main menu.\n";
            cout<<"[*] If you wish to use another command, use \"help\" to see a list of available commands!\n\n";
            Sound();
        } else {
            cout<<"\n[!] Volume is already [ OFF ]. If you instead wanted to use another command, use \"help\" to see a list of all available ocmmands.\n\n";
            Sound();
        }
        
    } else if (soundSettings == "on") {
        if (Volume != "On") {
            Volume = "On";
            cout<<"\n[!] Volume has been turned [ ON ]. If you wish to turn it off, use \"off\" (no quotation marks). If you instead wish to leave it on, simply type \"exit\" to return to the main menu.\n";
            cout<<"[*] If you wish to use another command, use \"help\" to see a list of available commands!\n\n";
            Sound();
        } else {
            cout<<"\n[!] Volume is already [ ON ]. If you instead wanted to use another command, use \"help\" to see a list of all available ocmmands.\n\n";
            Sound();
        }
        
    } else if (soundSettings == "exit") {
        cout<<"[!] Returning to the main menu. Please wait...";
        std::this_thread::sleep_for(std::chrono::seconds(randomness));
        system("cls");
        ShowScreen();
        chosenOption = "Options";
        ShowButtons();
        cout<<endl<<endl<<"[*] If you wish to start the game, press Enter. Otherwise, if you wish to modify some settings, type 's' to move to the Options menu, and press Enter to access it.\n"<<"                                                            ";
        Selector();
    } else if (soundSettings == "help") {
        cout<<"\n[*] Here's a list of all currently available commands: \n\n";
        cout<<"- off | Turn volume off\n"<<
        "- on | Turn volume back on\n"<<
        "- test | Test if you have the volume turned on or off\n"<<
        "- help | Show all available commands\n"<<
        "- exit | Exit out of this menu\n"<<
        "- code | ???\n\n";
        Sound();
    } else if (soundSettings == "code") {
        cout<<"[?] Up up down down left right left right b a\n";
        cout<<"[*] If you wish to use any other command, use \"help\" to see a list of all of them!\n\n";
        Sound();
    } else {
        cout<<"\n[?] Unknown command. Try to rewrite it, though if you do not remember the exact syntax, do make use of the following menu: \n";
        cout<<"- off | Turn volume off\n"<<
        "- on | Turn volume back on\n"<<
        "- test | Test if you have the volume turned on or off\n"<<
        "- help | Show all available commands\n"<<
        "- exit | Exit out of this menu\n"<<
        "- code | ???\n\n";
        Sound();
    } 
}

Player::Player(short int n) { airplaneNumber = n; }

int Human::ReturnNumberOfAirplanes() { return humanAirplanes; }

int Robot::ReturnNumberOfAirplanes() { return robotAirplanes; }

Human::Human(const Player& k) { humanAirplanes = k.airplaneNumber; }

Robot::Robot(const Player& l) { robotAirplanes = l.airplaneNumber; }

void ConvertorCoord(Airplane& a) {
    for (int i = 0; i < 10; i++)
        if (a.vCoord == letters[i]) {
            a.vCoordConv = i+1;
            break;
        }
}



void AirplaneConfig() {
    if (o.humanAirplanes > 0 && o.humanAirplanes <= 3) {
      //Read direction
      if (config == 1) {
        switch (airplaneSetup) {
            case 1:
                cout<<"[*] What direction should the FIRST airplane have? Horizontal or vertical?";
                break;
            case 2:
                cout<<"[*] What direction should the SECOND airplane have? Horizontal or vertical?";
                break;
            case 3:
                cout<<"[*] What direction should the THIRD airplane have? Horizontal or vertical?";
                break;
        }
      cout<<"\n[!] The answer must be either horizontal or vertical!\n\n>> I think I'd like the airplane to have its' direction as... ";
        std::getline(cin, o.decision);
        while (o.decision != "horizontal" && o.decision != "vertical") {
             cout<<"as... ";
             std::getline(cin, o.decision);
        }
        if (o.decision == "horizontal") {
            switch (airplaneSetup) {
            case 1:
                A1.direction = "horizontal";
                break;
            case 2:
                A2.direction = "horizontal";
                break;
            case 3:
                A3.direction = "horizontal";
                break;
        }
      } else if (o.decision == "vertical") {
        switch (airplaneSetup) {
            case 1:
                A1.direction = "vertical";
                break;
            case 2:
                A2.direction = "vertical";
                break;
            case 3:
                A3.direction = "vertical";
                break;
        }
      } 
     cout<<"\n[*] Airplane "<<airplaneSetup<<" will have the following direction: [ "<<o.decision<<" ]\n\n";
     //Read orientation
      }
      config = 2;
     if (o.decision == "horizontal" && config == 2) {
        switch (airplaneSetup) {
            case 1: 
                cout<<"[*] What orientation do you wish for the FIRST airplane to have? Facing left or right?";
                break;
            case 2:
                cout<<"[*] What orientation do you wish for the SECOND airplane to have? Facing left or right?";
                break;
            case 3:
                cout<<"[*] What orientation do you wish for the THIRD airplane to have? Facing left or right?";
                break;
        }
        cout<<"\n[!] The answer must be either left or right!\n\n>> I think I'd like the airplane to be orientated towards... ";
        std::getline(cin, o.decision);
        while(o.decision!= "left" && o.decision != "right") {
            cout<<"towards... ";
            std::getline(cin, o.decision);
    }

      if (o.decision == "left") {
        switch (airplaneSetup) {
            case 1:
                A1.orientation = "left";
                break;
            case 2:
                A2.orientation = "left";
                break;
            case 3:
                A3.orientation = "left";
                break;
        }
      } else if (o.decision == "right") {
        switch (airplaneSetup) {
            case 1:
                A1.orientation = "right";
                break;
            case 2:
                A2.orientation = "right";
                break;
            case 3:
                A3.orientation = "right";
                break;
        }
      }
      cout<<"\n[*] Airplane "<<airplaneSetup<<" will have the following orientation: [ "<<o.decision<<" ]\n\n";
     } else if (o.decision == "vertical" && config == 2) {
        switch (airplaneSetup) {
            case 1:
                cout<<"[*] What orientation do you wish for the FIRST airplane to have? Upwards or downwards?";
                break;
            case 2:
                cout<<"[*] What orientation do you wish for the SECOND airplane to have? Upwards or downwards?";
                break;
            case 3:
                cout<<"[*] What orientation do you wish for the THIRD airplane to have? Upwards or downwards?";
                break;
        }
        cout<<"\n[!] The answer must be either up or down!\n\n>> I think I'd like the airplane to be orientated towards... ";
        std::getline(cin, o.decision);
        while (o.decision != "up" && o.decision != "down") {
            cout<<"towards... ";
            std::getline(cin, o.decision);
    }
      if (o.decision == "up") {
        switch (airplaneSetup) {
            case 1:
                A1.orientation = "up";
                break;
            case 2:
                A2.orientation = "up";
                break;
            case 3:
                A3.orientation = "up";
                break;
        }
      } else if (o.decision == "down") {
        switch (airplaneSetup) {
            case 1:
                A1.orientation = "down";
                break;
            case 2:
                A2.orientation = "down";
                break;
            case 3:
                A3.orientation = "down";
                break;
        }
      }
      cout<<endl;
      cout<<"[*] Airplane "<<airplaneSetup<<" will have the following orientation: [ "<<o.decision<<" ]\n\n";
     }
     config = 3;
     //Read position
     if (config == 3) {
        cout<<"[*] Choose the position of the airplane. The answer has to follow the format LETTERNUMBER (example: C2).\n";
        cout<<"[*] Furthermore, the position you will provide will represent the BEGINNING of the airplane, which means the farthest box from the vertex in the middle (vertex position -3).\n\n";
        switch (airplaneSetup) {
            case 1:
                cout<<">> The first airplane will start from... ";
                break;
            case 2:
                cout<<">> The second airplane will start from... ";
                break;
            case 3:
                cout<<">> The third airplane will start from... ";
                break;
        }
        std::getline(cin, o.decision); 
        while (!AnswerFormat(o.decision)) {
            cout<<"from... ";
            std::getline(cin, o.decision);
        }
        switch (airplaneSetup) {
            case 1:
                Judgeman(A1);
                break;
            case 2:
                Judgeman(A2);
                break;
            case 3:
                Judgeman(A3);
                break;
        }
     }

     
     //The airplane will begin from the position you mention, starting from the farthest box in the middle
     /*Ex:    
                                    X
                                X   X
        It will begin here ->   X X X >
                                X   X
                                    X
     */
     
   }
}



void Player::ShowTable() {
   passed1 = false, passed2 = false;
   //Set airplane plane
   for (int i = 0; i < 10; i++) 
      for (int j = 0; j < 10; j++) 
        PO.plane[i][j] = (j == 9 ? tmp1 + tmp2 + tmp3 : tmp1 + tmp2 + tmp2);
   if (finishedAirplane1) 
    ShowAirplanesOnTable(A1, 0, PO, airplaneMatrix, humanAirplaneVertices);
   if (finishedAirplane2) 
    ShowAirplanesOnTable(A2, 1, PO, airplaneMatrix, humanAirplaneVertices);
   if (finishedAirplane3) 
    ShowAirplanesOnTable(A3, 2, PO, airplaneMatrix, humanAirplaneVertices);
   //Set attack plane
   for (int i = 0; i < 10; i++) 
      for (int j = 0; j < 10; j++) 
         PAO.attack[i][j] = (j == 9 ? tmp1 + FULL_SQUARE + tmp3 : tmp1 + FULL_SQUARE + tmp2);

   if (attackPhase) {
    //Airplane plane
    for (int i = 0; i < 10; i++) 
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < hitHuman.size(); k++) 
                if ((std::to_string(i) + std::to_string(j)) == hitHuman[k]) 
                    PO.plane[i][j] = (j == 9 ? "| X |" : "| X ");

            for (int s = 0; s < dodgedHuman.size(); s++) 
                if ((std::to_string(i) + std::to_string(j)) == dodgedHuman[s]) 
                    PO.plane[i][j] = (j == 9 ? "| O |" : "| O ");
    }

    //Attack plane
    for (int i = 0; i < 10; i++) 
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < hit.size(); k++) 
                if ((std::to_string(i) + std::to_string(j)) == hit[k]) 
                    PAO.attack[i][j] = (j == 9 ? "| X |" : "| X ");

            for (int l = 0; l < dodged.size(); l++) 
                if ((std::to_string(i) + std::to_string(j)) == dodged[l]) 
                    PAO.attack[i][j] = (j == 9 ? "|   |" : "|   ");
    } 
}
   //Show table
   cout<<"                        A   B   C   D   E   F   G   H   I   J                           A   B   C   D   E   F   G   H   I   J\n";
   cout<<"                       _______________________________________                         _______________________________________\n";
   for (int i = 0; i < 10; i++) {
      cout<<(i == 9 ? "                  " : "                   ")<<i+1<<"  ";
      for (int j = 0; j < 10; j++) 
         cout<<PO.plane[i][j];
      cout<<(i == 9 ? "                   " : "                    ")<<i+1<<"  ";
      for (int k = 0; k < 10; k++) 
         cout<<PAO.attack[i][k];
      cout<<endl;
   }
   cout<<"                       ---------------------------------------                         ---------------------------------------\n";
   cout<<"                                   AIRPLANE PLANE                                                    ATTACK PLANE\n\n";
   if (airplaneSetup == 4) {
    if (o.ReturnCheatMode())
        if (robo.ReturnNumberOfAirplanes() != 0 && o.ReturnNumberOfAirplanes() != 0)
            cout<<"\n[*] In order to access the special menu, write the following when prompted to attack: Sesame\n\n";
   }
        
   if (!guardian)
        Game();
}



void Verify() {
    if (!passed1 || !passed2) {
            config = 3;
            cout<<"\n[X] You cannot place the airplane in that position! Please choose another one.\n\n";
            AirplaneConfig();
    }
}



void Judgeman(Airplane& a) {
        passed1 = false, passed2 = false;
        a.vCoord = o.decision[0];
        ConvertorCoord(a);
        if (o.decision.size() == 3) 
            a.oCoordConv = 10;
        else if (o.decision.size() == 2) {
            a.oCoord = o.decision[1];
            a.oCoordConv = std::stoi(a.oCoord);   //string to int
        }
        if (a.direction == "horizontal") {
            if (a.orientation == "right") {
                if (a.vCoordConv <= 7 && a.vCoordConv >= 1) {
                    passed1 = true;
                    passed2 = (a.oCoordConv <= 8 && a.oCoordConv >= 3) ? true : false;
                }
                Verify();
            } else if (a.orientation == "left") {
                if (a.vCoordConv > 3 && a.vCoordConv <= 10) {
                    passed1 = true;
                    passed2 = (a.oCoordConv <= 8 && a.oCoordConv >= 3) ? true : false;
                }
                Verify();
            }
        } else if (a.direction == "vertical") {
            if (a.orientation == "up") {
                if (a.vCoordConv >= 3 && a.vCoordConv <= 8) {
                    passed1 = true;
                    passed2 = (a.oCoordConv <= 10 && a.oCoordConv >= 4) ? true : false;
                }
                Verify();
            } else if (a.orientation == "down") {
                if (a.vCoordConv >= 3 && a.vCoordConv <= 8) {
                    passed1 = true;
                    passed2 = (a.oCoordConv <= 7 && a.oCoordConv >= 1) ? true : false;
                }
                Verify();
            }
        }
        if (passed1 && passed2) {
            if (airplaneSetup == 1) {
                cout<<"\n[*] Airplane "<<airplaneSetup<<" will have the following position: [ "<<o.decision<<" ]\n\n";
                finishedAirplane1 = true;
            }
            else if (airplaneSetup == 2) {
                while (IsOverlap(airplaneMatrix, 2, "human")) {
                    cout<<"[X] You cannot place the airplane in that position, due to either there being an overlap with another airplane or an invalid provided position. Try again.\n\n";
                    AirplaneConfig();
                }
                cout<<"\n[*] Airplane "<<airplaneSetup<<" will have the following position: [ "<<o.decision<<" ]\n\n";
                finishedAirplane2 = true;
            }
            else if (airplaneSetup == 3) {
                while (IsOverlap(airplaneMatrix, 3, "human")) {
                    cout<<"[X] You cannot place the airplane in that position, due to either there being an overlap with another airplane or an invalid position. Try again.\n\n";
                    AirplaneConfig();
                }
                cout<<"\n[*] Airplane "<<airplaneSetup<<" will have the following position: [ "<<o.decision<<" ]\n\n";
                finishedAirplane3 = true;
            }
            airplaneSetup++;
            config = 1;
            cout<<endl;
            system("pause");
            system("cls");
            cout<<endl;
            Player::ShowTable();
        }
}



void ShowAirplanesOnTable(Airplane a, int n, Player::AirplanePlane& P, string v[3][10], string vertices[3]) {
    if (a.direction == "horizontal") {
        if (a.orientation == "right") {
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][0] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][1] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][2] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);

            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv] = tmp1 + FULL_SQUARE + tmp2;
            v[n][3] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv);

            
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv+1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][4] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv+1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv+1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][5] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv+1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv+1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][6] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv+1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv+1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][7] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv+1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv+1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][8] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv+1);
            if (a.vCoordConv != 7)
                P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 +3] = "| > ";
            else 
                P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 +3] = "| > |";
            //Vertex gets saved last
            v[n][9] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +3);
            vertices[n] = v[n][9];
                
        } else if (a.orientation == "left") {
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -3] = "| < ";
            //Save vertex first
            v[n][0] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -3);
            vertices[n] = v[n][0];
            
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -2] = tmp1 + FULL_SQUARE + tmp2;
            v[n][1] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1 -2] = tmp1 + FULL_SQUARE + tmp2;
            v[n][2] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 -2] = tmp1 + FULL_SQUARE + tmp2;
            v[n][3] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1 -2] = tmp1 + FULL_SQUARE + tmp2;
            v[n][4] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 -2] = tmp1 + FULL_SQUARE + tmp2;
            v[n][5] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2);

            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][6] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1);
            
            if (a.vCoordConv != 10) {
                P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
                v[n][7] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
                P.plane[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
                v[n][8] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
                P.plane[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
                v[n][9] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            } else {
                P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp3;
                v[n][7] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
                P.plane[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp3;
                v[n][8] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
                P.plane[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp3;
                v[n][9] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            }
        }
    } else if (a.direction == "vertical") {
        if (a.orientation == "up") {
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -3][ApYPlaneIndex+a.vCoordConv-1] = "| ^ ";
            //Save vertex first
            v[n][0] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -3) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            vertices[n] = v[n][0];

            P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 -2] = tmp1 + FULL_SQUARE + tmp2;
            v[n][1] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 -1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][2] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][3] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 +1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][4] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1);
            if (a.vCoordConv != 8)
                P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 +2] = tmp1 + FULL_SQUARE + tmp2;
            else 
                P.plane[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 +2] = tmp1 + FULL_SQUARE + tmp3;
            v[n][5] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +2);

            P.plane[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][6] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);

            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][7] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][8] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 +1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][9] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1);
        } else if (a.orientation == "down") {
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][0] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][1] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 +1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][2] = std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1);

            P.plane[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][3] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);

            P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 -2] = tmp1 + FULL_SQUARE + tmp2;
            v[n][4] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 -1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][5] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][6] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 +1] = tmp1 + FULL_SQUARE + tmp2;
            v[n][7] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1);
            if (a.vCoordConv != 8) 
                P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 +2] = tmp1 + FULL_SQUARE + tmp2;
            else 
                P.plane[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 +2] = tmp1 + FULL_SQUARE + tmp3;
            v[n][8] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +2);

            P.plane[ApXPlaneIndex+a.oCoordConv-1 +3][ApYPlaneIndex+a.vCoordConv-1] = "| v ";
            //Save vertex last
            v[n][9] = std::to_string(ApXPlaneIndex+a.oCoordConv-1 +3) + std::to_string(ApYPlaneIndex+a.vCoordConv-1);
            vertices[n] = v[n][9];
        }
    }
}



bool IsOverlap(string v[3][10], int n, string who) {
    bool overlap = false;
    if (n == 2) {
            if (who == "human")
                ShowAirplanesOnTable(A2, 1, PO, airplaneMatrix, humanAirplaneVertices);
            else if (who == "robot")
                ShowAirplanesOnTable(R2, 1, PR, robotAirplaneMatrix, humanAirplaneVertices);
            for (int i = 0; i < 10; i++) 
                for (int j = 0; j < 10; j++) 
                    if (v[1][j] == v[0][i]) 
                        overlap = true;
    } else if (n == 3) {
        if (who == "human")
            ShowAirplanesOnTable(A3, 2, PO, airplaneMatrix, humanAirplaneVertices);
        else if (who == "robot")
            ShowAirplanesOnTable(R3, 2, PR, robotAirplaneMatrix, humanAirplaneVertices);
        for (int j = 0; j < 10; j++) 
            for (int k = 0; k < 10; k++) 
                if (v[2][k] == v[1][j] || v[2][k] == v[0][j]) 
                    overlap = true;
    }  
    return overlap;
}



bool AnswerFormat(string s) {
    bool comparison;
    for (int i = 0; i < 10; i++) {
        if (comparison) 
            break;
        for (int j = 0; j < 10; j++) {
            if (s == (letters[i] + std::to_string(j+1))) {
                comparison = true;
                break;
            } else if (s == "Sesame")
                if (o.ReturnCheatMode())
                    comparison = true;
             else 
                if (o.ReturnCheatMode())
                    comparison = false;        
    }
}
    return (!comparison ? false : true);
}



void Robot::SetActivity(bool active) { this->active = active; }

void Human::VerifyHit() {
     if (robo.ReturnNumberOfAirplanes() == 0) {
        guardian = true;
        system("pause");
        system("cls");
        Player::ShowTable(); 
        cout<<"\n\n[!] Congratulations! You have destroyed all enemy airplanes. You won!\n";
        cout<<"[ "<<sistem.ShowSystemInfo()<<" ] You earned ";
        sistem.SetHumanPoints(100+rand()%501);
        cout<<sistem.ReturnHumanPoints()<<" points!\n\n";
        //cout<<"[*] Game has finished!\n\n";
        //system("pause");
        exit(-1);             
     }
    string attackPosition, aux1, aux2;
    int aux4, aux5, aux6;
    cout<<"[*] Please provide the position you wish to attack: \n";
    cout<<"[O] Attack ";
    std::getline(cin, attackPosition);
    while (!AnswerFormat(attackPosition)) {
        cout<<"[X] Unknown position. Try again, using the LETTERNUMBER model (example: C2).\n";
        cout<<"[O] Attack ";
        std::getline(cin, attackPosition);
    }
    if (attackPosition != "Sesame") {
    //Read A8 for instance
    aux1 = attackPosition[0]; //Holds A
    if (attackPosition.size() < 3) 
        aux2 = attackPosition[1]; //Holds 8 
     else {
        string auxi;
        auxi = attackPosition[2];
        aux2 = (auxi == "0") ? std::to_string(10) : auxi;
        //Will 100% be 10, so we'll have something like J10 for example
    } 

    finished = aux2 + std::to_string(ConvertPosition(aux1)); // finished will hold the position in string form: ROW COLUMN; ConvertPosition(aux1) will return the equivalent of the specified letter as a number; Example: A8 will turn into 81
    
    aux4 = std::stoi(finished); //aux4 = int finished
    if (aux4 < 110) {
            aux5 = aux4/10; //aux5 - horizontal coordinate, aux6 for vertical
            aux5 -= 1;
            aux6 = aux4%10;
            aux6 -= 1; 
    } else {
            aux5 = aux4/10/10; 
            aux5 -= 1;
            aux6 = 10; 
            aux6 -= 1;
    }
    while (hasAttackedAgain[aux5][aux6]) {
        cout<<"\n[X] You've already attacked that position! Please provide another target."<<endl<<endl;
        o.VerifyHit();
    }
    if (!hasAttackedAgain[aux5][aux6]) 
        hasAttackedAgain[aux5][aux6] = true;
    finished = std::to_string(aux5) + std::to_string(aux6); 
    //Make finished equal to aux4 from int to string in order to attain the correct position with which we will use for comparison
    int tempCounter = 0, anotherCounter = 0;
    for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 10; j++) {
                if (finished == robotAirplaneMatrix[i][j]) {
                    if (Volume == "On")
                        cout<<endl<<"\a[!] Hit! Your turn continues.\n";
                    else if (Volume == "Off")
                        cout<<endl<<"[!] Hit! Your turn continues.\n";
                    if (finished == robotAirplaneVertices[i]) {
                        if (Volume == "On")
                            cout<<"\a[!] You've hit the vertex of an airplane! As a result, the entire airplane is destroyed. Congratulations!\n\n";
                        else if (Volume == "Off")
                            cout<<"[!] You've hit the vertex of an airplane! As a result, the entire airplane is destroyed. Congratulations!\n\n";
                        switch(i) {
                            case 0:
                                o.VerifyHitVertex(1);
                                robotAirplaneVertices[0] = "X";
                                break;
                            case 1:
                                o.VerifyHitVertex(2);
                                robotAirplaneVertices[1] = "X";
                                break;
                            case 2:
                                o.VerifyHitVertex(3);
                                robotAirplaneVertices[2] = "X";
                                break;
                        }
                        robo.ModifyNumberOfAirplanesRobot(robo);
                        robo.ShowNumberOfAirplanesLeftRobot(robo);       
                    }
                    hit.push_back(finished);
                    attackPhase = true;
                    tempCounter  = 1;
                    anotherCounter = 4;
                    o.VerifyHit();
                } else 
                    if (anotherCounter == 2) 
                        if (j == 9) 
                            if (tempCounter == 0) {
                            cout<<"[*] Missed! It's the bot's turn now.\n\n"<<"------------------------------------------\n";
                            dodged.push_back(finished);
                            attackPhase = true;
                            tempCounter = 1;
                            cout<<endl;
                            //system("pause");
                            //system("cls");
                            robo.Attack();
                        }
        }
        anotherCounter++;
    }
    } else {
        continueAttacking = false;
        SpecialMenu menu;
        cout<<menu<<endl;
        menu.Menu(menu);
    }
    
}

void Human::Attack() {
    //Verify if we hit something
    o.VerifyHit();
    guardian = true;
    if (!o.ReturnCheatMode()) {
            system("pause");
            system("cls");
            Player::ShowTable(); 
    }
    if (continueAttacking) {
        system("pause");
        system("cls");
        Player::ShowTable(); 
    }

}


int ConvertPosition(string s) {
    int aux3;
    for (int i = 0; i < 10; i++)
        if (s == letters[i])
            aux3 = i+1;
    return aux3;
}



void Player::VerifyVertex(Airplane a, vector <string>& v) {
    if (a.direction == "horizontal") {
        if (a.orientation == "right") {
            //Vertex
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +3));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv+1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv+1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv+1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv+1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv+1));
            
        }
            
        else if (a.orientation == "left") {
            //Vertex
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -3));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));

            }
            
    } else if (a.direction == "vertical") {
        if (a.orientation == "up") {
            //Vertex
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -3) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +2));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 -1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1));
        }
            
        else if (a.orientation == "down") {
            //Vertex
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +3) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +1) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));

            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -2));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 -1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +1));
            v.push_back(std::to_string(ApXPlaneIndex+a.oCoordConv-1 +2) + std::to_string(ApYPlaneIndex+a.vCoordConv-1 +2));
        }
    } 
}


void Robot::ModifyNumberOfAirplanesRobot(Robot& r) { r.robotAirplanes--; }

void Human::ModifyNumberOfAirplanesRobot(Human& o) { o.humanAirplanes--; }

void Robot::ShowNumberOfAirplanesLeftRobot(Robot& r) {
    if (r.robotAirplanes != 1) {
        if (r.robotAirplanes != 0) 
            cout<<"[*] The bot has "<<r.robotAirplanes<<" airplanes left."<<endl<<endl;
         else 
            cout<<"[X] The bot has no more airplanes left."<<endl<<endl;
    }
    else 
        cout<<"[*] The bot has "<<r.robotAirplanes<<" airplane left."<<endl;
}


void Human::VerifyHitVertex(int n) {
    switch(n) {
        case 1:
            VerifyVertex(R1, hit);
            o.MarkAsAttacked(R1, hasAttackedAgain);
            break;
        case 2:
            VerifyVertex(R2, hit);
            o.MarkAsAttacked(R2, hasAttackedAgain);
            break;
        case 3:
            VerifyVertex(R3, hit);
            o.MarkAsAttacked(R3, hasAttackedAgain);
            break;
    }   
}

void Human::MarkAsAttacked(Airplane a, bool (&v)[10][10]) {
        if (a.direction == "horizontal") {
                if (a.orientation == "right") {
                    //Vertex
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 +3] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv+1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv+1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv+1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv+1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv+1] = true;
                    
                }
                    
                else if (a.orientation == "left") {
                    //Vertex
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -3] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -2] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1 -2] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 -2] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1 -2] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 -2] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -1] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1] = true;

                 }
                    
            } else if (a.direction == "vertical") {
                if (a.orientation == "up") {
                    //Vertex
                    v[ApXPlaneIndex+a.oCoordConv-1 -3][ApYPlaneIndex+a.vCoordConv-1] = true;
                    
                    v[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 -2] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 -1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 +1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 -2][ApYPlaneIndex+a.vCoordConv-1 +2] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1 -1][ApYPlaneIndex+a.vCoordConv-1] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 +1] = true;
                }
                 
                else if (a.orientation == "down") {
                    //Vertex
                    v[ApXPlaneIndex+a.oCoordConv-1 +3][ApYPlaneIndex+a.vCoordConv-1] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 -1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1][ApYPlaneIndex+a.vCoordConv-1 +1] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1 +1][ApYPlaneIndex+a.vCoordConv-1] = true;

                    v[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 -2] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 -1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 +1] = true;
                    v[ApXPlaneIndex+a.oCoordConv-1 +2][ApYPlaneIndex+a.vCoordConv-1 +2] = true;
                }   
            } 
}

void Robot::VerifyHitVertex(int n) {
    switch(n) {
        case 1:
            VerifyVertex(A1, hitHuman);
            break;
        case 2:
            VerifyVertex(A2, hitHuman);
            break;
        case 3:
            VerifyVertex(A3, hitHuman);
            break;
    }        
}

bool SpecialMenu::VerifyCommand(string& s) {
    if(s != "show --all" && s != "show --vertices" && s != "destroy --all" &&
       s != "destroy --A1" && s != "destroy --A2" && s != "destroy --A3" && s != "help" && s != "exit") 
        return false;
    else 
        return true;           
}


std::istream & operator >> (std::istream& read, SpecialMenu& m) {
    std::getline(read, m.command);
    return read;
}

std::ostream & operator << (std::ostream& write, SpecialMenu& m) {
    write<<R"(
                                     __  ____   ____   ___ __  ___  __       ___  ___  ____ __  __ __ __
                                    (( \ || \\ ||     //   || // \\ ||       ||\\//|| ||    ||\ || || ||
                                     \\  ||_// ||==  ((    || ||=|| ||       || \/ || ||==  ||\\|| || ||
                                    \_)) ||    ||___  \\__ || || || ||__|    ||    || ||___ || \|| \\_//



                            /-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\|/-\
                            |                                                                                 |
                            \      Available commands:                                                        /
                            -      -------------------                                                        -
                            /                                                                                 \
                            |      show [--option]                                                            |
                            \         | - all  -> Displays the positions and vertices of each enemy airplane  /
                            -         | - vertices -> Only displays the vertices of each enemy airplane       -
                            /                                                                                 \
                            |                                                                                 |
                            \                                                                                 /
                            -      Usage example: show --all                                                  -
                            /                                                                                 \
                            |                                                                                 |
                            \      destroy [--option]                                                         /
                            -         | - all -> Destroys all enemy airplanes in one hit                      -
                            /         | - A[number] -> Only destroys the specified enemy airplane             \
                            |                                                                                 |
                            \                                                                                 /
                            -      Usage example: destroy --A3  -> Will only destroy the 3rd enemy airplane   -
                            /                                                                                 \
                            |                                                                                 |
                            \      help -> Shows this menu                                                    /
                            -                                                                                 -
                            /      exit -> Exits out of this menu                                             \
                            |                                                                                 |
                            \-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/|\-/
                            
    )"<<endl<<endl;
    return write;
}

vector <string> InvertConversion(string (&s)[3][10]) {
    string aux, aux1, aux2;
    vector <string> allPositions;
    for (int i = 0; i < 3; i++) 
            for (int j = 0; j < 10; j++) {
                aux = s[i][j];
                aux1 = aux[0], aux2 = aux[1];
                //Vertical coordinate
                if (aux2 == std::to_string(0)) 
                    aux2 = "A";
                else if (aux2 == std::to_string(1)) 
                    aux2 = "B";
                else if (aux2 == std::to_string(2)) 
                    aux2 = "C";
                else if (aux2 == std::to_string(3)) 
                    aux2 = "D";
                else if (aux2 == std::to_string(4)) 
                    aux2 = "E";
                else if (aux2 == std::to_string(5)) 
                    aux2 = "F";
                else if (aux2 == std::to_string(6)) 
                    aux2 = "G";
                else if (aux2 == std::to_string(7)) 
                    aux2 = "H";
                else if (aux2 == std::to_string(8)) 
                    aux2 = "I";
                else if (aux2 == std::to_string(9)) 
                    aux2 = "J";
                //Horizontal coordinate
                if (aux1 == std::to_string(0)) 
                    aux1 = "1";
                 else if (aux1 == std::to_string(1)) 
                    aux1 = "2";
                 else if (aux1 == std::to_string(2)) 
                    aux1 = "3";
                 else if (aux1 == std::to_string(3)) 
                    aux1 = "4";
                 else if (aux1 == std::to_string(4)) 
                    aux1 = "5";
                 else if (aux1 == std::to_string(5)) 
                    aux1 = "6"; 
                 else if (aux1 == std::to_string(6)) 
                    aux1 = "7";
                 else if (aux1 == std::to_string(7)) 
                    aux1 = "8";
                 else if (aux1 == std::to_string(8)) 
                    aux1 = "9";
                 else if (aux1 == std::to_string(9)) 
                    aux1 = "10";
                aux = aux2 + aux1;
                allPositions.push_back(aux);
}
    
        return allPositions;
}

vector <string> InvertVerticesCoord(string (&v)[3]) {
    vector <string> vertices;
    string aux, aux1, aux2;
    for (int i = 0; i < 3; i++) {
        aux = v[i];
        aux1 = aux[0], aux2 = aux[1];
        //Horizontal coordinate
        if (aux2 == std::to_string(0))
            aux2 = "A";
        else if (aux2 == std::to_string(1)) 
            aux2 = "B";
        else if (aux2 == std::to_string(2)) 
            aux2 = "C";
        else if (aux2 == std::to_string(3)) 
            aux2 = "D";
        else if (aux2 == std::to_string(4)) 
            aux2 = "E";
        else if (aux2 == std::to_string(5)) 
            aux2 = "F";
        else if (aux2 == std::to_string(6)) 
            aux2 = "G";
        else if (aux2 == std::to_string(7)) 
            aux2 = "H";
        else if (aux2 == std::to_string(8)) 
            aux2 = "I";
        else if (aux2 == std::to_string(9)) 
            aux2 = "J";
        //Vertical coordinate
        if (aux1 == std::to_string(0)) 
            aux1 = "1";
        else if (aux1 == std::to_string(1)) 
            aux1 = "2";
        else if (aux1 == std::to_string(2)) 
            aux1 = "3";
        else if (aux1 == std::to_string(3)) 
            aux1 = "4";
        else if (aux1 == std::to_string(4)) 
            aux1 = "5";
        else if (aux1 == std::to_string(5)) 
            aux1 = "6"; 
        else if (aux1 == std::to_string(6)) 
            aux1 = "7";
        else if (aux1 == std::to_string(7)) 
            aux1 = "8";
        else if (aux1 == std::to_string(8)) 
            aux1 = "9";
        else if (aux1 == std::to_string(9)) 
            aux1 = "10";
        aux = aux2 + aux1;
        vertices.push_back(aux);
    }
    return vertices;
}

void SpecialMenu::Menu(SpecialMenu& me) {
    vector <string> botPositions = InvertConversion(robotAirplaneMatrix);
    vector <string> botVertices = InvertVerticesCoord(robotAirplaneVertices);
    cout<<"[*] Please type the command you wish to use. If you don't know which commands are available, use \"help\" (no quotation mark)\n>>";
    cin>>me;
    while (!me.VerifyCommand(me.command)) {
        cout<<"\n[X] Unknown command. Use \"help\" to see a list of all available commands.\n>>";
        cin>>me;
    }
    if (me.command == "help") {
        cout<<me<<endl;
        me.Menu(me);
    } else if (me.command == "show --all") {
        cout<<endl<<"[*] Here's where each enemy airplane is situated: \n\n";
        //We know that we will have 30 elements, so we show each of them
        cout<<"[*] First airplane: ";
        for (int i = 0; i < 10; i++) 
            cout<<botPositions[i]<<" ";
        cout<<" | direction: "<<R1.direction<<" | orientation: "<<R1.orientation<<endl;
        cout<<"[*] Second airplane: ";
        for (int i = 10; i < 20; i++) 
            cout<<botPositions[i]<<" ";
        cout<<" | direction: "<<R2.direction<<" | orientation: "<<R2.orientation<<endl;
        cout<<"[*] Third airplane: ";
        for (int i = 20; i < 30; i++) 
            cout<<botPositions[i]<<" ";
        cout<<" | direction: "<<R3.direction<<" | orientation: "<<R3.orientation<<endl<<endl;
    } else if (me.command == "show --vertices") {
        cout<<"[*] Here is every enemy airplane vertex: \n\n";
        for (int i = 0; i < 3; i++)  
            cout<<botVertices[i]<<" ";
        cout<<endl<<endl;
    } else if (me.command == "exit") {
        cout<<endl;
        continueAttacking = true;
        o.Attack();
    } else if (me.command == "destroy --all") {
        attackPhase = true;
        VerifyVertex(R1, hit);
        VerifyVertex(R2, hit);
        VerifyVertex(R3, hit);
        airplaneSetup++;
        Player::ShowTable();
        AfterDestruction();
        cout<<"\n[V] All enemy airplanes have been destroyed. You won!\n";
        cout<<"[ "<<sistem.ShowSystemInfo()<<" ] You earned  ";
        sistem.SetHumanPoints(100+rand()%501);
        cout<<sistem.ReturnHumanPoints()<<" points!\n\n";
        //cout<<"[*] Game has finished!\n\n";
        //system("pause");
        exit(-1);
    } else if (me.command == "destroy --A1") {
        while (destroyedAirplane[0]) {
            cout<<"[X] The first enemy airplane has already been destroyed. If you wish to destroy another, use either --A2 or --A3, provided they haven't been destroyed either.\n\n";
            me.Menu(me);
        }
        attackPhase = true;
        VerifyVertex(R1, hit);
        AfterDestruction();
        robo.ModifyNumberOfAirplanesRobot(robo);
        robotAirplaneVertices[0] = "X";
        destroyedAirplane[0] = true;
        cout<<"\n";
        Player::ShowTable();
        cout<<"\n[V] The first enemy airplane has been destroyed.\n";
        robo.ShowNumberOfAirplanesLeftRobot(robo);
    } else if (me.command == "destroy --A2") {
        while (destroyedAirplane[1]) {
            cout<<"[X] The second enemy airplane has already been destroyed. If you wish to destroy another, use either --A1 or --A3, provided they haven't been destroyed either.\n\n";
            me.Menu(me);
        }
        attackPhase = true;
        VerifyVertex(R2, hit);
        AfterDestruction();
        robo.ModifyNumberOfAirplanesRobot(robo);
        robotAirplaneVertices[1] = "X";
        destroyedAirplane[1] = true;
        cout<<"\n";
        Player::ShowTable();
        cout<<endl<<"[V] The second enemy airplane has been destroyed.\n";
                robo.ShowNumberOfAirplanesLeftRobot(robo);
    } else if (me.command == "destroy --A3") {
        while (destroyedAirplane[2]) {
            cout<<"[X] The third enemy airplane has already been destroyed. If you wish to destroy another, use either --A1 or --A2, provided they haven't been destroyed either.\n\n";
            me.Menu(me);
        }
        attackPhase = true;
        VerifyVertex(R3, hit);
        AfterDestruction();
        robo.ModifyNumberOfAirplanesRobot(robo);
        robotAirplaneVertices[2] = "X";
        destroyedAirplane[2] = true;
        cout<<"\n";
        Player::ShowTable();
        cout<<"\n[V] The third enemy airplane has been destroyed.\n";
        robo.ShowNumberOfAirplanesLeftRobot(robo);   
    }
        if (robo.ReturnNumberOfAirplanes() != 0) 
            me.Menu(me);
        else {
            system("cls");
            Player::ShowTable();
            cout<<"\n\n[!] Congratulations! You have destroyed all enemy airplanes. You won!\n";
            cout<<"[ "<<sistem.ShowSystemInfo()<<" ] You earned ";
            sistem.SetHumanPoints(100+rand()%501);
            cout<<sistem.ReturnHumanPoints()<<" points!\n\n";
            //cout<<"[*] Game has finished!\n\n";
            //system("pause");
            exit(-1);
        }
        
}


void StopVerifying(bool (&b)[10][10], bool (&c)[10][10], bool (&d)[10][10], bool (&e)[10][10]) {
    for (int i = 0; i < 10; i++) 
        for (int j = 0; j < 10; j++) {
            b[i][j] = false;
            c[i][j] = false;
            d[i][j] = false;
            e[i][j] = false;
        }
}


void SetHowManyTimesTheyAttacked(bool (&b)[10][10]) {
    for (int i = 0; i < 10; i++) 
        for (int j = 0; j < 10; j++) 
            b[i][j] = false;
}



void TheGame::SetNumberOfPlayers(short int n) {
    players = n;
}

TheGame::TheGame(TheGame& j) {
    players = j.players;
}

void System::DeleteTempBool(bool* b) {
    delete b;
}


void System::DeleteTempString(string* s) {
    delete s;
}


void AfterDestruction() {
    cout<<sistem.ShowMessage("special", true);
    string *aux1 = new string, *aux2 = new string;
    string aux;
    for (int i = 0; i < hit.size(); i++) {
        aux = hit[i];
        *aux1 = aux[0], *aux2 = aux[1];
        hasAttackedAgain[std::stoi(*aux1)][std::stoi(*aux2)] = true;
    }
    sistem.DeleteTempString(aux1);
    sistem.DeleteTempString(aux2);
}
 

void System::SetHumanPoints(int points) {
    humanPoints = points;
}

string System::ReturnHumanPoints() {
    return std::to_string(humanPoints);
}

string System::ShowMessage(string type) {
    if (type == "normal")
        return ("[ " + name + " ] Some maintenance functions have been run.\n");
}

string System::ShowMessage(string type, bool secret) {
    if (type == "special" && secret)
        return ("[ " + name + " ] The specified objects have been destroyed.\n");
}
