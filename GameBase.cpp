/*

Authors: Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120



*/
#include "stdafx.h"
#include "GameBase.h"
#include "TicTacToe.h"
#include "Gomoku.h"
#include "Sudoku.h"
using namespace std;

#define nn 19

//game_piece constructor
game_piece::game_piece()
: letter(exes), name(""), display(" ") {}

//game_piece mutator
game_piece::game_piece(piece_letter letter, string name, string display, int pos)
: letter(letter), name(name), display(display) {}


int GameBase::whichGame = 0;
int p1 = 0;
int p2 = 0;
int gDim = 21;
int gCount = 5;
int sdkCount;

shared_ptr<GameBase> GameBase::sharedPointer = nullptr;
vector<game_piece> GameBase::positions;

shared_ptr<GameBase> GameBase::instance()
{
	if (sharedPointer != nullptr) return sharedPointer;
	else throw nn;
}

int usageMessage(char * name)
{
	cout << "Usage: " << name << " TicTacToe or " << name << " Gomoku" << " or " << name << " Sudoku" << endl;
	return argError;
}

void GameBase::checkDisplayLength() {

	for (game_piece p : pieces) {
		if (p.display.length() > GameBase::longestStr) {
			GameBase::longestStr = p.display.length();
		}
	}
}

void GameBase::argCheck(int l, char* argName[]) {
	if (sharedPointer == nullptr) {
		if (l == defaultNum) {
			// checks to see if the second parameter is TicTacToe
			if (strcmp(argName[gameName], "TicTacToe") == 0) {
				whichGame = TTT;
				GameBase::sharedPointer = make_shared<TicTacToe>();
			}
			// checks to see if the second parameter is Gomoku
			else if (strcmp(argName[gameName], "Gomoku") == 0) {
				whichGame = GMK;
				GameBase::sharedPointer = make_shared<Gomoku>();
			}
			else if (strcmp(argName[gameName], "Sudoku") == 0) {
				whichGame = SDK;
				GameBase::sharedPointer = make_shared<Sudoku>();
			}
			else {
				throw t1;
			}
		}

		else if (l == newBoard){
			int a = stoi(argName[gomNewBoard]);
			// check if input is valid: if a is less than the default of connect value, which is 5, return die
			if (a >= 5) {
				whichGame = GMK;
				GameBase::sharedPointer = make_shared<Gomoku>(a);
			}
			else {
				throw t2;
			}
		}
		else if (l == newMatch){
			int a = stoi(argName[gomNewBoard]);
			int b = stoi(argName[gomNewMatch]);
			// check if input is valid: if a is less than 1 or the dimension of the board is smaller than the connect value, return die
			if (a >= 1 && a >= b) {
				whichGame = GMK;
				sharedPointer = make_shared<Gomoku>(a, b);
			}
			else {
				throw t3;
			}
		}
		else {
			throw t4;
		}
	}
	else {
		throw twenty;
	}
}

//prompt method for Sudoku only
void GameBase::prompt(unsigned int & horiz, unsigned int & vert, unsigned int & input) {

	string s1;

	int first;
	int second;
	int third; 

	cout << "Enter coordinates and input <x,y,z>  or type <quit>" << endl;
	getline(cin, s1);


	bool comma = false; 
	int digits = 0;

	if (s1.compare("quit") == 0) {
		throw quit;
	}
	else {

		//check for valid input (presence of comma)
		for (unsigned int i = 0; i < s1.length(); i++) {
			if (s1[i] == ',') {
				s1[i] = ' ';
				digits++;
				comma = true;
			}
		}

		if (comma) {

			//need to convert ascii back to int
		
			if (digits == 2 && s1.length() == 5) {
				first = s1[0] - '0';
				second = s1[2] - '0';
				third = s1[4] - '0';
			}

			else {
				cout << "Invalid format: x,y,z between 0 and 10" << endl;
				throw wrongInput;
			}

			//extract to first then second and then find range

			if (whichGame == SDK) {
				if ((first <= 0) || (first >= 10) || (second <= 0) || (second >= 10) || (third <= 0) || (third >= 10)) {
					cout << "Please enter valid coordinates between 0 and 10" << endl;
					h = first;
					v = second;
					p = third;
					throw wrongInput;
				}
				else {
					h = first;
					v = second;
					p = third;
					throw promptComplete;
				}
			}
			
		}
		else {
			cout << "Invalid format: x,y,z" << endl;
			throw wrongInput;
		}
	}
}

