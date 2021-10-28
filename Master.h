#ifndef MASTER_H 
#define MASTER_H

#include <iostream>
#include<vector>
#include <string>
#pragma once

using namespace std;

typedef std::vector<char> vecChar;

class Master
{
public:
    Master(size_t, size_t, size_t, bool);
    void Play();
    ~Master();

private:
    void ShowBoard();
    string GetInput();
    bool CheckInput(string);
    string GetCombo();

    size_t codeLen, letterCnt, guessCnt;
    bool repeatLetter;
    vector<vecChar> guesses, results;
    string letters, combo;
};

#endif