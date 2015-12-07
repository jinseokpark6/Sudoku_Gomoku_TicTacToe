/*

Authors: Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120



*/
#ifndef SUDOKU_H
#define SUDOKU_H

#include "GameBase.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;



class Sudoku : public GameBase {

	friend ostream & operator << (ostream &, const Sudoku &);

public:

	int boardSize; //board dimension
	int bufferSize; //board with buffer dimension
	int connectNum; //number of pieces that should be connected
	int numSpots;

	//constructors
	Sudoku();

	//virtual functions
	virtual void print();
	virtual bool done();
	virtual int turn();
	virtual int moveCount();
	virtual bool stalemate();

	bool is_valid(unsigned int, unsigned int, unsigned int);
	// int keep_turning(unsigned int, unsigned int, unsigned int, string, string);
	bool winner(unsigned int, unsigned int);

	//helper function
	bool checkRow(int, int);
	bool checkColumn(int, int);
	bool checkSquare(int, int, int);
	bool checkUnique(int, int, int);

	bool checkRowSum(int);
	bool checkColumnSum(int);
	bool checkSquareSum();


	bool checkBoard();
	int keep_turning(unsigned int, unsigned int, unsigned int, unsigned int, string);


	vector<int> whereEmpty();

	int getLocation(int, int);

};

ostream & operator << (ostream &, const Sudoku &);


#endif