#include "Users.h"

Users::Users()
{

}
Users::Users(string Ufnames, int fp, int flength)
{
	if (flength + 1 >= Limt)
	{
		cout << "ERROR 该用户系统文件已满" << endl;
		return;
	}
	this->Ufnames = Ufnames;
	this->flag = 1;
	this->fprotected[fp] = 1;
	GetLocalTime(&fdate);
	this->flength = flength;
}
string Users::get_fnames(int t)//重载更新用户下的文件集名字 
{
	return fnames[t];
}
void Users::Push_fnames(string fnames)
{
	this->fnames.push_back(fnames);
}
string Users::get_Ufnames()//该目录用户文件夹名
{
	return this->Ufnames;
}
bool Users::ch_Ufnames(string fnames)//更新目录用户文件夹名
{
	this->Ufnames = fnames;
	if (fnames == this->Ufnames)
		return true;
	else
		return false;
}
int Users::get_flag()
{
	return flag;
}
bool Users::ch_flag(int flag)
{
	this->flag = flag;
	if (flag == this->flag)
		return true;
	else
		return false;
}
int Users::get_fp(int t)
{
	return this->fprotected[t];
}
bool Users::ch_fp(int p,int c)//位置 状态
{
	this->fprotected[p] = c;
	if (this->fprotected[p] == c)
		return true;
	else
		return false;
}
SYSTEMTIME Users::get_fdate()
{
	return fdate;
}
bool Users::ch_fdate()
{
	GetLocalTime(&fdate);
	return true;
}
int Users::get_flength()
{
	return this->que.size();
}
bool Users::ch_flength()
{
	this->flength = que.size();
	return true;
}
Afd Users::get_Afd(int p)
{
	return que[p];
}
void Users::ch_Afd(Afd m, int p)
{
	que[p] = m;
}
void Users::Push(Afd m)
{
	que.push_back(m);
}
bool Users::Delete(string fname)
{
	vector<Afd>::iterator it = que.begin();
	auto it2 = fnames.begin();
	for (; it < que.end() && it2 < fnames.end(); it++, it2++)
	{
		if (it->get_opname() == fname)
		{
			this->que.erase(it);
			this->fnames.erase(it2);
			return true;
		}
	}
	return false;
}