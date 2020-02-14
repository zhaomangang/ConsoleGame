/*************************************************************************
	> File Name: Gobang.h
	> Author: MasonZhao
	> Mail: zhaomangang@qq.com 
	> Created Time: Fri 14 Feb 2020 11:08:20 AM CST
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;
class Gobang {
private:
	string Checkerboard[15][30];
	unsigned int board_size = 15;
	string board = "□";
	string piece_white = "☻";
	string piece_black = "☺";
	int pos_x_now;
	int pos_y_now;
	bool who_now;	//谁正在操作
	int winer;
public:
	Gobang();
	~Gobang();
	void initCheckerboard();
	void printBoard();
	int downPiece(int pos_x,int pos_y,bool price_type);
	void movePos(char type);
	int play();
	int scanKeyboard();
	int checkWin();
	void help();

};







