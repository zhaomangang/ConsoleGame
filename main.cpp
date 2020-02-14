/*************************************************************************
	> File Name: main.cpp
	> Author: MasonZhao
	> Mail: zhaomangang@qq.com 
	> Created Time: Fri 14 Feb 2020 11:10:45 AM CST
 ************************************************************************/


#include<iostream>

#include <string>
#include <stdio.h>
#include "Gobang.h"
using namespace std;




int main()
{

	Gobang gobang;
	// while(1)
	// {
	// 	cout<<gobang.scanKeyboard()<<endl;
	// }
	gobang.printBoard();
	int winer = gobang.play();
	return 0;
}