//for Gomoku and TicTacToe
int GameBase::prompt(unsigned int & horiz, unsigned int & vert) {
	string s1;
	string s2;

	int first;
	int second;

	cout << "Enter coordinate <x,y> or type <quit>" << endl;
	getline(cin, s1);


	bool comma = false;
	int digits = 0;

	if (s1.compare("quit") == 0) {
		return quit;
	}
	else {

		//check for valid input (presence of comma)
		for (unsigned int i = 0; i < s1.length(); i++) {
			if (s1[i] == ',') {
				s1[i] = ' ';
				digits = i;
				comma = true;
			}
		}

		if (comma) {
			char firstToken;
			char secondToken;

			//need to convert ascii back to int
			if (digits == 1 && s1.length() == 3) {
				firstToken = s1[0];
				secondToken = s1[2];
				first = firstToken - '0';
				second = secondToken - '0';
			}
			else if (digits == 1 && s1.length() == 4) {
				firstToken = s1[0];
				first = firstToken - '0';
				second = (s1[2] - '0') * 10 + (s1[3] - '0');
			}
			else if (digits == 2 && s1.length() == 4) {
				first = (s1[0] - '0') * 10 + (s1[1] - '0');
				secondToken = s1[3];
				second = secondToken - '0';
			}
			else if (digits == 2 && s1.length() == 5) {
				first = (s1[0] - '0') * 10 + (s1[1] - '0');
				second = (s1[3] - '0') * 10 + (s1[4] - '0');
			}
			else {
				return wrongInput;
			}

			//extract to first then second and then find range

			if (whichGame == TTT) {
				if ((first <= 0) || (first >= 4) || (second <= 0) || (second >= 4)) {
					cout << "Please enter valid coordinates between 0 and 4" << endl;
					h = first;
					v = second;
					return wrongInput;
				}
				else {
					h = first;
					v = second;
					return promptComplete;
				}
			}
			if (whichGame == GMK) {
				if ((first <= 0) || (first >= 20) || (second <= 0) || (second >= 20)) {
					cout << "Please enter valid coordinates between 0 and 20" << endl;
					h = first;
					v = second;
					return wrongInput;
				}
				else {
					h = first;
					v = second;

					return promptComplete;
				}
			}
		}
		else {
			cout << "Invalid format: x,y" << endl;
			return wrongInput;
		}
	}

	return wrongInput;
}

int GameBase::save() {
	string s1;
	string s2;

	cout << "Would you like to save the game before you quit? Y or N" << endl;

	getline(cin, s1);


	if (s1.compare("N") == 0) {
		return noSave;
	}
	else if (s1.compare("Y") == 0) {
		return yeah;
	}
	else {
		cout << "Please type Y or N" << endl;
		save();
	}

	return pokeball;
}

int GameBase::saidYes() {
	ofstream myGame;

	//depending on game, get correct vector of game_pieces to save
	if (whichGame == TTT) {
		myGame.open("tictactoe");
		myGame << "tictactoe" << endl;
		for (auto i = positions.begin(); i != positions.end(); ++i) {
			myGame << i->pos << '\n' << i->display << endl;
		}
		myGame.close();

	}

	else if (whichGame == GMK) {
		myGame.open("gomoku");
		myGame << "gomoku" << endl;
		myGame << gDim << '\n' << gCount << endl;

		for (auto i = positions.begin(); i != positions.end(); ++i) {
			myGame << i->pos << '\n' << i->display << endl;
		}
		myGame.close();
	}
	
	else if (whichGame == SDK) {
		myGame.open("sudoku");
		myGame << "sudoku" << endl;

		for (auto i = positions.begin(); i != positions.end(); ++i) {
			myGame << i->pos << '\n' << i->display << endl;
		}
		myGame.close();
	} 

	throw quit;
	return pokeball;
}

