#include "Master.h"
#include <algorithm>

using namespace std;

Master::Master(size_t codeLength, size_t letterCount, size_t guessCount, bool canRepeatLetter) {

	const string availableLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (codeLength < 2) codeLength = 2;
	if (!canRepeatLetter && letterCount < codeLength) letterCount = codeLength;
	if (letterCount < 2) letterCount = 2;
	if (guessCount < 2) guessCount = 2;

	codeLen = codeLength;
	letterCnt = letterCount;
	guessCnt = guessCount;
	repeatLetter = canRepeatLetter;

	for (size_t s = 0; s < letterCnt; s++) {
		letters.append(1, availableLetters.at(s));
	}
}

void Master::Play() {
	bool win = false;
	combo = GetCombo();

	while (guessCnt) {
		ShowBoard();
		if (CheckInput(GetInput())) {
			win = true;
			break;
		}
		guessCnt--;
	}

	if (win) {
		cout << "\n\n--------------------------------\n" <<
			"Well done, you found the code! " << combo <<
			"\n--------------------------------\n\n";
	}
	else {
		cout << "\n\n--------------------------------\n" <<
			"I am sorry, you couldn't make it!\nThe code was: " << combo <<
			"\n--------------------------------\n\n";
	}
}
Master::~Master()
{
}

void Master::ShowBoard() {
	vecChar::iterator y;

	for (int x = 0; x < guesses.size(); x++) {
		cout << "\n--------------------------------\n";
		cout << x + 1 << ": ";
		for (y = guesses[x].begin(); y != guesses[x].end(); y++) {
			cout << *y << " ";
		}

		cout << " :  ";
		for (y = results[x].begin(); y != results[x].end(); y++) {
			cout << *y << " ";
		}

		int z = codeLen - results[x].size();
		if (z > 0) {
			for (int x = 0; x < z; x++) cout << "- ";
		}
	}
	cout << "\n\n";
}

string Master::GetInput() {
	string a;

	while (true) {
		cout << "Enter your guess (" << letters << "): ";
		a = "";
		cin >> a;

		transform(a.begin(), a.end(), a.begin(), ::toupper);

		if (a.length() > codeLen)
			a.erase(codeLen);

		bool r = true;

		for (string::iterator x = a.begin(); x != a.end(); x++) {
			if (letters.find(*x) == string::npos) {
				r = false;
				break;
			}
		}

		if (r) break;
	}
	return a;
}

bool Master::CheckInput(string a) {
	vecChar g;

	for (string::iterator x = a.begin(); x != a.end(); x++) {
		g.push_back(*x);
	}
	guesses.push_back(g);

	int black = 0, white = 0;
	vector<bool> gmatch(codeLen, false);
	vector<bool> cmatch(codeLen, false);

	for (int i = 0; i < codeLen; i++) {
		if (a.at(i) == combo.at(i)) {
			gmatch[i] = true;
			cmatch[i] = true;
			black++;
		}
	}

	for (int i = 0; i < codeLen; i++) {
		if (gmatch[i]) continue;
		for (int j = 0; j < codeLen; j++) {
			if (i == j || cmatch[j]) continue;
			if (a.at(i) == combo.at(j)) {
				cmatch[j] = true;
				white++;
				break;
			}
		}
	}

	vecChar r;

	for (int b = 0; b < black; b++) r.push_back('X');
	for (int w = 0; w < white; w++) r.push_back('O');

	results.push_back(r);

	return (black == codeLen);
}

string Master::GetCombo() {
	string c, clr = letters;
	int l, z;

	for (size_t s = 0; s < codeLen; s++) {
		z = rand() % (int)clr.length();
		c.append(1, clr[z]);
		if (!repeatLetter) clr.erase(z, 1);
	}

	return c;
}