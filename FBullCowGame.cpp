//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Kaiyan Li on 8/13/19.
//  Copyright © 2019 Kaiyan Li. All rights reserved.
//

#pragma once
#include "FBullCowGame.hpp"
#include <iostream>
#include <map>

//to make the syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame()
{
    Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32,int32> WordLengthToMaxTries {{3,4},{4,7},{5,10},{6,15}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
    
    
}

bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
}

void FBullCowGame::Reset(){
    constexpr int32 MAX_TRIES = 5;
    MyMaxTries = MAX_TRIES;
    
    const FString  HIDDEN_WORD = "feak";// this MUST be a isogram word
    MyHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
    
    MyCurrentTry = 1;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    }
    
    else if (!IsLowercase(Guess)){
        return EGuessStatus::Not_Lowercase;
    }
    
    //if the length of guess is wrong return an error
    else if (Guess.length() != GetHiddenWordLength()){
        return EGuessStatus::Wrong_Length;
    }
    //otherwise return ok
    else{
    return EGuessStatus::OK ;
    }
}

//receives a VALID guess,increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
    
    //loop through all letters in the Hiddenword
    for (int32 i = 0; i < WordLength; i++) {
        //compare the letters against the guess
        for(int32 j = 0; j < WordLength; j++){
            //if they match then
            if (Guess[i] == MyHiddenWord[j]) {
                //if they are in same palace
                if (i == j){
                    
                    BullCowCount.Bulls++;//increment bulls
                }
                //else
                else {
                    
                    BullCowCount.Cows++;//increment cows
                }
    
            }
        
        }
    }
    if (BullCowCount.Bulls == WordLength && GetCurrentTry() <= MyMaxTries) {
        bGameIsWon = true;
    }else{
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    //treat 0 or 1 letter word as isogram
    if (Word.length() <= 1) {return true;}
    TMap<char, bool> LetterSeen; //setup the map
    for(auto Letter : Word)  //for all letters of the word
    {
        Letter = tolower(Letter); // handle all cases
        //if the letter is in the map
        if (LetterSeen[Letter]) {return false;}//we do not have an isogram
        else{
            LetterSeen[Letter] = true; //add the letter to the map as seen
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter: Word) {
        if (!islower(Letter)) { return false;}
    }
    return true;
}
