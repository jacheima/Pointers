#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

//Declaring my global constants

const char x = 'x';
const char o = 'o';
const char Empty = ' ';
const char tie = 't';
const char no_won = 'n';

//Declaring functions
void directions(); //tells players how to play
char YesNo(string question); //initalizes the yes/no questions that are asked to the players
int Number(string question, int high, int low = 0); //asks the player where they would like to move
char playerPieces(); //player moves
char opponent(char piece); //opponent moves
void showBoard(const vector<char>* const pBoard); //draws the board with the moves included
char winner(const vector<char>* const pBoard); //looks at board to see if anyone has won yet
bool isValid(const vector<char>* const pBoard, int move); //checks to see if the move is valid
int playerMove(const vector<char>* const pBoard, char player); // players piece is placed on the board
int computerMove(vector<char> board, char computer); //computers piece is placed on the board
void showWinner(char winner, char computer, char player); //show the winner


//the main function
int main()
{
	//declaring the move variable that holds where the player wants to move
	int move;
	//this is the number of space on the board
	const int boardSquares = 9;
	//a vector that holds the board spaces
	vector<char> board(boardSquares, Empty);

	//call the direction functions to tell the player how to play the game
	directions();

	//set the character to the function playerPieces()
	char player = playerPieces();
	//seting the computer to the players opponent
	char computer = opponent(player);
	//sets the turn to x since that is what the player places on the board
	char turn = x;

	//this calls the function that draws the board on the screen
	showBoard(&board);
	//while no one has won the game
	while (winner(&board) == no_won)
	{
		//if it is the players turn
		if (turn == player)
		{
			//set move to the players move choice
			move = playerMove(&board, player);
			//place a piece of the players at that space
			board[move] = player;
		}
		//if it is the computers turn
		else
		{
			//set move to the computers move choice
			move = computerMove(board, computer);
			//place one of their pieces on that space
			board[move] = computer;
		}
		//draw the updated board
		showBoard(&board);
		//set the turn to the player whose turn it is not
		turn = opponent(turn);
	}

	//if there is a winner announce it
	showWinner(winner(&board), computer, player);
	//exit the program
	return 0;

}

//Tells the player the directions they need to use to play the game
void directions()
{
	cout << "Welcome to Tic-Tac-Toe" << endl;
	cout << "In this game you will play against the computer" << endl << endl;

	cout << "To move, enter a number 0 through 8" << endl;
	cout << "The number coresponds to a space on the board as follows:" << endl << endl;

	cout << "     0 | 1 | 2 " << endl;
	cout << "     3 | 4 | 5 " << endl;
	cout << "     6 | 7 | 8 " << endl;

	cout << "The game will begin when you are ready" << endl << endl;

	system("pause");

	cout << endl << endl;
}
//this function ask the player yes/no questions and gets their response
char YesNo(string question)
{
	char response;
	//ask the question and get the response while the response is not yes or no
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}
//this function asks the player where they would like to move
int Number(string question, int high, int low)
{
	//number holds the number of the square they want to move to
	int number;
	//do this while the number is bigger than 9 or smaller than 0
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);

	return number;
}
//This function asks the player if they would like to go first. If yes, the player makes the first move. If no, then the computer goes first.
char playerPieces()
{
	//initialize the question to ask the player
	char askIfFirst = YesNo("Would you like to make the first move?");
	//if the player answers yes
	if (askIfFirst == 'y')
	{
		//tell them they can go first and set ther piece type
		cout << "You are autorized to make the first move" << endl;
		return x;
	}
	//if they say no
	else
	{
		//tell them that the computer will go first and set their piece type
		cout << "You have not been authorized to make the first move. The computer will go first." << endl;
		return o;
	}
}
//this function determines whose turn it is not. And sets the next turn by piece type
char opponent(char piece)
{
	//if the piece that was placed is x
	if (piece == x)
	{
		//set next piece to o
		return o;
	}
	//if the piece was placed is o
	else
	{
		//then set next piece to x
		return x;
	}
}

