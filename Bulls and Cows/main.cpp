/*This is the console executable, that makes use of the BullCow class
This acts ast the view in a MVC pattern, and is responsible for al user interaction.
For game logic see the FBullCowGame class*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //create a new instance of the game

//start of the aplication
int main()
{
	bool bPlayAgain;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} 
	while (bPlayAgain);
	
	return 0; //end of the applications
}

void PrintIntro() 
{
	//introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " <<  BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset();
	const int32 MaxTries = BCGame.GetMaxTries();
	//loop for the number of turns asking for guesses
	for (int32 count = 0; MaxTries > count; count++) {	// TODO change from for to while loop
		FText Guess = GetValidGuess(); // TODO make loop checking valid guesses


		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	//TODO summarise game

}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		int32 CurrentGuess = BCGame.GetCurrentTry();
		//get a guess from the player
		std::cout << "Try " << CurrentGuess << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Enter a " << BCGame.GetHiddenWordLength() << " letters word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "You have to enter an isogram.\n";
		case EGuessStatus::Not_Lowercase:
			std::cout << "Enter all letters in lowercase.\n";
			break;
		default: //valid guess
			Status = EGuessStatus::OK;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //loops until there are no input errors

	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y'); //exit the application
}
