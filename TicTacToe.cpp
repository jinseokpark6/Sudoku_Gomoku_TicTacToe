/*

Authors: Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120



*/
#include "stdafx.h"
#include "TicTacToe.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;


//TicTacToe constructor
TicTacToe::TicTacToe() {

	TicTacToe::alternate = 0;

	ifstream getGame("tictactoe");
	string line;

	p1 = 0;
	p2 = 0;

	pieces.resize(ticSize * ticSize);

	for (int i = ticSize - 1; i >= 0; i--) {
		for (int j = 0; j < ticSize; j++) {
			int location = (ticSize*i) + j;
			//label axis
			if (i == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(j);
			}
			else if (j == 0) {
				pieces[location].letter = border;
				pieces[location].name = "border";
				pieces[location].display = to_string(i);
			}
			//if not axes, intialize game_piece in array pieces
			else {
				pieces[location] = game_piece();
			}
		}
	}


	if (getGame.is_open()) {
		string firstline;
		getline(getGame, firstline);

		//check the first line of input file to see what data is available
		if ((firstline.compare("NO DATA") != 0 && firstline.compare("COMPLETE") != 0) || firstline.compare("tictactoe") == 0) {
			while (getline(getGame, line)) {
				string letter;
				getline(getGame, letter);
				if (letter.compare("X") == 0) {
					pieces[stoi(line)] = game_piece(exes, "X", "X", stoi(line));
					p1++;
				}
				else if (letter.compare("O") == 0) {
					pieces[stoi(line)] = game_piece(ohs, "O", "O", stoi(line));
					p2++;
				}
			}
			getGame.close();
		}
	}
	//print board before game
	print();

}

//draws board
ostream & operator << (ostream & o, const TicTacToe &ttt) {
	TicTacToe frame = ttt;

	for (int i = ticSize - 1; i >= 0; i--) {
		for (int j = 0; j < ticSize; j++) {
			int location = (ticSize*i) + j;

			o << setw(ttt.longestStr) << frame.pieces[location].display;

		}
		o << "\n";
	}

	o << endl;
	return o;
}

void TicTacToe::print() {
	cout << *this << endl;
}


//true if 3-Xs or Os is in a vertical, horizontal, or diagonal line; otherwise returns false
bool TicTacToe::done() {
	//8 possible winning combinations, 4 of which involve center piece
	//checks diagonal cases
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < ticSpots; j++) {
			int loc = ticSize + i*ticSize + j + 1;
			if (loc == 6) {
				if (pieces[loc].display == "X" && pieces[loc + 6].display == "X" && pieces[loc + 12].display == "X") {
					return true;
				}
				else if (pieces[loc].display == "O" && pieces[loc + 6].display == "O" && pieces[loc + 12].display == "O") {
					return true;
				}
			}
			else if (loc == 8) {
				if (pieces[loc].display == "X" && pieces[loc + 4].display == "X" && pieces[loc + 8].display == "X") {
					return true;
				}
				else if (pieces[loc].display == "O" && pieces[loc + 4].display == "O" && pieces[loc + 8].display == "O") {
					return true;
				}
			}
		}
	}

	//checks horizontal win cases
	//looks at spots 6, 11, 16
	for (int i = 0; i < ticSpots; i++) {
		for (int j = 0; j < 1; j++) {
			int loc = ticSize + i*ticSize + j + 1;
			if (pieces[loc].display == "X") {
				if (pieces[loc + 1].display == "X" && pieces[loc + 2].display == "X") {
					return true;
				}
			}
			else if (pieces[loc].display == "O") {
				if (pieces[loc + 1].display == "O" && pieces[loc + 2].display == "O") {
					return true;
				}
			}
		}
	}

	// checks vertical win cases
	//looks at spots 6, 7, 8
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < ticSpots; j++) {
			int loc = ticSize + i*ticSize + j + 1;
			if (pieces[loc].display == "X") {
				if (pieces[loc + 5].display == "X" && pieces[loc + 10].display == "X") {
					return true;
				}
			}
			else if (pieces[loc].display == "O") {
				if (pieces[loc + 5].display == "O" && pieces[loc + 10].display == "O") {
					return true;
				}
			}
		}
	}

	return false;
}

bool TicTacToe::stalemate() {

	//if game is done, then no draw
	if (done()) {
		return false;
	}

	bool taken = false;
	int allTaken = 0;

	for (int i = 0; i < ticSpots; i++) {
		for (int j = 0; j < ticSpots; j++) {
			int loc = ticSize + i*ticSize + j + 1;
			if (pieces[loc].display == "X" || pieces[loc].display == "O") {
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
	if (allTaken == 9) {
		return true;
	}
	//if entire board is not full and no one has won yet, no draw
	else {
		return false;
	}

}

//same as draw method, but returns int of total moves


int TicTacToe::turn() {
	//assign players to different int values
	//if alternate%2 == 0, then player O and if == 1, then player X
	string playerO = "Player O: ";
	string playerX = "Player X: ";

	if (p1 > p2) {
		alternate++;
	}


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
			//go into helper method to continue game
			int going = keep_turning(h, v, alternate, playerO, playerX);

			//check what going returns
			if (going == winO) {
				return winO;
			}
			else if (going == winX) {
				return winX;
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

		if (going == winO) {
			return winO;
		}
		else if (going == winX) {
			return winX;
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

//helper method for alternating turns
int TicTacToe::keep_turning(unsigned int hh, unsigned int vv, unsigned int alternate, string playerO, string playerX) {
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

			int loc = ticSize*v + h;
			pieces[loc] = game_piece(ohs, "O", "O", loc);
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
				return winO;
			}
			else if (stalemate()) {
				return draww;
			}
			else {
				cout << "\nPlayer X's turn" << endl;
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
			int loc = ticSize*v + h;
			pieces[loc] = game_piece(exes, "X", "X", loc);
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
				return winX;
			}
			else if (stalemate()) {
				return draww;
			}
			else {
				cout << "\nPlayer O's turn" << endl;
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

bool TicTacToe::is_valid(unsigned int horiz, unsigned int vert) {
	int loc = ticSize*vert + horiz;

	//checking out of bounds condition
	if (loc < 6 || loc > 18) {
		return false;
	}

	//if it's not an empty space or has X or O, then spot is already taken
	if (pieces[loc].display != " " || pieces[loc].display == "X" || pieces[loc].display == "O") {
		return false;
	}
	else {
		//empty spot - can be taken
		return true;
	}
}


int TicTacToe::moveCount() {
	int moves = 0;
	for (int i = 0; i < ticSpots; i++) {
		for (int j = 0; j < ticSpots; j++) {
			int loc = ticSize + i*ticSize + j + 1;
			if (pieces[loc].display == "X" || pieces[loc].display == "O") {
				//checks all pieces to see if they're filled
				moves++;
				pieces[loc].pos = loc;
				positions.push_back(pieces[loc]);
			}
		}
	}
	return moves;
}