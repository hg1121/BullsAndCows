//
//  main.cpp
//  BullCowGame
//
//  Created by Kaiyan Li on 8/12/19.
//  Copyright © 2019 Kaiyan Li. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
int32 GetHiddenWordLength();
void PrintGameSummary();

FBullCowGame BCGame;//instantiate a new game

// the entry point for our application
int main(int32 argc, const char * argv[])
{
    // insert code here...
    do
    {
        PrintIntro();
        PlayGame();
    }
    while (AskToPlayAgain());

    return 0;//exit the game
}


void PrintIntro()
{
    //Introduce the game.
    const FString  HIDDEN_WORD = "planet";
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

     //loop asking for guesses while the game .
     //is not Won and there are still tries remaining
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        #warning TODO change from for to while loop once we are validating tries
        FText Guess = GetValidGuess();
        
    //submit valid GUESS
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
    
    //Print number of BULLS and COWS
        std::cout <<"Bulls = " << BullCowCount.Bulls;
        std::cout <<"  Cows = " << BullCowCount.Cows << "\n\n";
    }
    PrintGameSummary();
    return;
    
}
FText GetValidGuess() // loop continuely untill the user gives a valid guess
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    do {
         #warning change to valid guess
        int32 CurrentTry = BCGame.GetCurrentTry();
        
        //Get the guess from player
        std::cout << "Try " << CurrentTry <<".Please enter your Guess:";
        std::getline (std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " <<BCGame.GetHiddenWordLength() << " letter word \n";
                break;
                
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.. \n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters. \n";
                break;
            default:
                break;
        }
            std::cout << std::endl;
    }while (Status != EGuessStatus::OK); // keep looping untill we get no errors
    return Guess;
}


bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? y/n\n";
    FText Response = "";
    std::getline(std::cin,Response);

    return (Response[0] == 'y') ||( Response[0] == 'Y');
}

//summaries game
void PrintGameSummary()
{
    if  (BCGame.IsGameWon()){
        std::cout << " -- WELL DONE, YOU WIN--\n";
    }else{
        std::cout << " --Better luck next time--\n";
    }
}

