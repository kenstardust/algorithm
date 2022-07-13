#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;
class Afd //用户打开文件类
{
private:
	string opnames; //文件名
	int flag = 0;//文件存在标志
	int opfprotect[3] = { 0,0,0 }; //文件保护标志r\w\e
	int rwpoint = rand() % 100;;//文件读写指针
public:
	Afd();
	Afd(string opname, int opfp, int rwpoint=1);
	string get_opname();
	void ch_opname(string opnames);
	int get_flag();
	void ch_flag(int flag);
	int get_opfp(int p);
	void ch_opfp(int p);
	int get_rwpoint();
};

