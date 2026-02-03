#include "header.h"
#include <cstdlib>

Airplane R1, R2, R3;
short int robotChoice, airplaneConfig = 1, airplanePositionP2, options = 0, random;

int addOnlyOnce[10][10], movementOptions[10][10] = {        2, 3, 3, 3, 3, 3, 3, 3, 3, 2,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            3, 4, 4, 4, 4, 4, 4, 4, 4, 3,
                                                            2, 3, 3, 3, 3, 3, 3, 3, 3, 2 };

string robotAirplaneMatrix[3][10], airplanePositionP1, finalPosition, robotAirplaneVertices[3], possiblePositions[10][10];
vector <string> hitHuman, dodgedHuman, attackContinuations, saveIndex, saveOptions, samePossiblePositions;
bool stopVerifyingAbove[10][10], stopVerifyingBelow[10][10], stopVerifyingLeft[10][10], stopVerifyingRight[10][10];
bool *verify = new bool;

void ModifyPossiblePositions(Airplane& a, string (&p) [10][10], string& C, string& D);
void DeleteWhatIsRepeatingInsideVector (vector <string>& l);


void Robot::Decisions() {
    Optimizations optimiz;
    System sistemRobot(sistem);
    *verify = true;
    if (*verify) {
        StopVerifying(stopVerifyingAbove, stopVerifyingBelow, stopVerifyingRight, stopVerifyingLeft);
        SetPossiblePositions(possiblePositions);
        SetHowMnayTimesToAdd(addOnlyOnce);
        SetHowManyTimesTheyAttacked(hasAttackedAgain);
        *verify = false;
    }
    if (o.ReturnNumberOfAirplanes() != 0 && hitHuman.size() != 30) {
        if (active) {
            string* superaux1 = new string, *superaux2 = new string, *superaux3 = new string;
            *superaux1 = humanAirplaneVertices[0], *superaux2 = humanAirplaneVertices[1], *superaux3 = humanAirplaneVertices[2];
            //The bot chooses the direction
            if (airplaneConfig == 1) {
            robotChoice = rand()%2; // 0 sau 1
            R1.direction = (robotChoice == 0) ? "horizontal" : "vertical";
            //The bot chooses the orientation
            if (robotChoice == 0) {
                robotChoice = 1+rand()%2; // 1 or 2
                R1.orientation = (robotChoice == 1) ? "right" : "left";
            } else {
                robotChoice = 2+rand()%2; // 2 or 3
                R1.orientation = (robotChoice == 2) ? "up" : "down";
            }
            //The bot chooses the position RANDOMLY
            if (R1.direction == "horizontal") {
                airplanePositionP1 = (R1.orientation == "right") ? letters[rand()%7] : letters[3+rand()%7];
                /* letters[rand()%7] -> A, B, ..., G are all the available positions to choose from
                   letters[3+rand()%7] -> // D, E, F, G, H, I, J */
                airplanePositionP2 = 3+rand()%6; // 3-8
                
            } else if (R1.direction == "vertical") {
                airplanePositionP1 = letters[2+rand()%6]; // C, D, E, F, G, H 
                airplanePositionP2 = (R1.orientation == "up") ? 4+rand()%7 : 1+rand()%7;
                /* 4+rand()%7 -> 4-10
                   1+rand()%7 -> 1-7 */
            }
            finalPosition = airplanePositionP1 + std::to_string(airplanePositionP2);
            R1.vCoord = airplanePositionP1;
            ConvertorCoord(R1);
            R1.oCoordConv = airplanePositionP2;
            ShowAirplanesOnTable(R1, 0, PR, robotAirplaneMatrix, robotAirplaneVertices); //To already set the first airplane on the table
            airplaneConfig++;
        }

        //Airplane 2
        if (airplaneConfig == 2) {
            robotChoice = rand()%2; // 0 or 1
            R2.direction = (robotChoice == 0) ? "horizontal" : "vertical";
            //The bot chooses the orientation
            if (robotChoice == 0) {
                robotChoice = 1+rand()%2; // 1 or 2
                R2.orientation = (robotChoice == 1) ? "right" : "left";
            } else {
                robotChoice = 2+rand()%2; // 2 or 3
                R2.orientation = (robotChoice == 2) ? "up" : "down";
            }
            //The bot chooses the position RANDOMLY
            if (R2.direction == "horizontal") {
                int lowerLimit, upperLimit;
                lowerLimit = (R2.orientation == "right") ? 0 : 3;
                upperLimit = (R2.orientation == "right") ? 7 : 10;
                for (int i = lowerLimit; i < upperLimit; i++) {
                        for (int j = 2; j < 8; j++) {
                            airplanePositionP1 = letters[i];
                            airplanePositionP2 = j+1;
                            R2.vCoord = airplanePositionP1;
                            ConvertorCoord(R2);
                            R2.oCoordConv = airplanePositionP2;
                            ShowAirplanesOnTable(R2, 1, PR, robotAirplaneMatrix, robotAirplaneVertices); //To set the airplane in 
                            if (!IsOverlap(robotAirplaneMatrix, 2, "robot")) {
                                saveOptions.push_back(std::to_string(R2.oCoordConv) + std::to_string(R2.vCoordConv));
                                options = saveOptions.size();
                            } else 
                                continue;
                            }
                }
        } else if (R2.direction == "vertical") {
                int lowerLimit, upperLimit;
                lowerLimit = (R2.orientation == "up") ? 3 : 0;
                upperLimit = (R2.orientation == "up") ? 10 : 7;
                for (int i = 2; i < 8; i++) {
                    for (int j = lowerLimit; j < upperLimit; j++) {
                        airplanePositionP1 = letters[i];
                        airplanePositionP2 = j+1;
                        R2.vCoord = airplanePositionP1;
                        ConvertorCoord(R2);
                        R2.oCoordConv = airplanePositionP2;
                        ShowAirplanesOnTable(R2, 1, PR, robotAirplaneMatrix, robotAirplaneVertices);
                        if (!IsOverlap(robotAirplaneMatrix, 2, "robot")) {
                            saveOptions.push_back(std::to_string(R2.oCoordConv) + std::to_string(R2.vCoordConv));
                            options = saveOptions.size();
                        } else 
                            continue;
                        }
                    }
            }
            //After the bot establishes all available positions, it picks one at random
            string *aux = new string;
            *aux = saveOptions[rand()%options]; //Suppose we have 10 options, then the random will be 0-9, which is perfect
            int tmp = std::stoi(*aux);
            if (tmp < 110) {
                R2.oCoordConv = (tmp>99) ? 10 : tmp/10;
                R2.vCoordConv = tmp%10; 
            } else {
                R2.oCoordConv = tmp/10/10; //Always the first number. In case it messes things up, make it tmp/10
                R2.vCoordConv = 10; 
            }
            //Save bot pick
            ShowAirplanesOnTable(R2, 1, PR, robotAirplaneMatrix, robotAirplaneVertices); //Setting the plane again
            finalPosition = std::to_string(R2.oCoordConv) + std::to_string(R2.vCoordConv);
            saveOptions.clear(); //Erase the entire vector of saved options
            options = saveOptions.size();
            airplaneConfig++;
            optimiz.DeleteTempString(aux);
        }

        if (airplaneConfig == 3) {
            robotChoice = rand()%2; 
            R3.direction = (robotChoice == 0) ? "horizontal" : "vertical";
            if (robotChoice == 0) {
                //The bot picks the orientation
                robotChoice = 1+rand()%2; 
                R3.orientation = (robotChoice == 1) ? "right" : "left";
            } else {
                //The bot picks the orientation
                robotChoice = 2+rand()%2;
                R3.orientation = (robotChoice == 2) ? "up" : "down";
            }
            //The bot chooses the position RANDOMLY
            if (R3.direction == "horizontal") {
                int lowerLimit, upperLimit;
                lowerLimit = (R3.orientation == "right") ? 0 : 3;
                upperLimit = (R3.orientation == "right") ? 7 : 10;
                for (int i = lowerLimit; i < upperLimit; i++) {
                    for (int j = 2; j < 8; j++) {
                        airplanePositionP1 = letters[i];
                        airplanePositionP2 = j+1;
                        R3.vCoord = airplanePositionP1;
                        ConvertorCoord(R3);
                        R3.oCoordConv = airplanePositionP2;
                        ShowAirplanesOnTable(R3, 2, PR, robotAirplaneMatrix, robotAirplaneVertices);
                        if (!IsOverlap(robotAirplaneMatrix, 3, "robot")) {
                            saveOptions.push_back(std::to_string(R3.oCoordConv) + std::to_string(R3.vCoordConv));
                            options = saveOptions.size();
                        } else 
                            continue;
                        }
                }
        } else if (R3.direction == "vertical") {
                int lowerLimit, upperLimit;
                lowerLimit = (R3.orientation == "up") ? 3 : 0;
                upperLimit = (R3.orientation == "up") ? 10 : 7;
                for (int i = 2; i < 8; i++) {
                    for (int j = lowerLimit; j < upperLimit; j++) {
                        airplanePositionP1 = letters[i];
                        airplanePositionP2 = j+1;
                        R3.vCoord = airplanePositionP1;
                        ConvertorCoord(R3);
                        R3.oCoordConv = airplanePositionP2;
                        ShowAirplanesOnTable(R3, 2, PR, robotAirplaneMatrix, robotAirplaneVertices);
                        if (!IsOverlap(robotAirplaneMatrix, 3, "robot")) {
                            saveOptions.push_back(std::to_string(R3.oCoordConv) + std::to_string(R3.vCoordConv));
                            options = saveOptions.size();
                        } else 
                            continue;
                        }
                    
                }
                
            }
            string* aux1 = new string;
            *aux1 = saveOptions[rand()%options];
            int tmp1 = std::stoi(*aux1);
            if (tmp1 < 110) {
                R3.oCoordConv = (tmp1 > 99) ? 10 : tmp1/10;
                R3.vCoordConv = tmp1%10; 
            } else {
                R3.oCoordConv = tmp1/10/10;
                R3.vCoordConv = 10; 
            }
            //Save bot pick
            ShowAirplanesOnTable(R3, 2, PR, robotAirplaneMatrix, robotAirplaneVertices);
            finalPosition = std::to_string(R3.oCoordConv) + std::to_string(R3.vCoordConv);
            cout<<sistemRobot.ShowMessage("normal");
            optimiz.DeleteTempString(aux1);
        }
        humanAirplaneVertices[0] = *superaux1, humanAirplaneVertices[1] = *superaux2, humanAirplaneVertices[2] = *superaux3;
        optimiz.DeleteTempString(superaux1);
        optimiz.DeleteTempString(superaux2);
        optimiz.DeleteTempString(superaux3);
        optimiz.DeleteTempBool(verify);
        guardian = true;
    }
    } else {
         cout<<"\n";
         Player::ShowTable();
         cout<<"[X] You have been defeated! All your airplanes have been destroyed."<<endl;
         //cout<<"[*] Game has finished!\n\n";
         //system("pause");
         exit(-1);
    }
    
}


