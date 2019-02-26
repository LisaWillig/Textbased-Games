/*Game class managing the logic behind the Bull Cow Game:
- validates guesses
- counts Bulls and Cows by comparing guess to hidden word
- manages current and max tries
- gets reset to start the game again.*/

#pragma once
#include <string>

using FString = std::string; 
using int32 = int; 

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0; 
};

enum class EGuessStatus { 
	//strongly typed enum, names can be used in othere enums 
	//(without class-keyword, this is not the case)
	INVALID, 
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Not_Unicode,
};

enum class EResetStatuus {
	No_Hidden_Word,
	OK, //global scope
};
class FBullCowGame {
public:
	FBullCowGame(); //Constructor

	int32 GetHiddenWordLength() const;
	int32 GetMaxTries() const; 
	int32 GetCurrentTry() const;
	FString GetHiddenWord() const;
	void SetHiddenWord(FString);

	bool IsGameWon() const; 
	bool GameWon(FBullCowCount BullCowCount);
	bool IsIsogram(FString) const;
	EGuessStatus CheckGuessValidity(FString);
	/* Getter functions: function that returns a private variable */

	/* const has a different meaning in different positions: 
	at the end of member function: 
	not allowed to change member variables in the function. 
	Always use that when wiriting a "getter" function! 
	Just works in class functions */

	void Reset(); 

	FBullCowCount SubmitValidGuess(FString);


private:
	//Compile time values -> are overriden at runtime by constructor
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord; 
	bool IsLowerCase(FString) const;
	bool bGameWon;
	//bool IsOneWord;
};

