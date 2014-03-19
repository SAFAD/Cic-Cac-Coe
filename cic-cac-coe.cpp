/*###################################################
  ##################Cic-Cac-Coe######################
  ######## All rights reserved to SAFAD(C) ##########
  ###########Please read the LICENSE file############
  ###################################################*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

//This is our board, 0 => empty, 1 => X, 2 => O
vector<char> originalBoard;
//the game is running or not ? 1 yes , 0 no
int status = 0;
//turns 1 = player1, 2 = player2 OR CPU
char turn = 'X';
//to define the character we put in the column
char block;
//the user input
int selection;
//AI vs Human
int opponent;

int checkGame(vector<char> board);
void run();
//show the board
void ShowBoard() {
    for(int i=0; i<7; i+=3) {
        cout <<  originalBoard[i] <<" | "<< originalBoard[i+1] << "| " << originalBoard[i+2]  << endl;
    }
}

//tell them spike, tell them its a draw !!
void show_draw(){
	cout << "Nothing to see here Peeps, its a Draw" << endl;
}
//show winner !
void show_winner(){
	cout << "Winner is Player " << turn << " congratulations !!" << endl;
}

//check who won !
bool check_winner(vector<char> board){

    for(int i=0; i<7; i+=3) {
        if((board[i] == 'X' && board[i+1] == 'X' && board[i+2] == 'X') || (board[i] == 'O' && board[i+1] == 'O' && board[i+2] == 'O')){
            return true;
        }
    }

    for(int i=0; i<3; i++) {
        if((board[i] == 'X' && board[i+3] == 'X' && board[i+6] == 'X') || (board[i] == 'O' && board[i+3] == 'O' && board[i+6] == 'O')){
            return true;
        }
    }

    for(int i=0; i<3; i+=2) {
        if((board[i] == 'X' && board[4] == 'X' && board[8-i] == 'X') || (board[i] == 'O' && board[4] == 'O' && board[8-i] == 'O')){
            return true;
        }
    }

    return false;
}

bool check_draw(vector<char> board){
    if (std::count(board.begin(), board.end(), 'E') < 0)
    {
        //there still are no more moves
        //now lets see if someone one
        if (!check_winner(board)) {
            return true;
        }
    }

	return false;

}

//validates the user input
bool validate_selection(int selection){
	//first we check if it is out of range
	if (selection > 8 || selection < 0)
	{
		return false;
	}
	if(originalBoard[selection] == 'X' || originalBoard[selection] == 'O'){
		return false;
	}
	else {
		return true;
	}
}

//function to switch from player one to two and vice versa
void switch_turns(){
	turn = (turn == 'X') ? 'O' : 'X';
	run();
}

void check_status(vector<char> board){
	int gameStatus = checkGame(board);
	//before we switch turns, we check if the user won or not
	if(gameStatus == 0){
		switch_turns();
		
	}
	//what if the game is a Draw ?
	else if(gameStatus == 2){
		show_draw();
		status = 0;
	}
	else if(gameStatus == 1){
		//winnnnnn
		show_winner();
		status = 0;
	}
}

vector<int> getAllPossibleMoves(vector<char> board){
	vector<int> spaces;
	for (int i = 0; i < 9; ++i)
	{
		if (board[i] == 'E')
		{
			//this is the chosen one
			spaces.push_back(i);
		}
	}
	return spaces;
}

//we use this function to check the game status, is it won, or draw
//int unfinished = 0, won = 1, draw = 2;

int checkGame(vector<char> board){
	if(check_winner(board)){
		return 1;
	}
	//what if the game is a Draw ?
	else if(check_draw(board)){
		return 2;

	}
	return 0;
}

int getScore(vector<char> board, char turn){
	int bestScore = 0,
		iterations = 0,
		MAXWIN = 100,
		penalty = -5;
	//here, we read all the possible moves, and choose the best based on the score
	//score, MAXWIN = 100, DRAW = 0, MAXLOSE = -5
	//The MAXWIN score is acheived by doing the least of iterations
	//MAXLOSE score is achieved by doing the most of iterations, this means the computer, if he is going to lose, choose the longest path
	//How to calculate score: MAXWIN += -5*(iterations); MAXLOSE += 5*(iterations);
	//first we get all the possible moves
	vector<int> moves = getAllPossibleMoves(board);
	//now we loop through every possibility
	for(std::vector<int>::size_type i = 0; i != moves.size(); i++) 
	{
		//okay so for this we clone the board, add our move
		vector<char> newBoard(board);
		//then we add a move 
		newBoard[moves[i]] = turn;

		//now we check if the game is won or a draw
		if (checkGame(newBoard) == 1){
			//this move, wins the game, but who won?
			//if the AI wins : calculate the score, if it is better, save it as best score
			//if the opponent wins : we calculate the lose score, compare it if it is better, then save it..
			int score;
			if (turn == 'O')
			{
				//its me mittens!
				score =  MAXWIN + penalty*iterations;
			}else{
				//its the human being...
				score = -MAXWIN + penalty*iterations;
				
			}
			bestScore = (bestScore < score) ? score : bestScore;
		}else if (checkGame(newBoard) == 2){
			//its a draw, we see if the bestScore is a losing score, we rather draw than lose..
			bestScore = (bestScore < 0) ? 0 : bestScore;
		}else{
			//the game is unfinished
			++iterations;
			//now we create a new board, and get its best score..
			vector<char> clonedBoard(newBoard);
			char newTurn = (turn == 'X') ? 'O' : 'X';
			int score = getScore(clonedBoard,newTurn);

			bestScore = (bestScore < score) ? score : bestScore;
		}

	}
	return bestScore;
}
bool opponentMove(vector<char> board){
	bool win = false;
	vector<int> opponentMoves = getAllPossibleMoves(board);
	for(std::vector<int>::size_type i = 0; i != opponentMoves.size(); i++) {
		vector<char> newBoard(originalBoard);
		newBoard[opponentMoves[i]] = 'X';
		if (checkGame(newBoard) == 1)
		{
			win = true;
			break;
		}
	}
	return win;
}
int nextMove(){
	//first we see, if the game has just begun
	//first we generate a list of all possible moves
	//then we loop over it over each choice, if the game can be lost on the next human move
	//priority = 0 if draw, 1 if lose, 2 if win;
	int bestScore = 0,
		bestPriority,
		bestMove = 0;

	vector<int> moves = getAllPossibleMoves(originalBoard);
	int size = moves.size();

	if (size == 8)
	{
		int random = rand() % moves[7] + moves[0];
		return moves[random];

	}
	//now we see what the opponent would pick..
	if (opponentMove(originalBoard))
	{
		/* code */
	}
	for(std::vector<int>::size_type i = 0; i != size; i++) {
	    vector<char> newBoard(originalBoard);
		newBoard[moves[i]] = 'O';
		//now we check whether the move wins us or not
		int priority = checkGame(newBoard);
		if (priority > bestPriority && priority != 0)
		{
			bestPriority = priority;
			bestMove = moves[i];
		}
		else if (priority == 0)
		{
			//the game is unfinished, if true it means he can win
			if (!opponentMove(newBoard) && priority > bestPriority)
			{
				bestPriority = priority;
				bestMove = moves[i];
			}
		}
	}
	return bestMove;
}
void AI(){
	//cout << "Calculating..." << endl;
	int next = nextMove();
	//now we use it on screen
	if(validate_selection(next)){
		originalBoard[next] = 'O';
		check_status(originalBoard);
	}
	else{
		AI();
	}
}

void player(){
	cout << "Player " << turn << " Please enter a valid number (0-8) :" <<endl;
	cin >> selection;
	if(validate_selection(selection)){
		originalBoard[selection] = turn;
		check_status(originalBoard);
	}else{
		//his choice is invalid
		cout << "invalid move" << endl;
		player();
	}
}

//function to show the board
void run(){
	ShowBoard();
	//Artificial Inteligence :)
	if(opponent == 2 && turn == 'O'){
		AI();
	}
	else{
		player();
	}

}

int main(){
	//we first populate the board with dummy strings
	char dummy[9] = {'E','E','E','E','E','E','E','E','E'};

	for(int index=0;index<9; ++index)
	{
		originalBoard.push_back(dummy[index]);
	}

	if(status == 0){
		cout << "Play VS :" << endl;
		cout << "1. Human" << endl;
		cout << "2. AI (CPU)" << endl;
		cin >> opponent;
		status = 1;
	}
	run();
}

