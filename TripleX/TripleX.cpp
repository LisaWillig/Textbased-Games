#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <vector>

int x, y, z;
int level;
bool gameOver = false;

int multiplicationResult(int x, int y, int z){
    return x*y*z;
}

int sumResult(int x, int y, int z){
    return x+y+z;
}

void printIntro(){
    std::cout << "Hello! Let us play a game! You enter the first level\n";
}

void printLevelIntro(int currentLevel){
    std::cout << "Your current Level is " << currentLevel <<"\n";
    std::cout << "Guess the three Numbers!\n";
    std::cout << "Your hints are:\n";
    std::cout << "Multiplied they are resulting to: " << multiplicationResult(x, y, z) << "\n";
    std::cout << "Summed up they are resulting to: " << sumResult(x, y, z) << "\n";
}

int randomNumber(){
    // initialize random seed: 
    srand (time(NULL));
    // generate secret number between 1 and 10: 
    return rand() % 10 + 1;
}

void createNumbers(){
    x = randomNumber();
    y = randomNumber();
    z = randomNumber();
}

void winningScreen(){
        std::cout << "Congratulations! You advanced to the next level!\n";
        level++;
        createNumbers();
}

void gameOverScreen(){
        std::cout<< "Oh no! You failed! You have to start all over again :(\n";
        std::cout << "The correct code was: " << x << " " << y << " " << z << "\n";
        std::cout<< "Do you want to quit? (Y/N)\n";
        std::string quit = "";
        std::getline(std::cin, quit);
        if (quit[0] == 'Y' || quit[0] == 'y'){
            gameOver = true;
        }
        else{level = 1;}
}
void checkAnswer(){

    int GuessA,GuessB,GuessC;
    
    std::cin >> GuessA;
    std::cin >> GuessB;
    std::cin >> GuessC;
    std::cin.ignore(1000, '\n');

    //Compare the numbers to given numbers
    if (sumResult(GuessA, GuessB, GuessC) == sumResult(x,y,z) 
        && 
        multiplicationResult(GuessA, GuessB, GuessC) == multiplicationResult(x,y,z)){

            winningScreen();
        }
    else{
        gameOverScreen();
    }
}

int main(){
    level = 1;
    printIntro();
    createNumbers();
    while (gameOver==false){
        printLevelIntro(level);
        checkAnswer();
    }
    return 0;
}