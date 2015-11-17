#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <array>

using namespace std;


class Checker{
	public:
		bool empty;
		int type;
		int r,c;
		Checker move(int rin,int cin, bool king){
			if(king)
				return Checker(type+1,rin,cin);
			else
				return Checker(type,rin,cin);

		}
		string toString(){
			string letters [4] ={"b","B","r","R"};
			if (empty)
				return "empty";
			else
				return letters[type] + " " + to_string(r) + "," + to_string(c);
		}
		string piece(){
			string letters [4] ={"b","B","r","R"};
			if (empty)
				return "_";
			else
				return letters[type];
		}
		Checker(int t,int rin,int cin){
			r=rin;
			c=cin;
			type=t;
			empty=false;
		}
		Checker(){
			empty=true;
		}
		Checker copy(){
			return Checker(type,r,c);
		}
};

class Checker_Board {
	vector<Checker> pieces;
	int move;
	array<array<Checker,8>,8> board;
	

	vector<Checker> viableNonJumps(Checker in){
		vector<Checker> out;
		if((in.type/2)==move){
			if(in.type%2==0){
				int dir=move*2-1;
				if (viableLocation(in.r+dir,in.c-1))
					out.push_back(in.move(in.r+dir,in.c-1,(in.r==6)));
				if (viableLocation(in.r+dir,in.c+1))
					out.push_back(in.move(in.r+dir,in.c+1,(in.r==6)));
			}
			else{
				if (viableLocation(in.r+1,in.c-1))
					out.push_back(in.move(in.r+1,in.c-1,false));
				if (viableLocation(in.r+1,in.c+1))
					out.push_back(in.move(in.r+1,in.c+1,false));
				if (viableLocation(in.r-1,in.c-1))
					out.push_back(in.move(in.r-1,in.c-1,false));
				if (viableLocation(in.r-1,in.c+1))
					out.push_back(in.move(in.r-1,in.c+1,false));
			}
		}
		return out;
	}	
	vector<Checker> viableJumps(Checker in){
		vector<Checker> out;
		return out;
	}

	vector<Checker> viableMoves(Checker in){
		vector<Checker> out=viableNonJumps(in);
		vector<Checker> temp=viableJumps(in);
		out.insert(out.end(),temp.begin(),temp.end());
		return out;
	}
	public:
		bool viableLocation(int r, int c){
			if(r>=0 && r<= 7 && c>=0 && c <= 7){
				if(board[r][c].empty)
					return true;
			}
			return false;
		}
		Checker_Board (vector<Checker> in_pieces, int in_move, array<array<Checker,8>,8> in_board){
			pieces=in_pieces;
			move=in_move;
			board=in_board;
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
			string out="";
			for (int i=0;i<8;i++){
				for (int j=0;j<8;j++){
					out+=board[i][j].piece();
				}
				out+="\n";
				//cout << out;
			}
			return out;
		}


		//outputes a vector of boards where each one is a possible board configuration after one move
		vector<Checker_Board> getAllMoves(){
			vector<Checker_Board> out;
			for (int i=0;i<pieces.size();i++){
				vector <Checker> moves=viableMoves(pieces[i]);
				//cout << pieces[i].toString() << " " << moves.size() << endl;
				for (int j=0;j<moves.size();j++){
					vector<Checker> pieces_copy=pieces;
					array<array<Checker,8>,8> board_copy=board;
					pieces_copy[i]=moves[j];
					board_copy[pieces[i].r][pieces[i].c]=Checker();
					board_copy[moves[j].r][moves[j].c]=moves[j].copy();
					out.push_back(Checker_Board(pieces_copy,1-move,board_copy));
				}
			}
			return out;
		}


};

Checker_Board make_new_board(){
	vector<Checker> pieces;
	array<array<Checker,8>,8> out_board;
	for (int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			out_board[i][j]=Checker();
		}
	}
	for( int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if((i+j)%2==0 && i<3){
				pieces.push_back(Checker(2,i,j));
				out_board[i][j]=Checker(2,i,j);
			}
			else if ((i+j)%2==0 && i>4){
				pieces.push_back(Checker(0,i,j));
				out_board[i][j]=Checker(0,i,j);
			}
		}
	}
	return Checker_Board(pieces,0,out_board);
};



int main(){
	Checker_Board new_board=make_new_board();
	cout << new_board.printBoard() << endl;
	//cout << new_board.viableLocation(4,3) << endl;
	vector<Checker_Board> moves=new_board.getAllMoves();
	
	for (int i=0;i<moves.size();i++){
		cout << moves[i].printBoard() << endl;
	}
	
	return 0;
}