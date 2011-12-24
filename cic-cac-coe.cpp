/*###################################################
  ##################Cic-Cac-Coe######################
  ######## All rights reserved to SAFAD(C) ##########
  ###########Please read the LICENSE file############
  ###################################################*/

#include <iostream>
#include <cstdlib>
using namespace std;

//X or O ?
char XorO[9] = {'0','1','2','3','4','5','6','7','8'};
//the game is running or not ? 1 yes , 0 no
int game_status = 0;
//rounds 1 = player1, 2 = player2 OR CPU
int rounds = 1;
//to define the character we put in the column
char block;
//the user input
int selection;
//AI vs Human
int opponent;

//show winner !
void show_winner(){
	cout << "Winner is Player " << rounds << " congratulations !!" << endl;
}

//show the board
void show_board() {
    cout << "+++++++++++++++++++++++++++++" << endl;
    for(int i=0; i<7; i+=3) {
        cout << "+++++ "<< XorO[i] <<" ++++ "<< XorO[i+1] << " +++++ " << XorO[i+2] <<" ++++++" << endl;
        cout << "+++++++++++++++++++++++++++++" << endl;
    }
}
//tell them spike, tell them its a draw !!
void show_draw(){
	cout << "Nothing to see here Peeps, its a Draw" << endl;
}

//check who won !
bool check_winner(){
    
    for(int i=0; i<7; i+=3) {
        if((XorO[i] == 'X' && XorO[i+1] == 'X' && XorO[i+2] == 'X') || (XorO[i] == 'O' && XorO[i+1] == 'O' && XorO[i+2] == 'O')){
            return true;
        }
    }
    
    for(int i=0; i<3; i++) {
        if((XorO[i] == 'X' && XorO[i+3] == 'X' && XorO[i+6] == 'X') || (XorO[i] == 'O' && XorO[i+3] == 'O' && XorO[i+6] == 'O')){
            return true;
        }
    }
    
    for(int i=0; i<3; i+=2) {
        if((XorO[i] == 'X' && XorO[4] == 'X' && XorO[8-i] == 'X') || (XorO[i] == 'O' && XorO[4] == 'O' && XorO[8-i] == 'O')){
            return true;
        }
    }

    return false;
}

bool check_draw(){
	if( XorO[0] != '0' &&
		XorO[1] != '1' &&
		XorO[2] != '2' &&
		XorO[3] != '3' &&
		XorO[4] != '4' &&
		XorO[5] != '5' &&
		XorO[6] != '6' &&
		XorO[7] != '7' &&
		XorO[8] != '8'
	   ){
	   	return true;
	   }
	return false;
    
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

//function to switch from player one to two and vice versa
void switch_turns(){
	if(rounds == 1){
		rounds = 2;
	}	
	else{
		rounds = 1;
	}
}

void check_game_status(){
	//before we switch turns, we check if the user won or not
	if(check_winner()){
		show_board();
		show_winner();
		game_status = 0;
	}
	//what if the game is a Draw ?
	else if(check_draw()){
		show_board();
		show_draw();
		game_status = 0;
	
	}
	else{
		switch_turns();
	}
}



//function to show the board
void board(){
	show_board();
	if(rounds == 1){
		block = 'X';
	}
	else{
		block = 'O';
	}
	//Artificial Inteligence :)
	if(opponent == 2 && rounds == 2){
		selection = rand() % 9;
		if(validate_selection(selection)){
			XorO[selection] = block;
			check_game_status();
		}
	}
	else{
		cout << "Player " << rounds << " Please enter a valid number (0-8) :" <<endl;
		cin >> selection;
		if(validate_selection(selection)){
			XorO[selection] = block;
			check_game_status();
		}
	}
	
}

int main(){
	if(game_status == 0){
		cout << "Play VS :" << endl;
		cout << "1. Human" << endl;
		cout << "2. AI (CPU)" << endl;
		cin >> opponent;
		game_status = 1;
	}
	while(game_status == 1){
		board();
	}
	
}

