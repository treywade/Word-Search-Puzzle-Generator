//
// Created by trey on 2021-11-14.
//

#ifndef ASSIGMENT4_2_JUMBLEPUZZLE_18GDW_H
#define ASSIGMENT4_2_JUMBLEPUZZLE_18GDW_H
using namespace std;
typedef char* charArrayPtr;

#endif //ASSIGMENT4_2_JUMBLEPUZZLE_18GDW_H


class BadJumbleException{
public:
    BadJumbleException(const string &message);
    string& what();
private:
    string message;
};

class JumblePuzzle{
public:
    //Constructos for JumblePuzzle
    JumblePuzzle(const string &hide, const string &diff);
    JumblePuzzle(const JumblePuzzle &jumble);
    //Deconstructor
    ~JumblePuzzle();
    //Overriding Operator
    JumblePuzzle& operator=(const JumblePuzzle& rhs);
    //Getters
    charArrayPtr* getJumble() const;
    string getToHide() const;
    int getDiffMult() const;
    int getSize() const;
    int getRowPos() const;
    int getColPos() const;
    char getDirection() const;

private:
    //Private Class Memebers
    string toHide;
    int diffMult;
    int size;
    char** puzzle;
    int rowPos;
    int colPos;
    char dir;

};
