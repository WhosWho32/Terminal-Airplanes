#pragma once

#include <string>
#include <iostream>
#include <vector>

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;

#define FULL_SQUARE "\xFE"
#define HEAD ">"

struct Airplane {
    string direction, orientation, oCoord, vCoord; 
    /* direction - horizontal/vertical
    orientation - up, down, left, right (where the airplane is facing)
    oCoord - horizontal coordinate
    vCoord - vertical coordinate */
    int vCoordConv, oCoordConv;
};



class Player {
    protected:
    void VerifyVertex(Airplane a, vector <string>& v);
    public:
    static void ShowTable();
    short int airplaneNumber;
    bool turnEnded;
    string decision; //Target position, for when the player wants to attack
    Player() {}
    Player(short int n);
    struct AirplanePlane {
        string plane[10][10];
 };
    struct AirplaneAttackPlane {
        string attack[10][10];
 };
};


class Human: public Player {
    bool cheat;
    short int humanAirplanes = 0;
    public:
    string decision;
    Human() {};
    Human(const Player& k);
    int ReturnNumberOfAirplanes();
    void SetCheatMode(bool cheating) { cheat = cheating; }
    bool ReturnCheatMode() { return cheat; }
    void Attack();
    void MarkAsAttacked(Airplane a, bool (&v)[10][10]);
    void VerifyHit();
    void VerifyHitVertex(int n);
    void ModifyNumberOfAirplanesRobot(Human& o);
    friend void AirplaneConfig();
};


class SpecialMenu: protected Human {
    public:
    void Menu(SpecialMenu& me);
    friend std::ostream & operator << (std::ostream& write, SpecialMenu& m);
    friend std::istream & operator >> (std::istream& read, SpecialMenu& m); //Reading the command
    bool VerifyCommand(string& s);
    string command;
};


class Robot: public Player {
    bool active;
    short int robotAirplanes = 0;
    public:
    Robot() {};
    Robot(const Player& l);
    void ModifyNumberOfAirplanesRobot(Robot& r);
    void ShowNumberOfAirplanesLeftRobot(Robot& r);
    void VerifyHitVertex(int n);
    void SetActivity(bool active);
    int ReturnNumberOfAirplanes();
    void Decisions();
    void Attack();
    void SmartAttack(); //Smart attack
};

class TheGame {
    short int players;
    public:
    TheGame() {};
    TheGame(TheGame& j);
    void SetNumberOfPlayers(short int n);
    int ReturnNumberOfPlayers() {
        return players;
    }
    ~TheGame() {
        cout<<"\n[*] The game has ended!\n\n";
    }
};
class System {
    protected:
    string name = "SYSTEM";    
    short int humanPoints;
    public:    
    System() {}
    System(System& SI) { name = SI.name; }
    void DeleteTempString(string* s);
    void DeleteTempBool(bool* b);
    void SetSystemName(string name) { this->name = name; }
    string ShowMessage(string type);
    string ShowMessage(string type, bool secret);
    void SetHumanPoints(int points);
    string ReturnHumanPoints();
    string ShowSystemInfo() {
        return name;
    } 
    ~System() {}
};



class Optimizations: public System {
    public:
    Optimizations() {}
    ~Optimizations() {}
};



void Selector();
void ShowScreen();
void ShowButtons();
void Sound();
void AirplaneConfig();
void Game();
void Verify();
void StopVerifying(bool (&b)[10][10], bool (&c)[10][10], bool (&d)[10][10], bool (&e)[10][10]);
void SetPossiblePositions(string (&s)[10][10]);
void SetHowMnayTimesToAdd(int (&i)[10][10]);
void SetHowManyTimesTheyAttacked(bool (&b)[10][10]);
void ConvertorCoord(Airplane& a);
void Judgeman(Airplane& a);
void ShowAirplanesOnTable(Airplane a, int n, Player::AirplanePlane& P, string v[3][10], string vertices[3]);
int ConvertPosition(string s);
bool IsOverlap(string v[3][10], int n, string who);
bool AnswerFormat(string s);
vector <string> InvertConversion(string (&s)[3][10]);


extern string soundSettings, Volume, finished, letters[10], airplaneMatrix[3][10], robotAirplaneMatrix[3][10],
              humanAirplaneVertices[3], robotAirplaneVertices[3], chosenOption, menuSelector, secretCode;
//secretCode - wwssadadba
//chosenOption - To keep track of where we are
extern vector <string> hitHuman, dodgedHuman;
extern Player j;
extern Player::AirplanePlane PO, PR;
extern Player::AirplaneAttackPlane PAO, PAR;
extern Human o;
extern Robot robo;
extern Airplane A1, A2, A3, R1, R2, R3;
extern System sistem;
extern Optimizations opti;
extern short int randomness;
extern int airplaneSetup;
extern bool guardian, hasAttackedAgain[10][10];
extern bool* verifyCode;