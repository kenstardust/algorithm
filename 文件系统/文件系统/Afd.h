#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;
class Afd //�û����ļ���
{
private:
	string opnames; //�ļ���
	int flag = 0;//�ļ����ڱ�־
	int opfprotect[3] = { 0,0,0 }; //�ļ�������־r\w\e
	int rwpoint = rand() % 100;;//�ļ���дָ��
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