void Robot::Attack() {
    if (o.ReturnNumberOfAirplanes() != 0 && hitHuman.size() != 30) {
        Optimizations opt;
        bool *putVertexInVector = new bool, *continueAttacking = new bool;
        *putVertexInVector = false, *continueAttacking = false;
        random = (hitHuman.size() == 0) ? 0 : rand()%2;
        if (random == 0) {
        string randomAttackPosition = std::to_string(rand()%10) + std::to_string(rand()%10); //Between 00 (A1) and 99 (J10)
        string aux1, aux2;
        aux1 = randomAttackPosition[0], aux2 = randomAttackPosition[1];
        while (possiblePositions[std::stoi(aux1)][std::stoi(aux2)] == "O" || possiblePositions[std::stoi(aux1)][std::stoi(aux2)] == "X") 
            robo.Attack();
        short int counter = 0, anotherCounter = 0;
        //Verify if the bot hit something or not
        //If it did, put an "X" in that position so it doesn't get picked again, or an "O" if it missed
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 10; j++) {
                if (randomAttackPosition == airplaneMatrix[i][j]) {
                    if (Volume == "On")
                        cout<<"\a[!] The bot hit you! Its' turn continues.\n";
                    else if (Volume == "Off")
                        cout<<"[!] The bot hit you! Its' turn continues.\n";
                        for (int k = 0; k < 3; k++) 
                            if (randomAttackPosition == humanAirplaneVertices[k]) {
                                if (Volume == "On")
                                    cout<<"\a[!] One of your airplane's vertex has been hit! As a result, the entire airplane is destroyed.\n";
                                else if (Volume == "Off")
                                    cout<<"[!] One of your airplane's vertex has been hit! As a result, the entire airplane is destroyed.\n";
                                *putVertexInVector = true;
                                switch(k) {
                                    case 0:
                                        robo.VerifyHitVertex(1);
                                        ModifyPossiblePositions(A1, possiblePositions, aux1, aux2);
                                        break;
                                    case 1:
                                        robo.VerifyHitVertex(2);
                                        ModifyPossiblePositions(A2, possiblePositions, aux1, aux2);
                                        break;
                                    case 2:
                                        robo.VerifyHitVertex(3);
                                        ModifyPossiblePositions(A3, possiblePositions, aux1, aux2);
                                        break;
                                }
                                o.ModifyNumberOfAirplanesRobot(o);
                                *continueAttacking = true;
                            }
                        if (!*putVertexInVector) 
                            hitHuman.push_back(randomAttackPosition);
                        DeleteWhatIsRepeatingInsideVector(hitHuman);
                        possiblePositions[std::stoi(aux1)][std::stoi(aux2)] = "X";
                        counter = 1;
                        anotherCounter = 1;
                        robo.Attack();
                } else 
                        if (j == 9) 
                            if (counter == 2) 
                                if (anotherCounter == 0) {
                                    cout<<"[V] The bot missed you!\n\n";
                                    cout<<"------------------------------------------\n";
                                    possiblePositions[std::stoi(aux1)][std::stoi(aux2)] = "O";
                                    cout<<endl<<endl;
                                    dodgedHuman.push_back(aux1 + aux2);
                                    anotherCounter = 1;
                                }    
                }
                counter++;
            }
            } else 
                robo.SmartAttack();
            if (!*continueAttacking) {
                if (o.ReturnNumberOfAirplanes() != 0) {
                    cout<<"\n";
                    Player::ShowTable();
                    o.Attack();
                }  else {
                    cout<<"\n";
                    Player::ShowTable();
                    cout<<"[X] You have been defeated! All your airplanes have been destroyed."<<endl;
                    //cout<<"[*] Game has finished!\n\n";
                    //system("pause");
                    exit(-1);
                }
            } else 
                robo.Attack();
            opt.DeleteTempBool(putVertexInVector);
            opt.DeleteTempBool(continueAttacking);
        } else {
            cout<<"\n";
            Player::ShowTable();
            cout<<"[X] You have been defeated! All your airplanes have been destroyed."<<endl;
            //cout<<"[*] Game has finished!\n\n";
            //system("pause");
            exit(-1);
        }
        
}


