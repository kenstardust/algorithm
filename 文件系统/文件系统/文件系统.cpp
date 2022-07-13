#include<iostream>
#include<algorithm>
#include"Mdf.h"
#include"Afd.h"
#include"Users.h"
#include<Windows.h>
#include<conio.h>
#include<iomanip>
#include<vector>
using namespace std;
Mdf UFD[11];
vector<Afd> Pc;
const int Limt = 15;
int cnt_Afd = 0;
int cnt_UFD = 0;
int UFD_p = 0;

bool check(string fname)
{
	bool F = 0;
	vector<Afd>::iterator it = Pc.begin();
	for (; it < Pc.end(); it++)
	{
		if (fname == it->get_opname())
		{
			return true;
			break;
		}
	}
	return false;
}
void User_file(string Ufname,int loc)
{
	string command = "ERROR";
	while (command != "exit")
	{
		Users temp = UFD[UFD_p].get_Users(loc);
		cout << "root\\" << UFD[UFD_p].get_uname() << "\\" << temp.get_Ufnames()
			<< "\\  ";
		cin >> command;
		if (command == "ls")
		{
			Users m = UFD[UFD_p].get_Users(loc);
			for (int i = 0; i < m.get_flength(); i++)
			{
				if (m.get_flag())
				{
					cout << setw(15) << "用户文件名" << setw(15) << "逻辑地址" << setw(15) << "文件保护状态" << endl;
					cout << setw(15) << m.get_fnames(i) << setw(15) << i << setw(10) << "r\\w\\e ";
					Afd a = m.get_Afd(i);
					for (int j = 0; j < 3; j++)
					{
						if (j != 0)
							cout << "\\";
						cout << a.get_opfp(j);
					}
					cout << endl;
				}
				else
				{
					cout << "该文件目录不存在" << endl;
				}
			}
		}
		else if (command == "create")
		{
			string fname;
			int fp;
			cin >> fname >> fp;
			Users m = UFD[UFD_p].get_Users(loc);
			if (m.get_fp(1) == 1)
			{
				if (m.ch_flength() >= Limt)
				{
					cout << "空间已满" << endl;
				}
				else
				{
					m.Push_fnames(fname);
					Afd c(fname, fp);
					m.Push(c);
					c.~Afd();
					m.ch_flength();
					UFD[UFD_p].ch_Users(m, loc);
					cout << "Create Successed" << endl;
				}
			}
			else
			{
				cout << "该文件权限不能写" << endl;
			}
		}
		else if (command == "delete")
		{
			string fname;
			cin >> fname;
			Users m = UFD[UFD_p].get_Users(loc);
			if (m.get_fp(1) == 1 && m.Delete(fname))
			{
				UFD[UFD_p].ch_Users(m, loc);
				m.ch_flength();
				cout << "Delet Success" << endl;
			}
			else
			{
				cout << "Delet fall" << endl;
			}
		}
		else if (command == "open")
		{
			string fname;
			int p = -1;
			cin >> fname;
			if (cnt_Afd < 5)
			{
				Users m = UFD[UFD_p].get_Users(loc);
				for (int i = 0; i < m.get_flength(); i++)
				{
					if (m.get_fnames(i) == fname)
					{
						p = i;
						break;
					}
				}
				if (p != -1)
				{
					Pc.push_back(m.get_Afd(p));
					cout << "成功打开" << endl;
					cnt_Afd++;
				}
				else
				{
					cout << "打开失败没有该文件" << endl;
				}
			}
			else
			{
				cout << "该系统能打开数量已满" << endl;
			}
		}
		else if (command == "close")
		{
			string fname;
			cin >> fname;
			if (cnt_Afd > 0)
			{
				bool F = 0;
				vector<Afd>::iterator it = Pc.begin();
				for (; it < Pc.end(); it++)
				{
					if (fname == it->get_opname())
					{
						Pc.erase(it);
						cout << "关闭成功" << endl;
						F = 1;
						cnt_Afd--;
						break;
					}
				}
				if (!F)
					cout << "未打开该文件" << endl;
			}
			else
			{
				cout << "关闭失败 没有任何打开文件" << endl;
			}
		}
		else if (command == "read")
		{
			string fname;
			int p = -1;
			cin >> fname;
			Users m = UFD[UFD_p].get_Users(loc);
			for (int i = 0; i < m.get_flength(); i++)
			{
				if (m.get_fnames(i) == fname)
				{
					p = i;
					break;
				}
			}
			if (p != -1 && check(fname)) 
			{
				Afd a = m.get_Afd(p);
				if (a.get_opfp(0))
				{
					cout << "成功读文件" << a.get_rwpoint() << endl;
				}
				else
				{
					cout << "读取失败权限不匹配" << endl;
				}
			}
			else
			{
				cout << "打开失败没有打开文件 或 不存在该文件" << endl;
			}
		}
		else if (command == "write")
		{
			string fname;
			int p = -1;
			cin >> fname;
			Users m = UFD[UFD_p].get_Users(loc);
			for (int i = 0; i < m.get_flength(); i++)
			{
				if (m.get_fnames(i) == fname)
				{
					p = i;
					break;
				}
			}
			if (p != -1 && check(fname))
			{
				Afd a = m.get_Afd(p);
				if (a.get_opfp(1))
				{
					cout << "成功写文件" << a.get_rwpoint() << endl;
				}
				else
				{
					cout << "写失败权限不匹配" << endl;
				}
			}
			else
			{
				cout << "打开失败没有该文件" << endl;
			}
		}
		else if (command != "exit")
		{
			cout << "command ERROR try again! or you can search help" << endl;
			continue;
		}
	}
}
void User()
{
	string command = "ERROR";
	while (command != "exit")
	{
		cout << "root\\" << UFD[UFD_p].get_uname() << "\\  ";
		cin >> command;
		if (command == "ls")
		{
			for (int i = 0; i < UFD[UFD_p].Size(); i++)
			{
				Users m = UFD[UFD_p].get_Users(i);
				if (m.get_flag())
				{
					SYSTEMTIME L;
					L = m.get_fdate();

					cout << setw(15) << "用户文件目录名" << setw(15) << "用户文件长度"
						<< setw(20) << "目录创建时间" << setw(15)<<"文件状态" << setw(15) << "逻辑地址" << endl;
					cout << setw(11) << m.get_Ufnames() << setw(15) << m.get_flength()
						<< setw(15) << L.wYear << "/" << L.wMonth << "/" << L.wDay
						<< "/" << L.wHour << ":" << L.wMinute << ":"
						<< L.wSecond << setw(10) << "r\\w\\e ";
					for (int j = 0; j < 3; j++)
					{
						if (j != 0)
							cout << "\\";
						cout << m.get_fp(j);
					}
					cout<< setw(10) << i << endl;
					for (int i = 0; i < m.get_flength(); i++)
					{
						cout << "-----------" << setw(15) << "用户文件名" << setw(15) << "逻辑地址" << endl;
						cout << setw(20) << m.get_fnames(i) << setw(15) << i << endl;
					}
					cout << endl;
				}
				else
				{
					cout << "该文件目录不存在" << endl;
				}
			}
		}
		else if (command == "dir")
		{
			string Ufname;
			int p = -1;
			cin >> Ufname;
			for (int i = 0; i < UFD[UFD_p].Size(); i++)
			{
				Users m = UFD[UFD_p].get_Users(i);
				if (m.get_Ufnames() == Ufname)
				{
					p = i;
					break;
				}
			}
			if (p != -1)
			{
				User_file(Ufname, p);
			}
			else
			{
				cout << "没有该用户文件" << endl;
			}
		}
		else if (command == "create" )
		{
			string Ufname;
			int fp;
			cin >> Ufname >> fp;
			Users m(Ufname, fp, 0);
			UFD[UFD_p].Push(m);
			cout << "Create Success" << endl;
		}
		else if (command == "delete")
		{
			string Ufname;
			cin >> Ufname;
			UFD[UFD_p].Delete(Ufname);
			cout << "Delet Success" << endl;
		}
		else if(command != "exit")
		{
			cout << "command ERROR try again! or you can search help" << endl;
			continue;
		}
	}
}
bool Login()
{
	string username, password;
	char temp[22];
	cout << "请输入用户名 : ";
	cin >> username;
	cout << "请输入密码: ";
	char c;
	int cnt = 0;
	while ((c = _getch()) != '\r') {
		if (c != '\b') {
			printf("#");
			temp[cnt] = c;
			cnt++;
		}
		else {
			printf("\b \b");
			cnt--;
		}
	}
	temp[cnt] = '\0';
	password = temp;
	cout << endl;
	getchar();
	for (int i = 0; i < cnt_UFD; i++)
	{
		if (username == UFD[i].get_uname() && password == UFD[i].get_password())
		{
			UFD_p = i;
			cout << "登录成功" << endl;
			return true;
		}
	}
	cout << "未查找到该用户" << endl;
	return false;
}
void system_work()//系统运行框架
{
	string command="ERROr";
	while (command != "exit")
	{
		cout << "nomal\\ ";
		cin >> command;
		if (command == "exit")
		{
			exit(0);
			return;
		}
		if (command == "su")
		{
			if (Login())
				User();
			else
				continue;
		}
		else
		{
			cout << "command ERROR try again!" << endl;
			continue;
		}
	}

}
void Newsystem()//初始化系统
{
	UFD[0].ch_uname("kevin");
	UFD[0].ch_password("812");
	UFD[1].ch_uname("stardust");
	UFD[1].ch_password("220");
	
	bool F = 0;
	Users x("dan", 0, 0);
	x.Push_fnames("12");
	Afd a("12", 0, 5);
	x.Push(a);
	a.~Afd();
	x.ch_flength();
	x.Push_fnames("13");
	Afd b("13", 1, 9);
	x.Push(b);
	b.~Afd();
	x.ch_flength();
	UFD[0].Push(x);
	
	F = 0;
	Users z("V", 1, 0);
	F = 0;
	z.Push_fnames("14");
	Afd c("14", 0, 18);
	z.Push(c);
	c.~Afd();
	z.ch_flength();
	z.Push_fnames("15");
	Afd d("15", 1, 10);
	z.Push(d);
	d.~Afd();
	z.ch_flength();
	UFD[0].Push(z);
	
	Users y("chen", 1, 0);
	y.ch_fp(0, 1);
	y.Push_fnames("20");
	Afd e("20", 0, 118);
	y.Push(e);
	e.~Afd();
	y.ch_flength();
	y.Push_fnames("21");
	Afd f("21", 1, 181);
	y.Push(f);
	f.~Afd();
	y.ch_flength();
	UFD[1].Push(y);
	cnt_UFD = 2;
}
int main()
{
	Newsystem();
	system_work();
}