//draws the board for the player to see, with the space locations as pointers. 

void showBoard(const vector<char>* const pBoard)
{
	cout << "\n\t" << (*pBoard)[0] << " | " << (*pBoard)[1] << " | " << (*pBoard)[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << (*pBoard)[3] << " | " << (*pBoard)[4] << " | " << (*pBoard)[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << (*pBoard)[6] << " | " << (*pBoard)[7] << " | " << (*pBoard)[8];
	cout << "\n\n";
}

char winner(const vector<char>* const pBoard)
{
	//all possible ways to win
	const int waysToWin[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {2, 4, 7}, {3, 5, 8}, {0, 4, 8}, {2, 4, 6} };
	//the number of win conditions
	const int totalWinRows = 8;


	//Winning condition: If there is any rows that have all the same 3 values and are not empty
	//Then a winner can be declared
	for (int row = 0; row < totalWinRows; ++row)
	{
		if (((*pBoard)[waysToWin[row][0]] != Empty) &&
			((*pBoard)[waysToWin[row][0]] == (*pBoard)[waysToWin[row][1]]) &&
			((*pBoard)[waysToWin[row][1]] == (*pBoard)[waysToWin[row][2]]))
		{
			return (*pBoard)[waysToWin[row][0]];
		}
	}

	//if at this point nobody has won, we need to check to see if the player and the computer have tied
	if (count(pBoard->begin(), pBoard->end(), Empty) == 0)
	{
		return tie;
	}

	//because there is not a tie, the game is not over
	return no_won;
}
//This checks to see if the space is empty 
inline bool isValid(int move, const vector<char>* pBoard)
{
	return((*pBoard)[move] == Empty);
}
//This function asks the player to chose their next move and tells them if it is valid or not.
int playerMove(const vector<char>* const pBoard, char player)
{
	int move = Number("Where would you like to move?", (pBoard->size() - 1));
	while(!isValid(move, pBoard))
	{
		cout << "\n That square already has a piece in it. \n";
		move = Number("Where will you move?", (pBoard->size() - 1));
	}

	cout << "You have moved your piece";
	return move;
}
//The computer will move their piece
int computerMove(vector<char> board, char computer)
{
	//their move is set to 0 by default and will follow a particular model for moving
	unsigned int move = 0;
	bool found = false;

	//if the computer can win on the next move, then the computer will make that move
	while (!found && move < board.size())
	{
		//if the move is valid
		if (isValid(move, &board))
		{
			//try move
			board[move] = computer;
			//test for winner
			found = winner(&board) == computer;
			//undo move
			board[move] = Empty;
		}
		if (!found)
		{
			move++;
		}
	}

	//if the opponent can win on the next move, then it will make a move against it
	if (!found)
	{
		move = 0;
		char player = opponent(computer);

		while (!found && move < board.size())
		{
			if (isValid(move, &board))
			{
				//try move
				board[move] = player;
				//test for winner
				found = winner(&board) == player;
				//undo move
				board[move] = Empty;

			}

			if (!found)
			{
				move++;
			}
		}
	}

	//if nothing else find the best move to make
	if (!found)
	{
		move = 0;
		unsigned int i = 0;

		const int bestMove[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

		//pick the best square
		while (!found && i < board.size())
		{
			move = bestMove[i];
			if (isValid(move, &board))
			{
				found = true;
			}
			i++;
		}
	}

	cout << "The computer is moving to square: " << move << endl;
	return move;
}
//This function announces the winner of the game

void showWinner(char winner, char computer, char player)
{
	if (winner == computer)
	{
		cout << winner << "'s won! \n";
		cout << "Thank you for playing. Better luck next time.\n";

		system("pause");
	}
	else if (winner == player)
	{
		cout << winner << "'s won!\n";
		cout << "Congratulations, you won!";

		system("pause");
	}
	else
	{
		cout << "It's a tie \n";
		cout << "Thanks for playing. Better luck next time";

		system("pause");
	}
}