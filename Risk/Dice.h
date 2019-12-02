#pragma once
#include <memory>
#include <vector>

class Dice {  
public:
    Dice(); //constructor
    ~Dice();
    Dice(const Dice& orig); // copy constructor
    const Dice &operator=(const Dice &d);
    void setDiceToRoll(int numOfDice); //function to ask to how many dice the player wants to roll
    void rollDice(); //function to roll the dice
    void keepTracks(); //function to keep tracks of the rolled values
    std::vector<int> getValuesRolled(); //function to get the values rolled
    void clearDiceRolled();
private:
    std::unique_ptr<int> numOfDice; // Smart pointer to number of dice that will be rolled
    int valuesTracker[6]; //arrays that tracks the different values
    std::unique_ptr<int> timesRolled; //number of time the dice were rolled
    std::vector<int> valuesRolled;
};
