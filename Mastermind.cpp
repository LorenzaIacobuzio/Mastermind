#include <string>
#include <vector>
#include <iostream>
#include "Master.h"

typedef std::vector<char> vecChar;
using namespace std;

int main(int argc, char* argv[]) {
    int codeLen = 0;
    int letterCnt = 27;
    int guessCnt = 0;
    string repeat = "";
    string repeatLtr = "";
    bool repeatLetter = false;

    cout << "Welcome to Mastermind! \n";
    cout << "Please enter the length of the combination you want to guess \n";
    cin >> codeLen;

    while (letterCnt > 26) {
        cout << "Please enter the number of letters you want to play with (26 maximum) \n";
        cin >> letterCnt;
    }

    cout << "Please enter the number of times you want to guess \n";
    cin >> guessCnt;

    cout << "Do you want to repeat letters? [y/n] \n";
    cin >> repeat;

    if (repeat.compare("y") == 0)
        repeatLetter = true;

    cout << "You have chosen a " << codeLen << "-letter long combination \n";
    cout << "With " << letterCnt << " letters and " << guessCnt << " guesses \n";
    cout << "Remember that 'X' indicates correct letter and position, 'O' only correct letter, and '-' neither \n";

    Master m(codeLen, letterCnt, guessCnt, repeatLetter);
    m.Play();

    return 0;
}
