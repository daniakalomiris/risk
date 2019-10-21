#include <iostream>
#include "Dice.h"
#include <memory>

using namespace std;

//
//int main() {
//
//    //tells true if we roll the dice again
//    bool rollAgain = true;
//
//    //creates 2 dice rolling facility objects
//    Dice dice1;
//    Dice dice2;
//
//   //choice of the user if he/she wants to roll the dice again
//    int choice;
//
//    //ask the player 1 to roll their dice
//    cout << "\n*******----- Player 1, please roll your dice -----*******" << endl;
//
////do-while loop to keep asking to roll the dice
// do {
//   dice1.askRoll();
//    dice1.rollDice();
//    dice1.keepTracks();
//
//   cout << "Do you want to roll the dice again? If yes, enter 1, if no, please press 0" << endl;
//   cin >> choice;
//
//    //if the user input 0, put rollAgain equals to false to stop rolling the dice.
//       if(choice == 0) {
//            rollAgain = false;
//       }
//
//   }
//   while(rollAgain == true);
//    
//    //ask the player 2 to roll their dice
//    cout << "\n*******----- Player 2, please roll your dice -----*******" << endl;
//
//    //put rollAgain back to true
//    rollAgain = true;
//
//    //do-while loop to keep asking to roll the dice
//    do {
//    dice2.askRoll();
//    dice2.rollDice();
//    dice2.keepTracks();
//
//   cout << "Do you want to roll the dice again? If yes, enter 1, if no, please press 0" << endl;
//   cin >> choice;
//
//    //if the user input 0, put rollAgain equals to false to stop rolling the dice.
//       if(choice == 0) {
//            rollAgain = false;
//       }
//
//   }
//   while(rollAgain == true);
//
//   //Message to display that the program ended
//   cout << "\n*******----- End of program -----*******" << endl;
//}
//
