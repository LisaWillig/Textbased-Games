/*This is the console executable that makes use of the BullCowClass.
This acts as the view in a MVC pattern, and is responisble for all
user interaction. For game logic see the FBUllCowGame class*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#include "readInput.h"
#include <random>

//to make syntax unreal friendly
#define TMap std::map;
using FText = std::string;
using int32 = int; 

std::vector<FString> words;
bool bGameWon = false;
int difficultyLength = 4;

void createNewWordFromDictionary(int &difficultyLength);
int randomNumber(int const &size);
void PrintIntro();
void PrintOutro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void restart(bool);

FBullCowGame BCGame;


int main() {
	
	bool bPlay = false;
	restart(false);
	do {
		PrintIntro();
		PlayGame();
		bPlay = AskToPlayAgain();
	} while (bPlay);

	return 0;
}

//play one game instance to completion
void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	FBullCowCount BullCowCount;


	while (!BCGame.GameWon(BullCowCount) && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << "& Cows: " << BullCowCount.Cows << "\n\n";
		std::cout << "Try:  " << BCGame.GetCurrentTry() << " of " << MaxTries << std::endl;
	}
	if (BCGame.GameWon(BullCowCount) || BCGame.GetCurrentTry() >= MaxTries) {
		PrintOutro();
	}

}

//loop until user gives valid guess
FText GetValidGuess(){

	EGuessStatus Status = EGuessStatus::INVALID; 
	FText Guess = "";
	
	do {

		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Please enter a valid guess: "; 
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word! \n" << std::endl;
			break;
		case EGuessStatus::Not_Isogram://TODO create function for detecting this error!
			std::cout << "This is not an Isogram! Please enter an Isogram (each letter appears only once in the word)\n " << std::endl;
			break;
		case EGuessStatus::Not_Lowercase: //TODO create function for detecting this error!
			std::cout << "This game supports only lowercase. Please write in lowercase only!\n " << std::endl;
			break;
		case EGuessStatus::Not_Unicode://TODO create function for detecting this error!
			std::cout << "Please only write standard unicode letter words! \n" << std::endl;
			break;
		default:
			continue; 
		}

	} while (Status != EGuessStatus::OK);
	return Guess;
}


void PrintIntro(){
	//introduce the game
	std::cout << "\n\n Welcome to Bulls and Cows, a fun word game!" << std::endl;
	std::cout << "Can you guess the " << difficultyLength
		<< " letter isogram I'm thinking of? " << std::endl; 
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;
	std::cout << "  We are playing the Bull & Cow Game." << std::endl;
	std::cout << "  That means after you enter a valid guess you will get a count of Bulls and Cows. "<< std::endl;
	std::cout << "  Bulls: a letter is at the correct position in the word. " << std::endl;
	std::cout << "  Cows: a letter is correct but not at the right position. " << std::endl;
	std::cout << "  We are only looking for Isograms, so words where no letter appears twice. " << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void PrintOutro() {
	if (BCGame.IsGameWon()) {
		bGameWon = true;
		std::cout << "Well done! You have won! \n";
		std::cout << "Thank you for playing :)\n";
		std::cout << "Please come back another time.";
	}
	else {
		std::cout << "!! GAME OVER !!\n";
		std::cout << "Better luck next time!\n oOOo";
		bGameWon = false;
	}
}

bool AskToPlayAgain() {
	if (bGameWon == false) {
		std::cout << "Do you want to know the solution? (y/n)" << std::endl;
		FText Response = "";
		std::getline(std::cin, Response);
		if (Response[0] == 'y' || Response[0] == 'Y') {
			std::cout << BCGame.GetHiddenWord() << std::endl;
			std::cout << "\n\n Do you want to play again with a new word? (y/n)";
			FText Response = "";
			std::getline(std::cin, Response);
			if (Response[0] == 'y' || Response[0] == 'Y') {
				restart(false);
			}
			return (Response[0] == 'y' || Response[0] == 'Y');
		}
		if (Response[0] == 'n' || Response[0] == 'N') {
			std::cout << "\n\n Do you want to play again with this word? (y/n)";
			FText Response = "";
			std::getline(std::cin, Response);
			if (Response[0] == 'y' || Response[0] == 'Y') {
				restart(true);
			}
			return (Response[0] == 'y' || Response[0] == 'Y');
		}
	}
	else if (bGameWon == true) {
		std::cout << "\n\n Do you want to play again with a new word? (y/n)";
		FText Response = "";
		std::getline(std::cin, Response);
		if (Response[0] == 'y' || Response[0] == 'Y') {
			restart(false);
		}
		return (Response[0] == 'y' || Response[0] == 'Y');
	}
		
}

void restart(bool bKeepWord) {
	if (bKeepWord != true) {
		createNewWordFromDictionary(difficultyLength);
	}
	BCGame.Reset();
}

int randomNumber(int const &size)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, size); // define the range

	return distr(eng);
}

void createNewWordFromDictionary(int &difficultyLength) {
	std::vector<std::string> myDictionary;
	readVectorFromFile(myDictionary);

	for (int entry = 0; entry < myDictionary.size(); entry++) {
		std::string wordInQuestion = myDictionary[entry];
		if (wordInQuestion.size() == difficultyLength && BCGame.IsIsogram(wordInQuestion)) {
			words.push_back(wordInQuestion);
		}
	}
	int rand = randomNumber(words.size());
	BCGame.SetHiddenWord(words[rand]);
}