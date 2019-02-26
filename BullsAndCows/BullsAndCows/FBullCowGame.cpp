#pragma once;
#include "FBullCowGame.h"
#include <iostream>
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{	
	FBullCowGame::Reset();	 
}

int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; } //quite common style for "Getter" methods: put it together and on top
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
void FBullCowGame::SetHiddenWord(FString Word) {MyHiddenWord = Word;}
bool FBullCowGame::IsGameWon() const { return bGameWon; }


bool FBullCowGame::GameWon(FBullCowCount BullCowCount) {
	if (BullCowCount.Bulls == GetHiddenWordLength() && GetHiddenWordLength()!= 0) {
		return bGameWon=true;
	}
	else {
		return bGameWon = false; 
	}
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	MyHiddenWord = GetHiddenWord();
	bGameWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WorldLengthToMaxtries{ 
		{3, 4}, 
	    {4, 7},
	    {5, 10},
	    {6, 16},
	    {7, 20},
	};
	return WorldLengthToMaxtries[GetHiddenWordLength()];
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString GuessWord) 
{
	if (!IsIsogram(GuessWord)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(GuessWord)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (GuessWord.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else if (false) {
		return EGuessStatus::Not_Unicode;
	}
	else
	{
		return EGuessStatus::OK;
	} 
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString GuessWord) {
	MyCurrentTry++;
	FBullCowCount BullCowCount; 
	int32 WordLength = MyHiddenWord.length(); 
	//assuming both words have the same length

	for (int32 i = 0; i < WordLength; i++) {
		for (int32 j = 0; j < WordLength; j++) {
			if (i == j) {
				if (GuessWord[i] == MyHiddenWord[j]) {
					BullCowCount.Bulls++;
				}
			}
			else {
				if(GuessWord[i] == MyHiddenWord[j])
					BullCowCount.Cows++;
			}
		}
	}
	return BullCowCount; 
}

//easier
/* if (Guess[i] == MyHiddenWord[j]
if (i == j)
BullCowCount.Bulls++;
else BullCowcount.Cow++;
*/

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool>  letterSeen;

	for (auto letter : Word) {
		//for all letters of the word, range-based loop, ":" means "in" in this case
		//auto: compiler gets the type og the variable iteslf
		letter = tolower(letter);
		if (letterSeen[letter]) {
			return false;
		}
		else { letterSeen[letter] = true; }
		
    }
	return true; // for examples in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	int count = 0;
	for (auto letter : Word) {
		if (letter == '\0') {
			count--;
		}
		if (!islower(letter)) {
			count++;
		}
	}
	if (count != 0) { return false; }
	else return true;
}
