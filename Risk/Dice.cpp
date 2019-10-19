#include "Dice.h"
#include "time.h"
#include<iostream>
using namespace std;

 Dice:: Dice() {

     //initializes the array that tracks the rolled values with zeros
   for(int i = 0; i <6; i++) {
        valuesTracker[i] = 0;
    }

    //intializes the number of time the dice have been rolled
    timesRolled.reset(new int(0));
}

// Player selects how many dice (1 to 3) to roll
void Dice::askRoll() {
    int diceToRoll;
    cout << "\nPlease enter the number of dice you would like to roll (must be 1 to 3): " << endl;
    cin >> diceToRoll;

    // Player must keep choosing the number of dice to roll if it is not 1, 2 or 3
    while (diceToRoll < 1 || diceToRoll > 3) {
        cout << "You may only roll 1 to 3 dice. Please try again." << endl;
        cin >> diceToRoll;
    }

    // Point to the number of dice player decides to roll
    numOfDice.reset(new int(diceToRoll));
}

// Generates random dice values (1 to 6) for each dice rolled
void Dice::rollDice() {

    // Initialize container
    int diceContainer[3];

    // Resets the random
   // srand(time(NULL));

    // Generates numbers between 1 and 6 and stores them in an array
    for(int i = 0; i < *numOfDice; i++) {
        int temp = rand()% 6+1;
        diceContainer[i] = temp;

        //Keep tracks of the number rolled
        valuesTracker[temp-1]++;
        
        //increments the number of dice rolled
        (*timesRolled)++;
    }

    //Sorts the array diceContainer
    for(int i = 0; i < *numOfDice; i++) {
        for(int j = i+1; j < *numOfDice; j++) {
            if(diceContainer[i] > diceContainer[j]) {
                int temp = diceContainer[i];
                diceContainer[i] = diceContainer[j];
                diceContainer[j] = temp;
            }
        }
    }

    // Display the values for each dice rolled
    if (*numOfDice == 1) {
        cout << "You decided to roll 1 die. This is the result of your die: " << diceContainer[0] << endl;
        // cout <<  << endl;
    }
    else {
        cout << "You decided to roll " << *numOfDice << " dice. " << "These are the results of your dice: " << endl;
        for(int i = 0; i < *numOfDice; i++) {
            cout << diceContainer[i] << " ";
        }
        cout << " " << endl;
    }
}

void Dice::keepTracks() {

    //Diplays percentage of each values rolled up to now
    cout << "\nPercentage of all values rolled up to now" << endl;
    for(int i = 0 ; i< 6; i++) {
    double percentage = ((double)valuesTracker[i]/(double)*timesRolled) * 100;
    cout << (i+1) << ": " << percentage << "%" << endl;

}
        cout << "Total number of times you rolled a die: " << *timesRolled << "\n" << endl;
}
