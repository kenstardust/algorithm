#pragma once
#include<iostream>
#include<Windows.h>
#include"Afd.h"
#include<vector>
using namespace std;
class Users //用户文件目录类
{
private:
	int Limt = 15;
	string Ufnames;
	//string fnames[15];
	int flag;//文件存在标志
	int fprotected[3] = { 0,0,0 };//保护标志r\w\e 1可 0不可
	SYSTEMTIME fdate;//文件创造时间 
	int flength = 0;//文件长度
	vector<Afd>que;
	vector<string> fnames;
public:
	Users();
	Users(string fnames, int fp, int flength);
	string get_fnames(int t);//重载更新用户下的文件集名字 
	void Push_fnames(string fnames);
	string get_Ufnames();//该目录用户文件夹名
	bool ch_Ufnames(string fnames);//更新目录用户文件夹名
	int get_flag();
	bool ch_flag(int flag);
	int get_fp(int t);
	bool ch_fp(int p,int c);//位置 状态
	SYSTEMTIME get_fdate();
	bool ch_fdate();
	int get_flength();
	bool ch_flength();
	Afd get_Afd(int p);
	void ch_Afd(Afd m, int p);
	void Push(Afd m);
	bool Delete(string fnames);//删除的文件名字
};


