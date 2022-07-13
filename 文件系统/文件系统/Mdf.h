#pragma once
#include<iostream>
#include"Users.h"
#include<vector>
using namespace std;
class Mdf //主目录类
{
private:
	string uname;//用户名
	string password;//用户登录密码
	vector<Users>que;
public:
	Mdf();
	Mdf(string uname, string password);
	string get_uname();
	void ch_uname(string uname);
	string get_password();
	void ch_password(string password);
	void Push(Users t);
	void Delete(string fnames);//删除的文件名字
	int Size();
	Users get_Users(int p);
	void ch_Users(Users m, int p);

};


