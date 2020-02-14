/*************************************************************************
	> File Name: Gobang.cpp
	> Author: MasonZhao
	> Mail: zhaomangang@qq.com 
	> Created Time: Fri 14 Feb 2020 11:46:46 AM CST
 ************************************************************************/

#include<iostream>
#include <unistd.h>
#include <termio.h>
#include <stdio.h>
#include <stdlib.h>
#include "Gobang.h"
#define TTY_PATH "/dev/tty"
#define STTY_CLOSE             "stty raw -echo -F "
#define STTY_OPEN            "stty -raw echo -F "

using namespace std;
Gobang::Gobang() {
	initCheckerboard();
	this->pos_x_now = 0;
	this->pos_y_now = 0;
	this->who_now = true;
}
Gobang::~Gobang() {
	system(STTY_OPEN TTY_PATH);
}
void Gobang::initCheckerboard() {
	//初始化棋盘，
	for(int i=0;i<this->board_size;++i) {
		for(int j=0;j<2*this->board_size;++j) {
			if(j%2==0)
				this->Checkerboard[i][j] = board;
			else
				this->Checkerboard[i][j] = " ";
		}
	}

}

void Gobang::printBoard() {
	//打印棋盘
	cout<<"\033[2J";
	movePos('c');
		//打开参数
	system(STTY_OPEN TTY_PATH);
	for(int i=0;i<this->board_size;i++){
		for(int j=0;j<2*this->board_size;j++) {
			cout<<Checkerboard[i][j];
		}
		cout<<endl;
	}
	help();
	movePos('c');
}

int Gobang::downPiece(int pos_x,int pos_y,bool price_type) {
	//落子，price_type = true时落黑子，反之落白子
	if(price_type){
		this->Checkerboard[pos_x][pos_y] = piece_black;
	}
	else {
		this->Checkerboard[pos_x][pos_y] = piece_white;
	}
	int win = checkWin();
	//printBoard();
	return win;

}
void Gobang::movePos(char type) {
	//移动光标位置
	/***
	c、移至默认位置,(开)
	u、向上移动
	d、下
	l、左
	r、右
	\033[y;xH设置位置
	\033[nA  光标上移n行 
	\033[nB  光标下移n行 
	\033[nC  光标右移n行 
	\033[nD  光标左移n行 
	**/
	switch(type) {
		case 'c':cout<<"\033[0;0H";
				this->pos_x_now = 0;
				this->pos_y_now = 0;
				break; 
		case 'u':cout<<"\033[1A";
				this->pos_x_now--;
				break; 
		case 'd':cout<<"\033[1B";
				this->pos_x_now++;
				break; 
		case 'l':cout<<"\033[2C";
				this->pos_y_now+=2;
				break; 
		case 'r':cout<<"\033[2D";
				this->pos_y_now-=2;
				break; 
		default:break;
	}

}
int Gobang::scanKeyboard()
{
	int in;
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
 
	in = getchar();
 
	tcsetattr(0,TCSANOW,&stored_settings);
	return in;
}
//这个方法就可以，返回值是该键的ASCII码值，不需要回车的，

int Gobang::checkWin() {
	//检测是否一方获胜。,返回1黑胜，返回2，白胜，返回0，无
	string temp = Checkerboard[pos_x_now][pos_y_now];
	int count=5;
	for(int x = pos_x_now;x>=0;--x){
		if(temp==Checkerboard[x][pos_y_now]) {
			count--;
		}else {
			break;
		}	
	}
	for(int x = 1+pos_x_now;x>=0&&x<15;++x){
		if(temp==Checkerboard[x][pos_y_now]) {
			count--;
		}else {
			break;
		}
	}
	if(count<=0) {
		if(this->who_now){
			return 1;
		}else{
			return 2;
		}
	}else {
		count = 5;
	}
	for(int y = pos_y_now;y>=0;y-=2) {
		if(temp==Checkerboard[pos_x_now][y]) {
			count--;
		}else {
			break;
		}	
	}
	for(int y = 2+pos_y_now;y>=0&&y<30;y+=2) {
		if(temp==Checkerboard[pos_x_now][y]) {
			count--;
		}else {
			break;
		}	
	}
	if(count<=0) {
		if(this->who_now){
			return 1;
		}else {
			return 2;
		}
	}else {
		count = 5;
	}

	for(int x = pos_x_now,y = pos_y_now;x>=0&&y>=0;x--,y-=2) {
		if(temp==Checkerboard[x][y]) {
			count--;
		}else {
			break;
		}	
	}
	for(int x = pos_x_now+1,y = pos_y_now+2;x>=0&&x<15&&y<30&&y>=0;x++,y+=2) {
		if(temp==Checkerboard[x][y]) {
			count--;
		}else {
			break;
		}	
	}
	if(count<=0) {
		if(this->who_now){
			return 1;
		}else {
			return 2;
		}
	}else {
		count = 5;
	}

	for(int x = pos_x_now,y = pos_y_now;x>=0&&y<30&&y>=0;x--,y+=2) {
		if(temp==Checkerboard[x][y]) {
			count--;
		}else {
			break;
		}	
	}	

	for(int x = pos_x_now+1,y = pos_y_now-2;x>=0&&y<30&&y>=0;x++,y-=2) {
		if(temp==Checkerboard[x][y]) {
			count--;
		}else {
			break;
		}	
	}	
	if(count<=0) {
		if(this->who_now){
			return 1;
		}else {
			return 2;
		}
	}else {
		return 0;
	}

	return 0;

}


int Gobang::play() {
	while(1) {
		system(STTY_CLOSE TTY_PATH);
		int temp = scanKeyboard();
		if(100==temp) {
			if(this->Checkerboard[pos_x_now][pos_y_now]==board){
				this->winer = downPiece(this->pos_x_now,this->pos_y_now,this->who_now);
				this->who_now = !this->who_now;
				printBoard();
				if(this->winer!=0){
					break;
				}
			}
			
		}else if(65==temp) {
			movePos('u');
		}else if(66==temp) {
			movePos('d');
		}else if(68==temp) {
			movePos('r');
		}else if(67==temp) {
			movePos('l');
		}else {
			//break;

		}
	}
	help();
	return this->winer;

}

void Gobang::help()	{


	if(winer==0){
		cout<<"\033[4;50H";
		cout<<"提示";
		cout<<"\033[6;40H";
		cout<<"移动光标："<<"键盘向键 ▲ ▼ ◄ ►";
		cout<<"\033[8;40H";
		cout<<"落子："<<"光标移至对应位置后按 d ";
		cout<<"\033[10;40H";
		cout<<"当前操作方：";
		if(this->who_now) {
			cout<<"黑方("<<this->piece_black<<")";
		}else {
			cout<<"白方("<<this->piece_white<<")";
		}
	}else {
		cout<<"\033[4;50H";
		cout<<"获胜";
		cout<<"\033[6;40H";
		cout<<"获胜方：";
		if(this->winer==1) {
			cout<<"黑方("<<this->piece_black<<")";
		}else {
			cout<<"白方("<<this->piece_white<<")";
		}
		cout<<"\033[16;0H";
	}
	
}
