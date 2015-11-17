#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


class Checker{
	public:
		int type;
		int x,y;
		void changeType (int in){
			type=in;
		}
		void changeLocation(int xin,int yin){
			x=xin;
			y=yin;
		}
		string toString(){
			string letters [4] ={"b","B","r","R"};

			return letters[type] + " " + to_string(x) + "," + to_string(y);
		}
		string piece(){
			string letters [4] ={"b","B","r","R"};
			return letters[type];
		}
		Checker(int t,int xin,int yin){
			x=xin;
			y=yin;
			type=t;
		}
};

class Checker_Board {
	vector<Checker> pieces;
	public:
		Checker_Board (vector<Checker> in_pieces){
			pieces=in_pieces;
		}

		//returns a string that's a concatanation of all the piece descriptions
		string toString(){
			string out="";
			for(int i=0;i<pieces.size();i++){
				out+="(" + pieces[i].toString() + ")";
			}
			return out;
		}

		//returns a string in the form of a board
		string printBoard(){
			string board [8][8];
			for (int i=0;i<8;i++){
				for (int j=0;j<8;j++)
					board[i][j]=" ";
			}	
			for (int i=0;i<pieces.size();i++){
				//cout << pieces[i].piece();
				//cout << pieces[i].x << pieces[i].y << "\n";
				board[pieces[i].x][pieces[i].y]=pieces[i].piece();
				//cout << board[0][0] << "\n";
			}
			string out="";
			for (int i=0;i<8;i++){
				for (int j=0;j<8;j++){
					out+=board[i][j];
				}
				out+="\n";
				//cout << out;
			}
			return out;
		}
};

Checker_Board make_new_board(){
	vector<Checker> pieces;
	for( int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if((i+j)%2==0 && i<3)
				pieces.push_back(Checker(2,i,j));
			else if ((i+j)%2==0 && i>4)
				pieces.push_back(Checker(0,i,j));
		}
	}
	return Checker_Board(pieces);
};

int main(){
	Checker_Board board=make_new_board();
	cout << board.printBoard();
	return 0;
}