void Robot::SmartAttack() {
    if (o.ReturnNumberOfAirplanes() != 0 && hitHuman.size() != 30) {
        Optimizations opt;
        bool* continueAttacking = new bool, *chooseSomethingElse = new bool, *putVertexInVector = new bool;
        *continueAttacking = false, *chooseSomethingElse = false, *putVertexInVector = false;
         string newAttackPosition, aux1, aux2, aux3, aux4, lastAttackPosition;
        lastAttackPosition = hitHuman[rand()%hitHuman.size()]; //The bot chooses a random position where it already attacked previously
        aux1 = lastAttackPosition[0], aux2 = lastAttackPosition[1];
        //After it chooses the position, it checks its' table to see if it has any movement options near that position
        for (int i = 0; i < 10; i++) {
            if (*chooseSomethingElse) 
                break;
            for (int j = 0; j < 10; j++) {
                if (possiblePositions[i][j] == "X" && std::stoi(aux1) == i && std::stoi(aux2) == j) {
                    if (movementOptions[i][j] == 0) {
                        *chooseSomethingElse = true;
                        break;
                    }
                        //First the corners
                        if (i == 0 && j == 0) {
                                //A1, verify right and down
                                //Down
                                if (possiblePositions[1][0] != "X" && possiblePositions[1][0] != "O") {
                                    if (addOnlyOnce[i][j] < 2) {
                                        attackContinuations.push_back(std::to_string(10)); 
                                        addOnlyOnce[i][j]++;
                                    }
                                    
                                } else {  
                                    if (!stopVerifyingBelow[i][j]) {
                                    //If that space is occupied, subtract options
                                        movementOptions[i][j]--;
                                        stopVerifyingBelow[i][j] = true;
                                }
                                
                                }
                                
                            
                                    //Right
                                    if (possiblePositions[0][1] != "X" && possiblePositions[0][1] != "O") {
                                        if(addOnlyOnce[i][j] < 2) {
                                        attackContinuations.push_back(std::to_string(0) + std::to_string(1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else {
                                        if (!stopVerifyingRight[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingRight[i][j] = true;

                                    }
                                    
                                }
                                if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        }
                        if (i == 9 && j== 0) {
                                //A10, verify up and right
                                //Up
                                if (possiblePositions[8][0] != "X" && possiblePositions[8][0] != "O") {
                                        if(addOnlyOnce[i][j] < 2) {
                                            attackContinuations.push_back(std::to_string(80)); //Save the position separately
                                            addOnlyOnce[i][j]++;
                                        }
                                } else { 
                                    if (!stopVerifyingAbove[i][j]) {
                                    movementOptions[i][j]--;
                                    stopVerifyingAbove[i][j] = true;
                                    }
                                }
                                
                                    //Right
                                    if (possiblePositions[9][1] != "X" && possiblePositions[9][1] != "O") {
                                        if (addOnlyOnce[i][j] < 2) {
                                            attackContinuations.push_back(std::to_string(91)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else {
                                        if (!stopVerifyingRight[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingRight[i][j] = true;
                                        }
                                    }
                                if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        }
                        if (i == 0 && j == 9) {
                                //J1, verify left and down
                                //Down
                                if (possiblePositions[1][9] != "X" && possiblePositions[1][9] != "O") {
                                    if (addOnlyOnce[i][j] < 2) {
                                        attackContinuations.push_back(std::to_string(19)); 
                                        addOnlyOnce[i][j]++;
                                    }
                                } else { 
                                    if (!stopVerifyingBelow[i][j]) {
                                    movementOptions[i][j]--;
                                    stopVerifyingBelow[i][j] = true;
                                    }
                                }
                                    //Left
                                    if (possiblePositions[0][8] != "X" && possiblePositions[0][8] != "O") {
                                        if (addOnlyOnce[i][j] < 2) {
                                            attackContinuations.push_back(std::to_string(0) + std::to_string(8)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else { 
                                        if (!stopVerifyingLeft[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingLeft[i][j] = true;
                                        }
                                     }
                                if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        }
                        if (i == 9 && j == 9) {
                            //J10, left and up
                            //Up
                            if (possiblePositions[8][9] != "X" && possiblePositions[8][9] != "O") {
                                if (addOnlyOnce[i][j] < 2) {
                                    attackContinuations.push_back(std::to_string(89));
                                    addOnlyOnce[i][j]++;
                                }
                            } else {
                                    if (!stopVerifyingAbove[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingAbove[i][j] = true;
                                    }   
                                }
                                //Left
                                    if (possiblePositions[9][8] != "X" && possiblePositions[9][8] != "O") {
                                        if (addOnlyOnce[i][j] < 2) {
                                            attackContinuations.push_back(std::to_string(98)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else {
                                        if (!stopVerifyingLeft[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingLeft[i][j] = true;
                                    }
                                    
                                }
                                if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        }

                        //------------------------------------------------------------------------------------

                        //The "outline" of the table is a bit more special, so it needs some extra conditions
                        //First column
                        if (j == 0) {
                            if (i  > 0 && i < 9) {
                                //If we're between 1-8, we got 3 options, otherwise 2 if we are in a corner
                                //Verify if around an X we have another X or O
                                //Up
                                if (possiblePositions[i-1][0] != "X" && possiblePositions[i-1][0] != "O") {
                                    if (addOnlyOnce[i][j] < 3) {
                                        attackContinuations.push_back(std::to_string(i-1) + std::to_string(0));
                                        addOnlyOnce[i][j]++;
                                    }
                                } else { 
                                    if (!stopVerifyingAbove[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingAbove[i][j] = true;
                                    }
                                }
                                //Down
                                if (possiblePositions[i+1][0] != "X" && possiblePositions[i+1][0] != "O") {
                                    if (addOnlyOnce[i][j] < 3) {
                                        attackContinuations.push_back(std::to_string(i+1) + std::to_string(0)); 
                                        addOnlyOnce[i][j]++;
                                    }
                                } else { 
                                    if (!stopVerifyingBelow[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingBelow[i][j] = true;
                                }
                                }
                                    //Right
                                    if (possiblePositions[i][1] != "X" && possiblePositions[i][1] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(i) + std::to_string(1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else { 
                                        if (!stopVerifyingRight[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingRight[i][j] = true;
                                    }
                                }
                            }
                            if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        } else if (j == 9) {
                            //Right column
                            if (i > 0 && i < 9) {
                                //Between 1-8, 3 options; corners - 2 options
                                //Up
                                    if (possiblePositions[i-1][9] != "X" && possiblePositions[i-1][9] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(i-1) + std::to_string(9));
                                            addOnlyOnce[i][j]++;
                                        }
                                } else {
                                    if (!stopVerifyingAbove[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingAbove[i][j] = true;
                                    }
                                }
                                //Down
                                if (possiblePositions[i+1][9] != "X" && possiblePositions[i+1][9] != "O") {
                                    if (addOnlyOnce[i][j] < 3) {
                                        attackContinuations.push_back(std::to_string(i+1) + std::to_string(9)); 
                                        addOnlyOnce[i][j]++;
                                    }
                                } else {
                                    if (!stopVerifyingBelow[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingBelow[i][j] = true;
                                    }
                                }
                                    //Left
                                    if (possiblePositions[i][8] != "X" && possiblePositions[i][8] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(i) + std::to_string(8)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else {  
                                        if (!stopVerifyingLeft[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingLeft[i][j] = true;
                                        }
                                }
                            } 
                            if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        }

                        //First row
                        if (i == 0) {
                            if (j != 9) {
                                //Verify left, down, right
                                //Down
                                if (possiblePositions[1][j] != "X" && possiblePositions[1][j] != "O") {
                                    if (addOnlyOnce[i][j] < 3) {
                                        attackContinuations.push_back(std::to_string(1) + std::to_string(j)); 
                                        addOnlyOnce[i][j]++;
                                    }
                                } else {  
                                    if (!stopVerifyingBelow[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingBelow[i][j] = true;
                                    }
                                }
                                    //Left
                                    if (possiblePositions[0][j-1] != "X" && possiblePositions[0][j-1] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(0) + std::to_string(j-1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else {
                                        if (!stopVerifyingLeft[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingLeft[i][j] = true;
                                    }
                                }
                                    //Right
                                    if (possiblePositions[0][j+1] != "X" && possiblePositions[0][j+1] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(0) + std::to_string(j+1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else { 
                                        if (!stopVerifyingRight[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingRight[i][j] = true;
                                        }
                                }
                            }
                            if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        } else if (i == 9) {
                            if (j != 0) {
                                    //Last row
                                    //Verify up, left, right
                                    //Up
                                    if (possiblePositions[8][j] != "X" && possiblePositions[8][j] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(8) + std::to_string(j)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                } else {
                                    if (!stopVerifyingAbove[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingAbove[i][j] = true;
                                    }
                                }
                                    //Right
                                    if (possiblePositions[9][j+1] != "X" && possiblePositions[9][j+1] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(9) + std::to_string(j+1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else { 
                                        if (!stopVerifyingRight[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingRight[i][j] = true;
                                        }
                                }
                                    //Left
                                    if (possiblePositions[9][j-1] != "X" && possiblePositions[9][j-1] != "O") {
                                        if (addOnlyOnce[i][j] < 3) {
                                            attackContinuations.push_back(std::to_string(9) + std::to_string(j-1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else { 
                                        if (!stopVerifyingLeft[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingLeft[i][j] = true;
                                        }
                                }
                            }
                            if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                                }
                        }

                        //Now we verify in general
                        if (i > 0 && i < 9 && j > 0 && j < 9) {
                                //Verify all 4 options: left, right, up, down
                                //Up
                                if (possiblePositions[i-1][j] != "X" && possiblePositions[i-1][j] != "O") {
                                    if (addOnlyOnce[i][j] < 4) {
                                        attackContinuations.push_back(std::to_string(i-1) + std::to_string(j)); 
                                        addOnlyOnce[i][j]++;
                                    }
                                } else { 
                                    if (!stopVerifyingAbove[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingAbove[i][j] = true;
                                    }
                                }
                                    //Right
                                    if (possiblePositions[i][j+1] != "X" && possiblePositions[i][j+1] != "O") {
                                        if (addOnlyOnce[i][j] < 4) {
                                            attackContinuations.push_back(std::to_string(i) + std::to_string(j+1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                    } else { 
                                        if (!stopVerifyingRight[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingRight[i][j] = true;
                                        }
                                }
                                    //Left
                                    if (possiblePositions[i][j-1] != "X" && possiblePositions[i][j-1] != "O") {
                                        if (addOnlyOnce[i][j] < 4) {
                                            attackContinuations.push_back(std::to_string(i) + std::to_string(j-1)); 
                                            addOnlyOnce[i][j]++;
                                        }
                                        
                                    } else {
                                        if (!stopVerifyingLeft[i][j]) {
                                            movementOptions[i][j]--;
                                            stopVerifyingLeft[i][j] = true;
                                        }
                                    
                                }
                                //Down
                                if (possiblePositions[i+1][j] != "X" && possiblePositions[i+1][j] != "O") {
                                    if (addOnlyOnce[i][j] < 4) {
                                        attackContinuations.push_back(std::to_string(i+1) + std::to_string(j)); 
                                        addOnlyOnce[i][j]++;
                                    }
                                } else {
                                    if (!stopVerifyingBelow[i][j]) {
                                        movementOptions[i][j]--;
                                        stopVerifyingBelow[i][j] = true;
                                   }   
                                }
                        }
                        if (movementOptions[i][j] == 0) {
                                    *chooseSomethingElse = true;
                                    break;
                        } 
                }
            }
        }
    if (!*chooseSomethingElse) {
        //Remove if they were hit due to a vertex attack
        for (int i = 0; i < attackContinuations.size(); i++) 
            for (int j = 0; j < hitHuman.size(); j++) 
                if (attackContinuations[i] == hitHuman[j]) 
                    attackContinuations.erase(attackContinuations.begin() + i);
        //Also remove anything repeating
        for (int i = 0; i < attackContinuations.size(); i++) 
            for (int j = i+1; j < attackContinuations.size(); j++) 
                if(attackContinuations[i] == attackContinuations[j]) 
                    attackContinuations.erase(attackContinuations.begin() + j);
    //After it adds to a separate vector all possible options, it chooses one of them, and removes it afterwards
    for (int i = 0; i < attackContinuations.size(); i++) {
        if (attackContinuations[i] == (aux1 + std::to_string(std::stoi(aux2) - 1))) {
            //Verify left
            if (possiblePositions[std::stoi(aux1)][std::stoi(aux2) - 1] != "X" && possiblePositions[std::stoi(aux1)][std::stoi(aux2) - 1] != "O")
                saveIndex.push_back(std::to_string(i));
        } else if (attackContinuations[i] == (aux1 + std::to_string(std::stoi(aux2) + 1))) {
            //Verify right
            if (possiblePositions[std::stoi(aux1)][std::stoi(aux2) + 1] != "X" && possiblePositions[std::stoi(aux1)][std::stoi(aux2) + 1] != "O")
                saveIndex.push_back(std::to_string(i));
        } else if (attackContinuations[i] == (std::to_string(std::stoi(aux1) -1) + aux2)) {
            //Verify up
            if (possiblePositions[std::stoi(aux1) - 1][std::stoi(aux2)] != "X" && possiblePositions[std::stoi(aux1) - 1][std::stoi(aux2)] != "O")
                saveIndex.push_back(std::to_string(i));
        } else if (attackContinuations[i] == (std::to_string(std::stoi(aux1) +1) + aux2)) {
            //Verify down
            if (possiblePositions[std::stoi(aux1) + 1][std::stoi(aux2)] != "X" && possiblePositions[std::stoi(aux1) + 1][std::stoi(aux2)] != "O")
                saveIndex.push_back(std::to_string(i));
        }
    }
        newAttackPosition = attackContinuations[std::stoi(saveIndex[rand()%saveIndex.size()])];
        aux3 = newAttackPosition[0], aux4 = newAttackPosition[1];
        //Remove it so it doesn't get picked again
        for (int i = 0; i < attackContinuations.size(); i++) 
            if (newAttackPosition == attackContinuations[i]) 
                attackContinuations.erase(attackContinuations.begin() + i);
        saveIndex.clear();
        //Attack
        short int counter = 0, anotherCounter = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 10; j++) {
                if (newAttackPosition == airplaneMatrix[i][j]) {
                    if (Volume == "On")
                        cout<<"\a[!] The bot hit you! Its' turn continues.\n";
                    else if (Volume == "Off")
                        cout<<"[!] The bot hit you! Its' turn continues.\n";
                    for (int k = 0; k < 3; k++) {
                        if (newAttackPosition == humanAirplaneVertices[k]) {
                            if (Volume == "On")
                                cout<<"\a[!] One of your airplane's vertex has been hit! As a result, the entire airplane is destroyed.\n";
                            else if (Volume == "Off")
                                cout<<"[!] One of your airplane's vertex has been hit! As a result, the entire airplane is destroyed.\n";
                            *putVertexInVector = true;
                            switch(k) {
                                case 0:
                                    robo.VerifyHitVertex(1);
                                    ModifyPossiblePositions(A1, possiblePositions, aux3, aux4);
                                    break;
                                case 1:
                                    robo.VerifyHitVertex(2);
                                    ModifyPossiblePositions(A2, possiblePositions, aux3, aux4);
                                    break;
                                case 2:
                                    robo.VerifyHitVertex(3);
                                    ModifyPossiblePositions(A3, possiblePositions, aux3, aux4);
                                    break;
                            }
                            o.ModifyNumberOfAirplanesRobot(o);
                        }
                    } 
                    if (!*putVertexInVector) 
                        hitHuman.push_back(newAttackPosition);
                    DeleteWhatIsRepeatingInsideVector(hitHuman);
                    possiblePositions[std::stoi(aux3)][std::stoi(aux4)] = "X";
                    counter = 1;
                    anotherCounter = 1;
                    robo.Attack();
                } else 
                    if (j == 9) 
                        if (counter == 2) 
                            if (anotherCounter == 0) {
                                cout<<"[V] The bot missed you!\n\n";
                                cout<<"------------------------------------------\n";
                                possiblePositions[std::stoi(aux3)][std::stoi(aux4)] = "O";
                                cout<<endl<<endl;
                                dodgedHuman.push_back(aux3 + aux4);
                                anotherCounter = 1;
                            }
            }
            counter++;
        }
        } else {
            if (o.ReturnNumberOfAirplanes() != 0 || hitHuman.size() != 30) {
                    if (attackContinuations.size() != 0)
                        robo.SmartAttack();
                    else 
                        robo.Attack();
            }
            else {
                cout<<"\n";
                Player::ShowTable();
                cout<<"[X] You have been defeated! All your airplanes have been destroyed."<<endl;
                //cout<<"[*] Game has finished!\n\n";
                //system("pause");
                exit(-1);
            }
        }
        opt.DeleteTempBool(chooseSomethingElse);
        opt.DeleteTempBool(putVertexInVector);
        opt.DeleteTempBool(continueAttacking);
    } else {
        cout<<"\n";
        Player::ShowTable();
        cout<<"[X] You have been defeated! All your airplanes have been destroyed."<<endl;
        //cout<<"[*] Game has finished!\n\n";
        //system("pause");
        exit(-1);
    }
}   


void ModifyPossiblePositions(Airplane& a, string (&p) [10][10], string& C, string& D) {
    if (a.direction == "horizontal") {
        if (a.orientation == "right") {
            //Vertex is already saved
            p[std::stoi(C)-2][std::stoi(D)-1] = "X";
            p[std::stoi(C)-1][std::stoi(D)-1] = "X";
            p[std::stoi(C)][std::stoi(D)-1] = "X";
            p[std::stoi(C)+1][std::stoi(D)-1] = "X";
            p[std::stoi(C)+2][std::stoi(D)-1] = "X";

            p[std::stoi(C)][std::stoi(D)-2] = "X";

            p[std::stoi(C)-1][std::stoi(D)-3] = "X";
            p[std::stoi(C)][std::stoi(D)-3] = "X";
            p[std::stoi(C)+1][std::stoi(D)-3] = "X";
        } else if (a.orientation == "left") {
            p[std::stoi(C)-2][std::stoi(D)+1] = "X";
            p[std::stoi(C)-1][std::stoi(D)+1] = "X";
            p[std::stoi(C)][std::stoi(D)+1] = "X";
            p[std::stoi(C)+1][std::stoi(D)+1] = "X";
            p[std::stoi(C)+2][std::stoi(D)+1] = "X";

            p[std::stoi(C)][std::stoi(D)+2] = "X";

            p[std::stoi(C)-1][std::stoi(D)+3] = "X";
            p[std::stoi(C)][std::stoi(D)+3] = "X";
            p[std::stoi(C)+1][std::stoi(D)+3] = "X";
        }
    } else if (a.direction == "vertical") {
        if (a.orientation == "up") {
            p[std::stoi(C)+1][std::stoi(D)-2] = "X";
            p[std::stoi(C)+1][std::stoi(D)-1] = "X";
            p[std::stoi(C)+1][std::stoi(D)] = "X";
            p[std::stoi(C)+1][std::stoi(D)+1] = "X";
            p[std::stoi(C)+1][std::stoi(D)+2] = "X";

            p[std::stoi(C)+2][std::stoi(D)] = "X";

            p[std::stoi(C)+3][std::stoi(D)-1] = "X";
            p[std::stoi(C)+3][std::stoi(D)] = "X";
            p[std::stoi(C)+3][std::stoi(D)+1] = "X";
        } else if (a.orientation == "down") {
            p[std::stoi(C)-1][std::stoi(D)-2] = "X";
            p[std::stoi(C)-1][std::stoi(D)-1] = "X";
            p[std::stoi(C)-1][std::stoi(D)] = "X";
            p[std::stoi(C)-1][std::stoi(D)+1] = "X";
            p[std::stoi(C)-1][std::stoi(D)+2] = "X";

            p[std::stoi(C)-2][std::stoi(D)] = "X";

            p[std::stoi(C)-3][std::stoi(D)-1] = "X";
            p[std::stoi(C)-3][std::stoi(D)] = "X";
            p[std::stoi(C)-3][std::stoi(D)+1] = "X";
        }
    }
}


void DeleteWhatIsRepeatingInsideVector (vector <string>& l) {
    if (l.size() > 1) {
        for (int i = 0; i < l.size(); i++) {
        for (int j = i+1; j < l.size(); j++) {
            if (l[i] == l[j]) {
                l.erase(l.begin() + j);
            }
        }
    }
    }
    
}

void SetPossiblePositions(string (&s)[10][10]) {
    for (int i = 0; i < 10; i++) 
        for (int j = 0; j < 10; j++) 
            possiblePositions[i][j] = std::to_string(i) + std::to_string(j);
}

void SetHowMnayTimesToAdd(int (&i)[10][10]) {
    for (int k = 0; k < 10; k++) 
        for (int j = 0; j < 10; j++) 
            addOnlyOnce[k][j] = 0;
}