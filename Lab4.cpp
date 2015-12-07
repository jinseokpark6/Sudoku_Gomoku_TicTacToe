// Lab4.cpp : Defines the entry point for the console application.
//

/*

Authors: Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120



*/


#include "stdafx.h"

#include <iostream>
#include <memory>

#include "GameBase.h"
#include "TicTacToe.h"
#include "Gomoku.h"
#include "Sudoku.h"


#define nt 19
#define tw 20
#define to 21
#define tt 22
#define tth 23
#define tf 24


int main(int argc, char* argv[])
{

	try {

		GameBase::argCheck(argc, argv);
		shared_ptr<GameBase> pointer = GameBase::instance();
		
		if (pointer == nullptr) {
			return nullPtr;
		}
		else {
			pointer->play();
		}
	}

	catch (int n) {
		if (n == nt) {
			cout << "The shared pointer is null" << endl;
			return nullPtr;
		}
		else if (n == tw) {
			cout << "Shared Pointer already initialized!" << endl;
			return ptrExists;
		}
		else if (n == to) {
			return usageMessage(argv[programName]);
		}
		else if (n == tt) {
			cout << "The new board size should be greater than 5!" << endl;
			return numRange;
		}
		else if (n == tth) {
			cout << "The new board size should be greater than 1 and greater than the default connect size!" << endl;
			return numRange;
		}
		else if (n == tf) {
			return usageMessage(argv[programName]);
		}
	}
	catch (status s) {
		return s;
	}

	catch (bad_alloc & ba) {
		cerr << "bad_alloc caught " << ba.what() << '\n';
	}

	catch (...) {
		cout << "Unknown error...Restarting game" << endl;
	}


	return success;
}





