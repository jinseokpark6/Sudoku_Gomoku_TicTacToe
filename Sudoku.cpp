/*

Authors Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120

*/
#include "stdafx.h"

#include <vector>
#include "Sudoku.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int getLocation(int h, int w) {
	return h * 11 + w;
}

// Default Initialization
Sudoku::Sudoku() {
	
	bufferSize = 11;
	boardSize = 9;

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
				pieces[location].display = "0"; //0 fills empty spaces. 
			}
		}
	}

	
	//check the first line of input file to see what data is available
	
	ifstream getGame("sudoku");
	string line;

	if (getGame.is_open()) {
		string firstline;
		getline(getGame, firstline);

		//saved game exists, so load that data
		if ((firstline.compare("NO DATA") != 0 && firstline.compare("COMPLETE") != 0) || firstline.compare("sudoku") == 0) {
			string location;
			while (getline(getGame, location)) {
				string number;
				getline(getGame, number);
				pieces[stoi(location)].display = number;
			}
		}
		else {
			ifstream getDefault("sudoku0");
			string location;
			while (getline(getDefault, location)) {
				string number;
				getline(getDefault, number);
				pieces[stoi(location)].display = number;
			}
		}
	}
	else {
		ifstream getDefault("sudoku0");
		string location;
		while (getline(getDefault, location)) {
			string number;
			getline(getDefault, number);
			pieces[stoi(location)].display = number;
		}
	}

	//print empty board before starting game
	print();
}


void Sudoku::print() {
	cout << *this << endl;
}

//draws board
ostream & operator << (ostream & o, const Sudoku &ggg) {
	Sudoku frame = ggg;
	for (int i = ggg.bufferSize - 1; i >= 0; i--) {
		for (int j = 0; j < ggg.bufferSize; j++) {
			int location = (ggg.bufferSize*i) + j;
			o << setw(2) << frame.pieces[location].display;
		}
		o << "\n";
	}

	o << endl;
	return o;
}

bool Sudoku::checkUnique(int horiz, int vert, int input) {

	//overall checker to check that value is unique in set of square, row, and col
	
	//everything must return true
	if (checkColumn(vert, input) && checkRow(horiz, input) && checkSquare(horiz, vert, input)){
		return true;
	}

	return false;

}

bool Sudoku::checkColumnSum(int horiz){
	//set must be lenght 9 since it only holds unique values

	set<int> numList;

	for (int i = 1; i < 10; i++) {

		int startLocation = (bufferSize)*i + horiz;
		numList.insert(stoi(pieces[startLocation].display));
	}

	if (numList.size() == 9) {
		return true;
	}
	return false;
}

bool Sudoku::checkRowSum(int vert){
	//same as checkColumnSum but for rows
	set<int> numList;

	for (int i = 1; i < 10; i++) {

		int startLocation = (bufferSize)*vert + i;
		numList.insert(stoi(pieces[startLocation].display));
	}

	if (numList.size() == 9) {

		return true;
	}

	return false;

}

bool Sudoku::checkSquareSum(){
	//checks surrounding 3 x 3 square
	for (int a = 1; a < 4; a++){
		for (int b = 1; b < 4; b++){

			set<int> numList;

			for (int i = 1; i < 4; i++) {
				for (int j = 1; j < 4; j++) {
					int startLocation = (bufferSize)*(i + 3 * a) + (j + 3 * b);

					if (pieces[startLocation].display.compare("0") == 0) {
						return false;
					}

					numList.insert(stoi(pieces[startLocation].display));

					return true;
				}
			}
		}
	}

	return false;

}

bool Sudoku::checkRow(int horiz, int input){
	//checks to see if input value already exists in the row
	for (int i = 1; i < 10; i++) {
		int loc = (bufferSize)*i + horiz;

		if (stoi(pieces[loc].display) == input) {
			return false;
		}
	}
	return true;
}

bool Sudoku::checkColumn(int vert, int input){
	//checks to see if input value already exists in the column
	for (int i = 1; i < 10; i++) {
		int loc = (bufferSize)*vert + i;

		if (stoi(pieces[loc].display) == input) {
			return false;
		}
	}
	return true;
}

bool Sudoku::checkSquare(int horiz, int vert, int input){
	//checks to see if input value already exists in the 3 x 3 square
	int vertPos = vert - (vert - 1) % 3;
	int horPos = horiz - (horiz - 1) % 3;

	for (int i = vertPos; i < vertPos + 3; i++) {
		for (int j = horPos; j < horPos + 3; j++) {
			int location = (bufferSize)*i + j;
			if (stoi(pieces[location].display) == input) {
				return false;
			}
		}
	}
	return true;


}


bool Sudoku::done() {
	//checks to see if you've won

	for (int i = 1; i < 10; i++) {
		if (!Sudoku::checkRowSum(i)){
			return false;
		}
	}

	for (int j = 1; j < 10; j++) {
		if (!Sudoku::checkColumnSum(j)){
			return false;
		}
	}

	if (!Sudoku::checkSquareSum()){
		return false;
	}
	
	//if all of the above conditions do not return true, then you've won
	return true; 
}

