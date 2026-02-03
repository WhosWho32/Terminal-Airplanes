//This program has been tested on Windows 11 and 10 on both VSCode and Code Blocks.
//Last edit made: February 3rd 2026
//Made by: WhosWho

#include <chrono>
#include <thread>
#include <cstdlib>
#include "header.h"

bool* verifyCode = new bool;
System sistem;
TheGame startMenu;
Optimizations opti;

void ShowSlowly(string a, int timp);

int main() {
    srand(time(NULL));
    startMenu.SetNumberOfPlayers(2);
    TheGame game(startMenu);
    system("cls");
    //Font used: Merlin1
    cout<<R"(
      __        __      _______     _______   ___            __      _____  ___    _______ 
     /""\      |" \    /"      \   |   __ "\ |"  |          /""\    (\"   \|"  \  /"     "|
    /    \     ||  |  |:        |  (. |__) :)||  |         /    \   |.\\   \    |(: ______)
   /' /\  \    |:  |  |_____/   )  |:  ____/ |:  |        /' /\  \  |: \.   \\  | \/    |  
  //  __'  \   |.  |   //      /   (|  /      \  |___    //  __'  \ |.  \    \. | // ___)_ 
 /   /  \\  \  /\  |\ |:  __   \  /|__/ \    ( \_|:  \  /   /  \\  \|    \    \ |(:      "|
(___/    \___)(__\_|_)|__|  \___)(_______)    \_______)(___/    \___)\___|\____\) \_______)
                                                                                           
    ______    ________                                                                     
   /    " \  /"       )       __                                                             
  // ____  \(:   \___/        \  \     _ _                                                                     
 /  /    ) :)\___  \           \**\ ___\/ \                                                                       
(: (____/ //  __/  \\        X*#####*+^^\_\                                                                       
 \        /  /" \   :)         o/\  \                                                                     
  \"_____/  (_______/             \__\ )";
    cout<<"\n\n";
    cout<<"[*] System logging: [ SYSTEM ]\n";
    cout<<"[*] Some things need to be verified. Please wait.\n\n";
    string *aux1 = new string, *aux2 = new string, *aux3 = new string, *aux4 = new string, *aux5 = new string, *aux6 = new string;
    *aux1 = "[*] PLAYERS ........................... 2\n";
    ShowSlowly(*aux1, 60);
    *aux2 = "[*] VOLUME ........................... ON\n";
    ShowSlowly(*aux2, 30);
    *aux3 = "[*] LANGUAGE .................... ENGLISH\n";
    ShowSlowly(*aux3, 20);
    *aux4 = "[*] TEMPERATURE ................. OPTIMAL\n";
    ShowSlowly(*aux4, 40);
    *aux5 = "[*] FREQUENCY ..................... " + std::to_string(15+rand()%85) + "kHZ\n"; // 15-99kHz
    ShowSlowly(*aux5, 30);
    cout<<"\n"<<sistem.ShowMessage("normal")<<"\n\n";
    cout<<"[*] Verification complete. Nothing out of the ordinary has been identified. Redirecting to the main menu screen";
    *aux6 = "...";
    ShowSlowly(*aux6, 1000);
    delete aux1, aux2, aux3, aux4, aux5, aux6;
    cout<<"\n\n";
    system("pause");
    system("cls");
    *verifyCode = false;
    //Show main menu screen
    ShowScreen();
    ShowButtons();
    cout<<"\n\nIf you wish to start the game, press Enter. Otherwise, if you wish to modify some settings, type 's' to move to the Options menu, and press Enter to access it.\n"<<"                                                            ";
    Selector();
    return 0;
}

void ShowSlowly(string a, int time) {
    for (char s : a) {
        cout<<s<<std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }
}