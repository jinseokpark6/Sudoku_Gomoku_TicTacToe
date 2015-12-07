/*

Authors: Jin Seok Park (420430), Jihyun Min (420023), Jin Hoon Jung 406120



*/
#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <string>
#include <iterator>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

#define twenty 20
#define nn 19
#define t1 21
#define t2 22
#define t3 23
#define t4 24

using namespace std;

enum systemArguments { programName, gameName, gomNewBoard, gomNewMatch, argError };
enum numArguments { defaultNum = 2, newBoard = 3, newMatch = 4 };
enum status { success, notStarted, sdkDone, winX, winO, winB, winW, draww, quit, lose, promptComplete, endOfGame, inputError, wrongInput, pokeball };
enum BoardDim { ticSize = 5, ticSpots = 3 };
enum gameType { TTT, GMK, SDK };
enum errorArguments { argFormat, numRange };
enum save { yeah, noSave };
enum check { nullPtr, ptrExists };

int usageMessage(char * name);

enum piece_letter { ohs, exes, border, doubleYou, bee, sudoku };
piece_letter getLetter(string letter);



struct game_piece {
	game_piece();
	game_piece(piece_letter, string, string, int);
	piece_letter letter;
	string name;
	string display;
	int pos;
};


class GameBase {

public:
	static void argCheck(int, char*[]);
	int play();

	//used to store which game we are playing
	static int whichGame;

	static vector<game_piece> positions;

	//used to figure out which error returns from the argCheck method
	static int errorCase;
	static shared_ptr<GameBase> instance();



protected:
	vector <game_piece> pieces;
	int alternate = 0;
	int numTurns = 0;
	int sdkCount = 0;
	unsigned int h;
	unsigned int v;
	unsigned int p;

	unsigned int longestStr = 1;
	//virtual functions
	virtual void print() = 0;
	virtual bool stalemate() = 0;
	virtual int turn() = 0;
	int prompt(unsigned int &, unsigned int &);
	virtual void prompt(unsigned int &, unsigned int &, unsigned int &);
	//helper method for counting moves
	virtual int moveCount() = 0;

	void checkDisplayLength();

	static shared_ptr<GameBase> sharedPointer;

	int save();
	int saidYes();
	int saidNo();
	int completeGame();

	int p1;
	int p2;


	int gDim;
	int gCount;
};




#endif