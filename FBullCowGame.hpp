//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Kaiyan Li on 8/13/19.
//  Copyright © 2019 Kaiyan Li. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h> 
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame
{
public:
    FBullCowGame();//constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    

    void Reset();
    #warning Todo make a more rich return value.
    EGuessStatus CheckGuessValidity(FString) const;
    #warning Todo make a more rich return value.
    FBullCowCount SubmitValidGuess(FString);

//^ ^ please try and ignore this and focus on the interface above. ^ ^
private:
    //see constructor for initialization.
    int32 MyCurrentTry ;
    int32 MyMaxTries ;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
    };
#endif /* FBullCowGame_hpp */
