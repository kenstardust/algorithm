#pragma once
#include<iostream>
#include"Users.h"
#include<vector>
using namespace std;
class Mdf //��Ŀ¼��
{
private:
	string uname;//�û���
	string password;//�û���¼����
	vector<Users>que;
public:
	Mdf();
	Mdf(string uname, string password);
	string get_uname();
	void ch_uname(string uname);
	string get_password();
	void ch_password(string password);
	void Push(Users t);
	void Delete(string fnames);//ɾ�����ļ�����
	int Size();
	Users get_Users(int p);
	void ch_Users(Users m, int p);

};


