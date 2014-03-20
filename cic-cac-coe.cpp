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
vector<int> originalBoard;
//the game is running or not ? 1 yes , 0 no
int status = 0;
//turns 1 = player1, -1 = player2 OR CPU
char turn = -1;
//to define the character we put in the column
char block;
//the user input
int selection;
//AI vs Human
int opponent;

int checkGame(vector<int> board);
void run();
//show the board
char ReplaceBlocks(int blockId){
	switch(blockId) {
        case -1:
            return 'X'; //it is the first player..
        case 0:
            return ' '; //an empty block
        case 1:
            return 'O'; //second player here..
    }
    return ' ';

}
void DrawBoard() {
    for(int i=0; i<7; i+=3) {
        cout << " " <<  ReplaceBlocks(originalBoard[i]) <<" | "<< ReplaceBlocks(originalBoard[i+1]) << " | " << ReplaceBlocks(originalBoard[i+2])  << endl;
        if (i != 6)
        {
        	cout << "---+---+---" <<endl;
        }
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
int check_winner(vector<int> board){

    for(int i=0; i<7; i+=3) {
        if((board[i] == -1 && board[i+1] == -1 && board[i+2] == -1) || (board[i] == 1 && board[i+1] == 1 && board[i+2] == 1)){
            return board[i];
        }
    }

    for(int i=0; i<3; i++) {
        if((board[i] == -1 && board[i+3] == -1 && board[i+6] == -1) || (board[i] == 1 && board[i+3] == 1 && board[i+6] == 1)){
            return board[i];
        }
    }

    for(int i=0; i<3; i+=2) {
        if((board[i] == -1 && board[4] == -1 && board[8-i] == -1) || (board[i] == 1 && board[4] == 1 && board[8-i] == 1)){
            return board[i];
        }
    }

    return 0;
}

bool check_draw(vector<int> board){
    if (std::count(board.begin(), board.end(), 0) < 0)
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
	if(originalBoard[selection] == 1 || originalBoard[selection] == -1){
		return false;
	}
	else {
		return true;
	}
}

//function to switch from player one to two and vice versa
void switch_turns(){
	turn = (turn == 1) ? -1 : 1;
	run();
}

void check_status(vector<int> board){
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

vector<int> getAllPossibleMoves(vector<int> board){
	vector<int> spaces;
	for (int i = 0; i < 9; ++i)
	{
		if (board[i] == 0)
		{
			//this is the chosen one
			spaces.push_back(i);
		}
	}
	return spaces;
}

//we use this function to check the game status, is it won, or draw
//int unfinished = 0, won = 1, draw = 2;

int checkGame(vector<int> board){
	if(check_winner(board)){
		return 1;
	}
	//what if the game is a Draw ?
	else if(check_draw(board)){
		return 2;

	}
	return 0;
}

int minmax(vector<int> board, int player){
	//player == 1 => X, == -1 => O
	int win = check_winner(board),
		bestScore = -2,
		bestMove = -1;
	if (win > 0) return player*win;

	for(std::vector<int>::size_type i = 0; i != originalBoard.size(); i++) 
	{
		if (board[i] == 0)
		{
			board[i] = player;
			int score = -minmax(board, -player);
			cout << score << endl;
			if (score > bestScore)
			{
				bestScore = score;
				bestMove = i;
			}
			board[i] = 0;
		}
	}
	if(bestMove == -1) return 0;
	return bestScore;
}
void AI(){
	//cout << "Calculating..." << endl;
	int bestScore = -2,
		bestMove = -1;
	for(std::vector<int>::size_type i = 0; i != originalBoard.size(); i++) {
	    if (originalBoard[i] == 0)
		{
			originalBoard[i] = 1;
			int score = -minmax(originalBoard, -1);
			originalBoard[i] = 0;
			if (score > bestScore)
			{
				bestScore = score;
				bestMove = i;
			}
		}
	}

	//now we use it on screen
	originalBoard[bestMove] = 1;
	check_status(originalBoard);
	
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
	if (opponent == 2)
	{
		if (turn == -1)
		{
			DrawBoard();
		}
		
	}else{
		DrawBoard();
	}
	//Artificial Inteligence :)
	if(opponent == 2 && turn == 1){
		AI();
	}
	else{
		player();
	}

}

int main(){
	//we first populate the board with dummy strings
	int dummy[9] = {0,0,0,0,0,0,0,0,0};

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

