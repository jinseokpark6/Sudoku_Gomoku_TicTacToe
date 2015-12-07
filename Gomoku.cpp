/*

Authors: Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120



*/

#include "stdafx.h"
#include <vector>
#include "Gomoku.h"
#include <iostream>
#include <iomanip>

using namespace std;


void Gomoku::checkSavedGame(int a, int b) {
	//see if a saved game exists in all three constructors below
	ifstream getGame("gomoku");

	string line;

	if (getGame.is_open()) {
		string firstline;
		getline(getGame, firstline);

		//check the first line of input file to see what data is available
		if ((firstline.compare("NO DATA") != 0 && firstline.compare("COMPLETE") != 0) || firstline.compare("gomoku") == 0) {

			string boardDim;
			getline(getGame, boardDim);

			string connectNeeded;
			getline(getGame, connectNeeded);

			if (stoi(boardDim) != a || stoi(connectNeeded) != b) {
				cout << "The saved game dimension / connect values are " << boardDim << " and " << connectNeeded << ". Ctrl + C to prevent overwrite... Otherwise continue playing" << endl;
			}

			else {
				while (getline(getGame, line)) {
					string letter;
					getline(getGame, letter);
					if (letter.compare("B") == 0) {
						pieces[stoi(line)] = game_piece(bee, "B", "B", stoi(line));
						p1++;
					}
					else if (letter.compare("W") == 0) {
						pieces[stoi(line)] = game_piece(doubleYou, "W", "W", stoi(line));
						p2++;
					}
				}
			}
		}

		getGame.close();
	}
}


// Default Initialization
Gomoku::Gomoku() {

	bufferSize = 21;
	boardSize = 19;
	connectNum = 5;

	gDim = 19;
	gCount = 5;

	pieces.resize(bufferSize * bufferSize);

	p1 = 0;
	p2 = 0;

	for (int i = bufferSize - 1; i >= 0; i--) {
		for (int j = 0; j < bufferSize; j++) {
			int location = (bufferSize*i) + j;
			//label axis
			if (i == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(j);
				if (pieces[location].display.length() > longestStr) {
					longestStr = pieces[location].display.length() + 1;
				}
			}
			else if (j == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(i);
				if (pieces[location].display.length() > longestStr) {
					longestStr = pieces[location].display.length() + 1;
				}
			}
			//if not axes, intialize game_piece in array pieces
			else {
				pieces[location] = game_piece();
			}
		}
	}

	Gomoku::checkSavedGame(boardSize, connectNum);

	//print empty board before starting game
	print();


}

Gomoku::Gomoku(int b) {

	// make the size of the board as input
	bufferSize = b + 2;
	boardSize = b;
	connectNum = 5;

	gDim = b + 2;
	gCount = 5;

	pieces.resize(bufferSize * bufferSize);

	for (int i = bufferSize - 1; i >= 0; i--) {
		for (int j = 0; j < bufferSize; j++) {
			int location = (bufferSize*i) + j;
			//label axis
			if (i == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(j);
				if (pieces[location].display.length() > longestStr) {
					longestStr = pieces[location].display.length() + 1;
				}
			}
			else if (j == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(i);
				if (pieces[location].display.length() > longestStr) {
					longestStr = pieces[location].display.length() + 1;
				}
			}
			//if not axes, intialize game_piece in array pieces
			else {
				pieces[location] = game_piece();
			}
		}
	}

	Gomoku::checkSavedGame(b, connectNum);

	//print empty board before starting game
	print();
}


Gomoku::Gomoku(int b, int c) {

	// make the size of the board as input
	bufferSize = b + 2;
	boardSize = b;
	connectNum = c;

	pieces.resize(bufferSize * bufferSize);

	gDim = b;
	gCount = c;


	for (int i = bufferSize - 1; i >= 0; i--) {
		for (int j = 0; j < bufferSize; j++) {
			int location = (bufferSize*i) + j;
			//label axis
			if (i == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(j);
				if (pieces[location].display.length() > longestStr) {
					longestStr = pieces[location].display.length() + 1;
				}
			}
			else if (j == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(i);
				if (pieces[location].display.length() > longestStr) {
					longestStr = pieces[location].display.length() + 1;
				}
			}
			//if not axes, intialize game_piece in array pieces
			else {
				pieces[location] = game_piece();
			}
		}
	}

	Gomoku::checkSavedGame(b, c);

	//print empty board before starting game
	print();
}



void Gomoku::print() {
	cout << *this << endl;
}