int GameBase::saidNo() {
	//if user doesn't save game, say NO DATA
	ofstream myGame;

	if (whichGame == TTT) {
		myGame.open("tictactoe");
		myGame << "NO DATA" << endl;
		myGame.close();
	}

	else if (whichGame == GMK) {
		myGame.open("gomoku");
		myGame << "NO DATA" << endl;
		myGame.close();
	}
	else if (whichGame == SDK) {
		myGame.open("sudoku");
		myGame << "NO DATA" << endl;
		myGame.close();
	}

	throw quit;
	return pokeball;
}

int GameBase::completeGame() {
	ofstream myGame;

	//if game is complete, then save COMPLETE
	if (whichGame == TTT) {
		myGame.open("tictactoe");
		if (myGame.is_open()) {
			myGame << "COMPLETE" << endl;
			myGame.close();
		}
		else {
			cout << "tictactoe could not be opened. Trying again..." << endl;
			myGame.close();
			completeGame();
		}

	}
	else if(whichGame == GMK) {
		myGame.open("gomoku");
		if (myGame.is_open()) {
			myGame << "COMPLETE" << endl;
			myGame.close();
		}
		else {
			cout << "gomoku could not be opened. Trying again... " << endl;
			myGame.close();
			completeGame();
		}

	}
	else if (whichGame == SDK) {
		myGame.open("sudoku");
		if (myGame.is_open()) {
			myGame << "COMPLETE" << endl;
			myGame.close();
		}
		else {
			cout << "sudoku could not be opened. Trying again..." << endl;
			myGame.close();
			completeGame();
		}
	}

	return pokeball;
}

int GameBase::play() {
	alternate = 0;
	int playing = turn();
	int move = moveCount();

	if (playing == quit) {
		int askSave = save();

		if (askSave == yeah)
		{
			//save the game
			int y = saidYes();
			if (whichGame != SDK) {
				cout << "You quit! Total moves: " << move << endl;
			}
			else{
				cout << "You quit! Total moves: " << sdkCount << endl;
			}
		}
		else {
			int n = saidNo();
			if (whichGame != SDK) {
				cout << "You quit! Total moves: " << move << endl;
			}
			else if (whichGame == SDK) {
				int moveC = 81-moveCount();
				cout << "You quit! Total moves: " << sdkCount << endl;
			}
			cout << "BOOM SHAKALAKA" << endl;
		}
		throw quit;
	}
	else {
		//overwrite appropriate game txt file when game is completed
		completeGame();

		if (playing == winX) {
			cout << "X won! Total moves: " << move << endl;
			throw winX;
		}
		else if (playing == winO) {
			cout << "O won! Total moves: " << move << endl;
			throw winO;
		}
		else if (playing == sdkDone) {
			cout << "You won!" << endl;
			throw sdkDone;
		}
		else if (playing == lose) {
			cout << "You lost!" << endl;
			throw lose;
		}
		else if (playing == winB) {
			cout << "B won! Total moves: " << move << endl;
			throw winB;
		}
		else if (playing == winW) {
			cout << "W won! Total moves: " << move << endl;
			throw winW;
		}
		else if (playing == draww) {
			int move = moveCount();
			cout << "DRAW! Total moves: " << move << endl;
			throw draww;
		}
		else if (playing == endOfGame) {
			//should never reach this point
			cout << "Uh oh. Something went wrong" << endl;
			throw endOfGame;
		}

	}
	return pokeball;
}