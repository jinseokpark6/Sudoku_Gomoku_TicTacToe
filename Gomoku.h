/*

Authors: Jin Seok Park (420430), Jihyun Min (420023)


*/
#ifndef GOMOKU_H
#define GOMOKU_H

#include "GameBase.h"
#include <iostream>
#include <vector>
using namespace std;


class Gomoku : public GameBase {

	friend ostream & operator << (ostream &, const Gomoku &);

public:

	int boardSize; //board dimension
	int bufferSize; //board with buffer dimension
	int connectNum; //number of pieces that should be connected

	void checkSavedGame(int, int);

	//constructors
	Gomoku();
	Gomoku(int);
	Gomoku(int, int);

	//virtual functions
	virtual void print();
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
	virtual int moveCount();

	bool is_valid(unsigned int, unsigned int);
	int keep_turning(unsigned int, unsigned int, unsigned int, string, string);
	bool winner(unsigned int, unsigned int);

	int numSpots;
	vector<int> whereEmpty();

};

ostream & operator << (ostream &, const Gomoku &);


#endif