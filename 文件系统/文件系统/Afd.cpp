#include "Afd.h"

Afd::Afd()
{

}
Afd::Afd(string opname, int opfp, int rwpoint)
{
	this->opnames = opname;
	this->flag = 1;
	this->opfprotect[opfp] = 1;
	this->rwpoint = rwpoint;
}
string Afd::get_opname()
{
	return this->opnames;
}
void Afd::ch_opname(string opnames)
{
	this->opnames = opnames;
}
int Afd::get_flag()
{
	return this->flag;
}
void Afd::ch_flag(int flag)
{
	this->flag = flag;
}
int Afd::get_opfp(int p)
{
	return this->opfprotect[p];
}
void Afd::ch_opfp( int p)
{
	this->opfprotect[p] = 1;
}
int Afd::get_rwpoint()
{
	return this->rwpoint;
}