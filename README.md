# Sudoku_Gomoku_TicTacToe
Created Sudoku, Gomoku, TicTacToe games with C++


========================================================================
    CONSOLE APPLICATION : Project Overview
========================================================================
Jin Hoon Jung 406120
Jin Seok Park 420430
Jihyun Min 420023


Lab4.cpp
    This is the main application source file.
Sudoku.cpp
	Main source file for Sudoku
Sudoku.h
	HEader file for Sudoku
TicTacToe.cpp
	Main source file for TicTacToe
TicTacToe.h
	Header file for TicTacToe
Gomoku.cpp
	Main source file for Gomoku
Gomoku.h
	Header file for Gomoku
GameBase.cpp
	Main source file for GameBase
GameBase.h
	Header file for GameBase


/////////////////////////////////////////////////////////////////////////////

For saving and restoring a game, we implemented a vector of game_piece into a
method that gets called after every turn in each of the respective games. For
example, in Sudoku, we added the game_piece into a vector in the is_valid
method so that every time a piece is added to the map, the piece gets added
to the vector as well. At any point, should the player quit the game, the vector
has the most vector. If the user chooses to save the game, then the ofstream
writes the position and the appropriate piece display (X, O for TicTacToe, numbers for Sudoku, and
B, W for Gomoku). The position and pieces are on separate lines, so when
we read the saved file, we use a while loop for getline and then call getline again
inside the while loop to get both pieces of data together. If the user does not save
the game, NO DATA is written into the file, so at the start of every game, we make sure
that the first line says the game name (sudoku, tictactoe, gomoku) rather than "NO DATA" or
"COMPLETE". We used .compare to compare strings. For example, for a midgame tictactoe,
it says:

tictactoe
13
X
14
O

As mentioned in the ReadMe for Labs 2 and 3, we used a one-dimensional array instead
of a vector. That means at position 13 of the array, the game_piece has a value of X
and at 14, O. We used shallow copy construction throug the use of shared_pointers , as it 
specifies in the lab instructions but, we did not optimize the use of them. We mainly used 
the shared pointer to redirect the gamebase class to the a specific game of the user's choosing. 
Because we only instantiate the GameBase Class once, for each game, we do not need a copy constructor 
and because we control that constructor with a shared pointer, we can automatically reference 
that class without using a move constructor/ assignment. 

By using a 1-D array, we had to calculate the positions and use a nested for loop
for printing/ locating pieces on the board. This implementation made checking the
winning conditions for Sudoku quite tedious, if extremely detailed. At every turn,
we checked to see that the input value (third number) was unique to the row, column,
and the surrounding 3 by 3 square. We also calculate to see the number of empty spots
after every turn by counting the number of "0"s on the board. If there are no 0s, then
we know that the player has finished playing. We check if the player has won only if
the number of empty spots are zero by running three helper methods. Like after every turn,
these helper methods check that each 1-9 number is used only once in every row/ column/ square.
We considered checking the winning condition after every move like we did in Gomoku and TicTacToe;
however, Sudoku is a more challenging game that requires some thought and allows room for error.
To account for the possibility that the player wants to change the position of a number, we
check if the input violatese any of the three conditions above, and if so, can choose to overwrite.
This means that until there are no empty spots, the values in each row/ column/ square may not 
necessarily be unique. Just like Sudoku on paper, we allow the player to "erase". Since we allow
the player to effectively revise their previous move, we must check the uniqueness condition again
at the end. Also, another benefit of allowing the user to overwrite the existing value is that
we can more easily verify if the player has won or lost at the end. We felt that expecting the user
to play a perfect game with no mistakes for Sudoku was a bit unreasonable. If the user does not
want to overwrite the value, then she can just type N and enter new coordinates as well.

We also implemented a different counter method for Sudoku. The number of moves no longer equals
the number of pieces on the board, since Sudoku is always filled with digits between 0 and 9. Thus,
we added to a variable every time a player writes or overwrites on the board; this variable is the
number that gets printed if the user quits before the game is complete.

/////////////////////////////////////////////////////////////////////////////

To test the games, we ran each game to see if it saved the appropriate lines when
a player won or quit without saving. All three games saved the correct values, and
we ensured that the game loaded properly even if the player quit midgame. To see if
Sudoku worked, we created a sudoku1 file with an almost-filled board. We found a
website that generates a correct combination given that we fill some of the spots.
Using the file available on the lab instructions, we prefilled all the other spots.
We left one spot empty and then typed in the answer. The correct answer printed
that you won while an incorrect answer said that you lost. Some of the combinations
that we tried were typing "sweljwle" to make sure it did not work, values that exceeded
the boundary, and incorrectly formatted numbers (like 522 or 2 3 1).

Because we did the extra credit for lab 3, we had an issue loading Gomoku games with
dimensions that were different than the saved values. For Gomoku, if the user saved a game with dimensions
 different from the default game, we allow the user to quit by ctrl+c. If the player wants to overwrite the existing game
file, she just has to continue playing. These instructions are clearly available at the
start so the player will never mistakenly overwrite her existing game. (We didn't want to delete the
extra credit feature.)
