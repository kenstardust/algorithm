#include "Mdf.h"

Mdf::Mdf()
{

}
Mdf::Mdf(string uname, string password)
{
	this->uname = uname;
	this->password = password;
}
string Mdf::get_uname()
{
	return this->uname;
}
void Mdf::ch_uname(string uname)
{
	this->uname = uname;
}
string Mdf::get_password()
{
	return this->password;
}
void Mdf::ch_password(string password)
{
	this->password = password;
}
void Mdf::Push(Users t)
{
	que.push_back(t);
}
void Mdf::Delete(string fnames)
{
	vector<Users>::iterator it = que.begin();
	for ( ; it != que.end(); it++)
	{
		if (it->get_Ufnames() == fnames)
		{
			que.erase(it);
			return;
		}
	}
}
int Mdf::Size()
{
	return que.size();
}
Users Mdf:: get_Users(int p)
{
	return que[p];
}
void Mdf::ch_Users(Users m, int p)
{
	que[p] = m;
}
