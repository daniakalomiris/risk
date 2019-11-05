#pragma once
#include <memory>
#include <vector>



//class that contains a dice facility
class Dice {

    public:

        //constructor
        Dice();
        ~Dice();
        //function to ask to how many dice the player wants to roll
        void setDiceToRoll(int diceToRoll);

        //function to roll the dice
        void rollDice();

        //function to keep tracks of the rolled values
        void keepTracks();
        
        //function to get the values rolled
        std::vector<int> getValuesRolled();
    
    private:
    // Smart pointer to number of dice that will be rolled
    std::unique_ptr<int> numOfDice;

     //arrays that tracks the different values
    int valuesTracker[6];

    //number of time the dice were rolled
    std::unique_ptr<int> timesRolled;
    
    std::vector<int> valuesRolled;

};