//draws board
ostream & operator << (ostream & o, const Gomoku &ggg) {
	Gomoku frame = ggg;
	for (int i = ggg.bufferSize - 1; i >= 0; i--) {
		for (int j = 0; j < ggg.bufferSize; j++) {
			int location = (ggg.bufferSize*i) + j;
			o << setw(ggg.longestStr) << frame.pieces[location].display;
		}
		o << "\n";
	}
	o << endl;
	return o;
}


bool Gomoku::winner(unsigned int h, unsigned int v) {

	int spot = bufferSize*v + h;

	int minH = 0;
	int maxH = 0;
	int minV = 0;
	int maxV = 0;
	int counter = 0;

	// vertical
	minV = v - (connectNum - 1);
	maxV = v + (connectNum - 1);
	if (minV < 0) minV = 0;
	if (maxV > boardSize) maxV = boardSize;
	for (int i = minV; i <= maxV; i++){
		int tempSpot = bufferSize*i + h;

		if (pieces[tempSpot].display == pieces[spot].display) {
			counter++;
		}
		else {
			counter = 0;
		}
		if (counter == connectNum){
			return true;
		}
	}

	// horizontal
	minH = h - (connectNum - 1);
	maxH = h + (connectNum - 1);
	if (minH < 0) minH = 0;
	if (maxH > boardSize) maxH = boardSize;
	for (int i = minH; i <= maxH; i++){
		int tempSpot = bufferSize*v + i;
		if (pieces[tempSpot].display == pieces[spot].display) {
			counter++;
		}
		else {
			counter = 0;
		}
		if (counter == connectNum) {
			return true;
		}
	}

	// decreasing diagonal
	minV = v - (connectNum - 1);
	maxV = v + (connectNum - 1);
	minH = h - (connectNum - 1);
	maxH = h + (connectNum - 1);
	for (int i = minV; i <= maxV; i++){
		if (!(i < 0 || i > boardSize)) {
			int tempSpot = bufferSize*i + (h + v - i);
			if (pieces[tempSpot].display == pieces[spot].display) {
				counter++;
			}
			else {
				counter = 0;
			}
			if (counter == connectNum){
				return true;
			}
		}
	}

	// increasing diagonal
	minV = v - (connectNum - 1);
	maxV = v + (connectNum - 1);
	minH = h - (connectNum - 1);
	maxH = h + (connectNum - 1);

	for (int i = minV; i <= maxV; i++){
		if (!(i < 0 || i > boardSize)) {
			int tempSpot = bufferSize*i + i;
			if (pieces[tempSpot].display == pieces[spot].display) {
				counter++;
			}
			else {
				counter = 0;
			}
			if (counter == connectNum){
				return true;
			}
		}
	}

	return false;
}


bool Gomoku::done() {

	if (Gomoku::winner(h, v)) {
		return true;
	}

	return false;
}

bool Gomoku::stalemate() {

	//if someone won, no draw
	if (done()) {
		return false;
	}

	bool taken = false;
	int allTaken = 0;

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			int loc = bufferSize + i*bufferSize + j + 1;
			if (pieces[loc].display == "W" || pieces[loc].display == "B") {
				//checks all pieces to see if they're filled
				taken = true;
				allTaken++;
			}
			else {
				taken = false;
			}
		}
	}

	//if entire board is full and no one has won, draw
	if (allTaken == boardSize*boardSize) {
		return true;
	}

	// checks to see if stalemate will occur if one spot remains in the entire board
	else if (allTaken == (boardSize*boardSize) - 1) {
		vector<int> spot = whereEmpty();

		//if you 'inject' the last spot into checking winning condition,
		//and a player can win, then no draw
		if (winner(spot[1], spot[0])) {
			return false;
		}

		//otherwise, will be a draw so end game early
		else {
			return true;
		}
	}

	//if entire board is not full and no one has won yet, no draw
	else {
		return false;
	}
}

//helper method that determines where the last remaining spot it
vector<int> Gomoku::whereEmpty() {

	int allTaken = 0;
	int spot = 0;
	vector<int> res;

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			int loc = bufferSize + i*bufferSize + j + 1;
			if (pieces[loc].display == "W" || pieces[loc].display == "B") {
				//checks all pieces to see if they're filled
				allTaken++;
			}
			else {
				spot = loc;
			}
		}
	}

	if (allTaken == boardSize*boardSize) {
		return res;
	}
	else {
		//push into vector<int> to pass along to winner(int, int)
		int ver = spot / bufferSize;
		int hor = spot % bufferSize;
		res.push_back(ver);
		res.push_back(hor);
		return res;
	}

}


