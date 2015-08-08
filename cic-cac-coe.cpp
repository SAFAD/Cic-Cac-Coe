/*###################################################
  ##################Cic-Cac-Coe######################
  ######## All rights reserved to SAFAD(C) ##########
  ###########Please read the LICENSE file############
  ###################################################*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

//PROTOTYPING
vector<int> originalBoard;
int status = 0;
char turn = -1;
char block;
int selection;
int opponent;
int checkGame(vector<int> board);
void run();
void show_winner();
void show_draw();
char convertToPlayer(int);
bool validate_selection(int);
void DrawBoard();


/***********************************
************** MAIN ****************
***********************************/
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


/***************************************************
* This is a function that takes the character in the
* slot and returns what value is there.
* X = -1  |  O = 1  |  _ = 0
***************************************************/
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


/***************************************************
* This is a function that checks the board for
* combinations that would be considered a winner
* Standard rules apply.
***************************************************/
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


/***************************************************
* This is a function that notes that if all 9 spaces
* have been taken up and that it should check for draw
***************************************************/
bool check_draw(vector<int> board){
    if (std::count(board.begin(), board.end(), 0) < 0)
    {
        if (!check_winner(board)) {
            return true;
        }
    }

	return false;
}


/***************************************************
* This is a function to switch from player one to
* two and vice versa.
***************************************************/
void switch_turns(){
	turn = (turn == 1) ? -1 : 1;
	run();
}


/***************************************************
* This is a function to set the status of if the
* player has won the game so that it can be checked
* in the next function.
* No winner = 0  |  winner = 1  |  Draw = 2
***************************************************/
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


/***************************************************
* This is a function to dictate if the person wins,
* loses, draw, or if it continues and switches turns.
* No winner = 0  |  winner = 1  |  Draw = 2
***************************************************/
void check_status(vector<int> board){
	int gameStatus = checkGame(board);

	if(gameStatus == 0){            //
		switch_turns();             // NO WINNER
	}                               //

	else if(gameStatus == 1){       //
		show_winner();              // THERE IS A WINNER
		status = 0;                 //
	}

	else if(gameStatus == 2){       //
		show_draw();                // THERE IS A DRAW
		status = 0;                 //
	}

}


/*********************************************************
* This function takes the AI settings and who's turn it is
* then proceeds through the menus.
**********************************************************/
void player(){

	if(opponent == 2 && turn != 1)
    {
        char whosTurn = convertToPlayer(turn);
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "*       Player " << whosTurn << " Please enter a valid number (0-8) :       *" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cin >> selection;
    }
    else if(opponent == 2 && turn == 1)
    {
        srand(time(NULL));
        selection = rand() % 8;
    }
    //If current selection is empty,
    //then mark
	if(validate_selection(selection))
    {
		originalBoard[selection] = turn;
		check_status(originalBoard);
	}
	else{
		//his choice is invalid
		cout << "invalid move, lose a turn!" << endl << "switching turns\n"<< endl;
		switch_turns();
	}
}

/*****************************************
* This function is in place so that the
* board is only drawn humans, not when
* AI plays.
******************************************/
void run(){
	if (opponent == 2)
	{
		if (turn == -1)
		{
			DrawBoard();
		}
	}
	else
    {
		DrawBoard();
	}

	if(opponent == 2 && turn == 1){
		player();
	}
	else{
		player();
	}
}




/*********************************************************
* This is a function that will check the board to see
* if there is already something in the place and report
* true or false back so the other functions can
* process accordingly.
*********************************************************/
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


/***********************************************
* Game end - text out functions..... shows the
* message of what the result was.
***********************************************/
void show_draw(){
    DrawBoard();
	cout << "Nothing to see here Peeps, its a Draw" << endl;
}
void show_winner(){
    char winner = convertToPlayer(turn);
    DrawBoard();
	cout << "***Winner is " << winner << ", congratulations !!***" << endl;
}


/***********************************************
* This functions converts the raw player
* value (-1 or 1)into the actual letter (x or o)
***********************************************/
char convertToPlayer(int x)
{
    char outputOf;
    if(x == -1)
        {outputOf = 'X';}
    else if (x == 1)
        {outputOf = 'O';}
    return outputOf;
}

/******************************
* Displays the board
******************************/
void DrawBoard() {
    for(int i=0; i<7; i+=3) {
        cout << " " <<  ReplaceBlocks(originalBoard[i]) <<" | "<< ReplaceBlocks(originalBoard[i+1]) << " | " << ReplaceBlocks(originalBoard[i+2])  << endl;
        if (i != 6)
        {
        	cout << "---+---+---" <<endl;
        }
    }
}