bool Sudoku::is_valid(unsigned int horiz, unsigned int vert, unsigned int input) {
	//checks if input spot can be taken

	int loc = (bufferSize)*vert + horiz;

	//out of bounds
	if (loc < bufferSize + 1 || loc > bufferSize * bufferSize - 1) {
		return false;
	}

	//if the input is equal to what is already displayed
	else if (stoi(pieces[loc].display) == input) {
		return false;
	}

	//can overwrite existing number
	else if (checkUnique(horiz, vert, input) == false) {
		cout << "Not a unique number in this row/column combination. Overwrite? Type Y or N" << endl;
		string answer;
		getline(cin, answer);
		if (answer.compare("Y") == 0) {
			return true;
		}
		else if(answer.compare("N") == 0) {
			return false;
		}
		else {
			cout << "Please type Y or N" << endl;
			is_valid(horiz, vert, input);
		}

		return false;
	}

	else {
		//any other form
		return true;
	}

}


int Sudoku::turn() {

	string playerO = "Player O: ";

	unsigned int horiz, vert, input;

	try {
		//start game by prompting user
		prompt(horiz, vert, input);
	}

	catch (status a) {

		//prompted user, but they quit

		if (a == quit) {
			return quit;
		}

		//if player didn't quit, but prompt returned wrong input
		else if (a == wrongInput) {

			try {
				prompt(horiz, vert, input);
			}
			catch (status b) {
				if (b == wrongInput) {

					//call turn() until valid input given or quit
					return turn();
				}
				else if (b == promptComplete) {
					alternate++;

					//go into helper method to continue game
					int going = keep_turning(h, v, p, alternate, playerO);

					//check what going returns
					if (going == sdkDone) {
						return sdkDone;
					}
					else if (going == quit) {
						return quit;
					}
					else if (going == lose) {
						return lose;
					}
				}
				else if (b == quit) {
					return quit;
				}
			}
		}
		//everything is valid so continue game
		else if (a == promptComplete) {
			alternate++;
			//go into helper method to continue game
			int going = keep_turning(h, v, p, alternate, playerO);

			if (going == sdkDone) {
				return sdkDone;
			}
			else if (going == lose) {
				return lose;
			}
			else if (going == quit) {
				return quit;
			}
		}

	}
	catch (...) {
		cout << " Caught something.. please quit and restart game " << endl;
	}
	return pokeball;
}

int Sudoku::keep_turning(unsigned int hh, unsigned int vv, unsigned int pp, unsigned int alternate, string playerO) {
	//check if the spot is already taken
	if (is_valid(h, v, p) == false) {
		try {
			prompt(hh, vv, pp);
		}
		catch (status e) {
			if (e == quit){
				return quit;
			}
			else if (e == wrongInput) {
				try {
					prompt(hh, vv, pp);
				} 
				catch (status ee) {
					if (ee == quit) {
						return quit;
					}

				}
			}
		}

		//at any point, if user quits, the game should exit out
		
		return keep_turning(hh, vv, pp, alternate, playerO);
	}

	//found empty spot/different input, continue
	else {
			int loc = bufferSize*v + h;
			pieces[loc] = game_piece(sudoku, "numb", to_string(p), loc);
			if (pieces[loc].display.length() > longestStr) {
				longestStr = pieces[loc].display.length();
			}

			//update board
			print();

			playerO += to_string(h) + ", " + to_string(v) + ", " + to_string(p) + "; ";
			cout << playerO << endl;

			sdkCount++;

			//check game conditions after every move
			int emptySpots = Sudoku::moveCount();

			if (emptySpots == 0 && done()) {
				return sdkDone;
			}
			//if the whole board is full and you haven't won, then you lose
			else if (emptySpots == 0 && !done()) {
				return lose;
			}

			else {
				unsigned int a, b, c;
				//no one has won and the game is not a draw
				try {
					prompt(a, b, c);
				}
				catch (status f) {
					if (f == quit){
						return quit;
					}
					else if (f == wrongInput) {
						try {
							prompt(a, b, c);
						}
						catch (status g) {
							if (g == quit) {
								return quit;
							}
						}
						return keep_turning(a, b, c, alternate, playerO);
					}
					else if (f == promptComplete) {
						return keep_turning(a, b, c, alternate, playerO);
					}
				}
			}

		}
	
	return endOfGame;
}

int Sudoku::moveCount() {
	int moves = 0;
	for (int i = 1; i <= boardSize; i++) {
		for (int j = 1; j <= boardSize; j++) {
			int loc = i*(bufferSize)+j;
			if (stoi(pieces[loc].display) == 0) {
				//checks all pieces to see if they're filled
				//should not have any 0s to win
				moves++;
			}
			else {
				//for save game, push into vector
				pieces[loc].pos = loc;
				positions.push_back(pieces[loc]);
			}
		}
	}
	return moves;
}

//can never tie, so always false
bool Sudoku::stalemate() {
	return false;
}