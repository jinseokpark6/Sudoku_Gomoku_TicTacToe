/*

Authors: Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120



*/
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>
#include <iterator>
#include <iostream>
#include "GameBase.h"

using namespace std;

class TicTacToe : public GameBase {

	friend ostream & operator << (ostream &, const TicTacToe &);
public:
	//constructors
	TicTacToe();

	//virtual functions
	virtual bool done();
	virtual int turn();
	virtual void print();
	virtual bool stalemate();
	virtual int moveCount();

	bool is_valid(unsigned int, unsigned int);
	int keep_turning(unsigned int, unsigned int, unsigned int, string, string);

	int numSpots;

};

ostream & operator << (ostream &, const TicTacToe &);


#endif