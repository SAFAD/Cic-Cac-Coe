###################################################
##################Cic-Cac-Coe######################
######## All rights reserved to SAFAD(C) ##########
###########Please read the LICENSE file############
###################################################

#include <iostream>
using namespace std;

//X or O ?
char XorO[9] = {'0','1','2','3','4','5','6','7','8'};
//the game is running or not ? 1 yes , 0 no
int game_status = 1;
//rounds 1 = player1, 2 = player2
int rounds = 1;
//to define the character we put in the column
char block;
//the user input
int selection;

//show winner !
void show_winner(){
	cout << "Winner is Player " << rounds << " congratulations !!" << endl;
}

//check who won !
bool check_winner(){
	if(XorO[0] && XorO[1] && XorO[2] == 'X' || XorO[0] && XorO[1] && XorO[2] == 'O'){
		return true;
	}
	if(XorO[3] && XorO[4] && XorO[5] == 'X' || XorO[3] && XorO[4] && XorO[5] == 'O'){
		return true;
	}
	if(XorO[6] && XorO[7] && XorO[8] == 'X' || XorO[6] && XorO[7] && XorO[8] == 'O'){
		return true;
	}
	if(XorO[0] && XorO[3] && XorO[6] == 'X' || XorO[0] && XorO[3] && XorO[6] == 'O'){
		return true;
	}
	if(XorO[1] && XorO[4] && XorO[7] == 'X' || XorO[1] && XorO[4] && XorO[7] == 'O'){
		return true;
	}
	if(XorO[2] && XorO[5] && XorO[8] == 'X' || XorO[2] && XorO[5] && XorO[8] == 'O'){
		return true;
	}
	if(XorO[0] && XorO[4] && XorO[8] == 'X' || XorO[0] && XorO[4] && XorO[8] == 'O'){
		return true;
	}
	if(XorO[2] && XorO[4] && XorO[6] == 'X' || XorO[2] && XorO[4] && XorO[6] == 'O'){
		return true;
	}
	
	return false;
}

//function to switch from player one to two and vice versa
void switch_turns(){
	if(rounds == 1){
		rounds = 2;
	}
	else{
		rounds = 1;
	}
}

//validates the user input
bool validate_selection(int selection){
	if(XorO[selection] == 'X' || XorO[selection] == 'O'){
		return false;
	}
	else {
		return true;
	}
}

//function to show the board
void board(){
	cout << "+++++++++++++++++++++++++++++" << endl;
	cout << "+++++ "<< XorO[0] <<" ++++ "<< XorO[1] << " +++++ " << XorO[2] <<" ++++++" << endl;
	cout << "+++++++++++++++++++++++++++++" << endl;
	cout << "+++++ "<< XorO[3] <<" ++++ "<< XorO[4] << " +++++ " << XorO[5] <<" ++++++" << endl;
	cout << "+++++++++++++++++++++++++++++" << endl;
	cout << "+++++ "<< XorO[6] <<" ++++ "<< XorO[7] << " +++++ " << XorO[8] <<" ++++++" << endl;
	cout << "+++++++++++++++++++++++++++++" << endl;
	if(rounds == 1){
		block = 'X';
	}
	else{
		block = 'O';
	}
	cout << "Player " << rounds << " Please enter a valid number (0-8) :" <<endl;
	cin >> selection;
	if(validate_selection(selection)){
		XorO[selection] = block;
		//before we switch turns, we check if the user won or not
		if(!check_winner()){
			switch_turns();
		}
		else{
			show_winner();
			game_status = 0;
		}
	}
	
}

int main(){
	while(game_status == 1){
		board();
	}
}

