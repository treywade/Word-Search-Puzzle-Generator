//
// Created by trey on 2021-11-14.
//

#include <iostream>
#include "cstdlib"
#include "jumblePuzzle_18gdw.h"

using namespace std;


BadJumbleException::BadJumbleException(const string &message) : message(message){}
string& BadJumbleException::what() {return message;}

JumblePuzzle::JumblePuzzle(const string& hide, const string& diff){
    //SEED FOR RAND WAS PUT IN THE TESTING
    int strLength = hide.length();
    if (strLength < 3 || strLength > 10){
        throw BadJumbleException("Error: Word to hide must have a length in the range 3 - 10 letters long");
    }
    //If the entered string is valid assign it
    toHide = hide;
    //Check the difficulty entered by the user
    if (diff == "easy") {
        diffMult = 2;
    } else if (diff == "medium") {
        diffMult = 3;
    } else if (diff == "hard"){
        diffMult = 4;
    } else {
        throw BadJumbleException("Error: Diffuculty must be one of easy, medium, hard must be chosen");
    }
    //After confirming string and difficulty determine size of puzzle needed
    //Calculate the size of the puzzle
    size = diffMult * strLength;

    //Initialize the 2D array that will hold the puzzle
    //cout << "Here 1" << endl;
    puzzle = new charArrayPtr[size];
    //Allocated arrays of size puzzleSize in each element of the elements of puzzle
    for (int i = 0; i < size; i++) {
        puzzle[i] = new char[size];
    }
    //Initialize the whole puzzle with random characters
    for (int col = 0; col < size; col++) {
        for (int row = 0; row < size; row++) {
            puzzle[row][col] = 'a' + rand() % 26;
        }
    }
    //Get Random Positions to Hide the given word
    rowPos = rand() % size;
    colPos = rand() % size;
    //These are so I dont have continuously refernce the class members
    int hideRow = getRowPos();
    int hideCol = getColPos();
    int puzzleSize = getSize();
    //Get Random Direction
    int direction = rand() % 4;
    //Direction allowed Flag
    int directionAllowed = 0;
    while (directionAllowed == 0) {
        if (direction == 0) {
            //North
            if (this -> getRowPos() - strLength + 1 > -1) {
                directionAllowed = 1;
                this -> dir = 'n';
            } else {
                direction++;
            }
        } else if (direction == 1) {
            //East
            if (this -> getColPos() + strLength - 1 < puzzleSize) {
                directionAllowed = 1;
                this -> dir = 'e';
            } else {
                direction++;
            }
        } else if (direction == 2) {
            //South
            if (this -> getRowPos() + strLength - 1 < puzzleSize) {
                directionAllowed = 1;
                this -> dir = 's';
            } else {
                direction++;
            }
        } else if (direction == 3){
            //West
            if (this -> getColPos() - strLength + 1 > 0) {
                directionAllowed = 1;
                this -> dir = 'w';
            } else {
                direction = 0;
            }
        }
    }
    //Temp to put word in puzzle
    int charCount = 0;
    if (this -> dir == 'n'){
        while (charCount < strLength){
            puzzle[hideRow][hideCol] = this->toHide.at(charCount);
            charCount++;
            //Move Downwards in the puzzle
            hideRow--;
        }
    } else if (this -> dir == 'e'){
        while (charCount < strLength){
            puzzle[hideRow][hideCol] = this->toHide.at(charCount);
            charCount++;
            //Move to the right in the puzzle
            hideCol++;
        }
    } else if (this -> dir == 's'){
        while (charCount < strLength){
            puzzle[hideRow][hideCol] = this->toHide.at(charCount);
            charCount++;
            //Move upwards in the puzzle
            hideRow++;
        }
    } else {
        while (charCount < strLength){
            puzzle[hideRow][hideCol] = this->toHide.at(charCount);
            charCount++;
            //Move to the left in the puzzle
            hideCol--;
        }
    }
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle &jumble){
    //Copy Constructor
    //Copy all memebers
    this -> toHide = jumble.toHide;
    this -> diffMult = jumble.diffMult;
    this -> size = jumble.getSize();
    this -> rowPos = jumble.getRowPos();
    this -> colPos = jumble.getColPos();
    this -> dir = jumble.dir;
    //Store a jumble puzzle in a temp
    char** tempPuzzle = jumble.getJumble();
    //Need to make a new 2D array for the new jumble
    this -> puzzle = new charArrayPtr[this -> size];
    for (int i = 0; i < size; i++) {
        puzzle[i] = new char[size];
    }
    for (int col = 0; col < size; col++) {
        for (int row = 0; row < size; row++) {
            puzzle[row][col] = tempPuzzle[row][col];
        }
    }
}



charArrayPtr* JumblePuzzle::getJumble() const{
    //Get Size of original puzzle
    int puzzleSize = size;
    //Create new 2D puzzle
    char **puzzleCopy = new charArrayPtr[puzzleSize];
    for (int i = 0; i < puzzleSize; i++) {
        puzzleCopy[i] = new char[puzzleSize];
    }
    for (int row = 0; row < puzzleSize; row++) {
        for (int col = 0; col < puzzleSize; col++) {
            puzzleCopy[row][col] = puzzle[row][col];
        }
    }
    //Return deep copy of the puzzle
    return puzzleCopy;
}

int JumblePuzzle::getSize() const{
    return diffMult * toHide.length();
}

int JumblePuzzle::getRowPos() const {
    return this -> rowPos;
}

int JumblePuzzle::getColPos() const{
    return this -> colPos;
}

char JumblePuzzle::getDirection() const{
    return this -> dir;
}

JumblePuzzle::~JumblePuzzle() {
    //Deconstrutor
    for (int i = 0; i < getSize(); i++){
        delete puzzle[i];
    }
    delete[] puzzle;
}

JumblePuzzle &JumblePuzzle::operator=(const JumblePuzzle& rhs) {
    //Overriding equals opperator
    toHide = rhs.getToHide();
    diffMult = rhs.getDiffMult();
    size = rhs.getSize();
    rowPos = rhs.getRowPos();
    colPos = rhs.getColPos();
    dir = rhs.getDirection();
    //Temp so i dont need to reference the class member
    int puzzleSize = rhs.getSize();
    char** puzzleCopy = rhs.getJumble();
    for (int row = 0; row < puzzleSize; row++) {
        for (int col = 0; col < puzzleSize; col++) {
            puzzle[row][col] = puzzleCopy[row][col];
        }
    }
    return *this;
}

string JumblePuzzle::getToHide() const {
    return this -> toHide;
}

int JumblePuzzle::getDiffMult() const {
    return this -> diffMult;
}