#pragma once
#include<iostream>
#include<Windows.h>
#include"Afd.h"
#include<vector>
using namespace std;
class Users //�û��ļ�Ŀ¼��
{
private:
	int Limt = 15;
	string Ufnames;
	//string fnames[15];
	int flag;//�ļ����ڱ�־
	int fprotected[3] = { 0,0,0 };//������־r\w\e 1�� 0����
	SYSTEMTIME fdate;//�ļ�����ʱ�� 
	int flength = 0;//�ļ�����
	vector<Afd>que;
	vector<string> fnames;
public:
	Users();
	Users(string fnames, int fp, int flength);
	string get_fnames(int t);//���ظ����û��µ��ļ������� 
	void Push_fnames(string fnames);
	string get_Ufnames();//��Ŀ¼�û��ļ�����
	bool ch_Ufnames(string fnames);//����Ŀ¼�û��ļ�����
	int get_flag();
	bool ch_flag(int flag);
	int get_fp(int t);
	bool ch_fp(int p,int c);//λ�� ״̬
	SYSTEMTIME get_fdate();
	bool ch_fdate();
	int get_flength();
	bool ch_flength();
	Afd get_Afd(int p);
	void ch_Afd(Afd m, int p);
	void Push(Afd m);
	bool Delete(string fnames);//ɾ�����ļ�����
};