int Gomoku::turn() {
	//assign players to different int values
	//if alternate%2 == 0, then player O and if == 1, then player X
	if (p1 > p2) {
		alternate++;
	}

	string playerO = "Player W: ";
	string playerX = "Player B: ";

	unsigned int horiz, vert;

	//start game by prompting user
	int start = prompt(horiz, vert);

	//prompted user, but they quit
	if (start == quit) {
		return quit;
	}

	//if player didn't quit, but prompt returned wrong input
	else if (start == wrongInput) {

		start = prompt(horiz, vert);
		if (start == wrongInput) {

			//call turn() until valid input given or quit
			return turn();
		}
		else if (start == promptComplete) {
			alternate++;

			//go into helper method to continue game
			int going = keep_turning(h, v, alternate, playerO, playerX);

			//check what going returns
			if (going == winW) {
				return winW;
			}
			else if (going == winB) {
				return winB;
			}
			else if (going == draww) {
				return draww;
			}
			else if (going == quit) {
				return quit;
			}
		}
		else if (start == quit) {
			return quit;
		}
	}
	//everything is valid so continue game
	else if (start == promptComplete) {
		alternate++;
		//go into helper method to continue game
		int going = keep_turning(h, v, alternate, playerO, playerX);

		if (going == winW) {
			return winW;
		}
		else if (going == winB) {
			return winB;
		}
		else if (going == draww) {
			return draww;
		}
		else if (going == quit) {
			return quit;
		}
	}

	return success;

}


bool Gomoku::is_valid(unsigned int horiz, unsigned int vert) {
	int loc = (bufferSize)*vert + horiz;

	//checking out of bounds condition

	if (loc < bufferSize + 1 || loc > bufferSize * bufferSize - 1) {
		return false;
	}

	//if it's not an empty space or has X or O, then spot is already taken
	else if (pieces[loc].display != " " || pieces[loc].display == "W" || pieces[loc].display == "B") {
		return false;
	}

	else {
		//empty spot - can be taken
		return true;
	}
}


int Gomoku::keep_turning(unsigned int hh, unsigned int vv, unsigned int alternate, string playerO, string playerX) {
	int start;

	//check if the spot is already taken
	if (is_valid(h, v) == false) {
		cout << "Please choose another spot." << endl;
		start = prompt(hh, vv);
		//at any point, if user quits, the game should exit out
		if (start == quit){
			return quit;
		}
		else if (start == wrongInput) {
			start = prompt(hh, vv);
			if (start == quit) {
				return quit;
			}
		}
		return keep_turning(hh, vv, alternate, playerO, playerX);
	}

	//found empty spot, continue
	else {
		if (alternate % 2 == 0) {

			int loc = bufferSize*v + h;
			pieces[loc] = game_piece(doubleYou, "W", "W", loc);
			if (pieces[loc].display.length() > longestStr) {
				longestStr = pieces[loc].display.length();
			}

			//update board
			print();

			playerO += to_string(h) + ", " + to_string(v) + "; ";
			alternate++;
			cout << playerO << endl;

			numSpots++;

			//check game conditions after every move
			if (done()) {
				return winW;
			}
			else if (stalemate()) {
				return draww;
			}
			else {
				cout << "\nPlayer B's turn" << endl;
				unsigned int a, b;
				//no one has won and the game is not a draw
				int ask = prompt(a, b);

				//again, make sure user can quit
				if (ask == quit){
					return quit;
				}
				else if (ask == wrongInput) {
					ask = prompt(a, b);
					if (ask == quit) {
						return quit;
					}
				}
				return keep_turning(a, b, alternate, playerO, playerX);
			}
		}
		else if (alternate % 2 == 1) {
			int loc = bufferSize*v + h;
			pieces[loc] = game_piece(bee, "B", "B", loc);
			if (pieces[loc].display.length() > longestStr) {
				longestStr = pieces[loc].display.length();
			}

			//update board
			print();

			playerX += to_string(h) + ", " + to_string(v) + "; ";
			cout << playerX << endl;
			alternate++;
			numSpots++;

			if (done()) {
				return winB;
			}
			else if (stalemate()) {
				return draww;
			}
			else {
				cout << "\nPlayer W's turn" << endl;
				unsigned int a, b;
				int ask = prompt(a, b);
				if (ask == quit) {
					return quit;
				}
				else if (ask == wrongInput) {
					ask = prompt(a, b);
					if (ask == quit) {
						return quit;
					}
				}
				return keep_turning(a, b, alternate, playerO, playerX);
			}
		}
	}
	return endOfGame;
}

int Gomoku::moveCount() {
	int moves = 0;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			int loc = bufferSize + i*(bufferSize)+j + 1;
			if (pieces[loc].display == "B" || pieces[loc].display == "W") {
				//checks all pieces to see if they're filled
				moves++;
				pieces[loc].pos = loc;
				positions.push_back(pieces[loc]);
			}
		}
	}
	return moves;
}