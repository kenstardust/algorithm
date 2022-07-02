#include<iostream>
#include<queue>
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
#include <iomanip>
using namespace std;
const int N = 7;//数据数量
const int TIME = 10;
const int LIM_PCB = 5;  //每级队列仅允许五个进程
const int LIM_QUE = 4; //四级队列
struct DWORK {
	int pid = -1; //任务编号
	int pri = -1;//优先级
	int arr = 0;//到达时间
	int rest = 0;//剩余时间
	int begin = 0;//开始时间
	int end = 0;//终止时间
	string d = "W";//运行状态 F 结束 W等待 R运行
	inline bool operator < (const DWORK& a) const
	{
		return !(pri < a.pri);
	}
};
bool cmp(DWORK a, DWORK b)
{
	return a.arr < b.arr;
}
vector<queue<DWORK>>PC;//队列集合
vector<int>Left[6];//记录作业完成情况
DWORK dw[10];
int vis[8];//每集队列有多少的PCB 
void load()//加载作业
{
	for (int i = 1; i <= N; i++)
	{
		PC[dw[i].pri].push(dw[i]);
		Left[dw[i].pri].push_back(i);
	}
}
void Show_working(DWORK m,int current,int T,int Cpu_t)
{
	static int P=-1;
	if (T != P)
	{
		cout << "-----------------------第" << T + 1 << "列处理中-------------------------------" << endl;
		P = T;
	}
	cout << "正在处理任务" << m.pid << "\t剩余时间" << m.rest << "\t到达时间" << m.arr << "\t时间片" << Cpu_t << "\t状态" << 'R' << endl;
}
void work(DWORK m,int &current,int T)
{
	int k = TIME;
	int loc = 0;
	for (int i = 1; i <= N; i++)//查找数据逻辑位置
	{
		if (dw[i].pid == m.pid)
		{
			loc = i;
			break;
		}
	}
	if (current <= dw[loc].arr) //刷新时间
	{
		current = dw[loc].arr;
	}
	if (T != 0)//计算当前CPU片时间
	{
		for (int i = 1; i <= T; i++)
		{
			k *= 2;
		}
	}
	if (m.rest <= k)
	{
		Show_working(dw[loc],current,T,k);
		dw[loc].begin = current;
		current += dw[loc].rest;
		dw[loc].rest = 0;
		dw[loc].end = current;
		dw[loc].d = 'F';
	}
	else
	{
		Show_working(dw[loc], current, T, k);
		dw[loc].begin = current;
		current += k;
		dw[loc].rest -= k;
		dw[loc].d = 'W';
		PC[T + 1].push(dw[loc]);
		Left[T + 1].push_back(loc);
	}

}
void Show_work(int l,int T)
{
	if (l == 1)
	{
		cout << "-----------------------第" << T + 1 << "列-------------------------------" << endl;
		for (int i = 0; i < Left[T].size(); i++)
		{
			cout << "任务" << dw[Left[T][i]].pid << "\t剩余时间" << dw[Left[T][i]].rest << "\t到达时间" << dw[Left[T][i]].arr
				<< "\t时间片" << "\t状态" << 'W' << endl;

		}
	}
	else
	{
		cout << "-----------------------第" << T + 1 << "列任务结束-----------------------" << endl;
		for (int i = 0; i < Left[T].size(); i++)
		{
			cout << "任务" << dw[Left[T][i]].pid << "\t剩余时间" << dw[Left[T][i]].rest << "\t到达时间" << dw[Left[T][i]].arr
				<< "\t状态" << dw[Left[T][i]].d << endl;
		}
		cout << endl << endl;
	}
}
void IR()
{
	int current = dw[1].arr;//初始化CPU时间
	for (int i = 0; i < PC.size(); i++)
	{
		Show_work(1,i);
		while (!PC[i].empty())
		{
			DWORK m = PC[i].front();
			PC[i].pop();
			work(m, current,i);
		}
		Show_work(2,i);
	}
}
void Show_dw()
{
	cout << setw(15) <<"PID 序号" << setw(15) << "优先级" << setw(15) << "到达时间" << setw(15) << "作业所需时间" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << setw(15) <<dw[i].pid << setw(15) << dw[i].pri << setw(15) << dw[i].arr << setw(15) << dw[i].rest << endl;
	}
}
void Show_end_dw()
{
	cout << "-----------------------任务结束-------------------------------" << endl;
	cout << setw(15) <<"序列号：" << setw(15) << "到达时间:" << setw(15) << "开始时间：" << setw(15) << "结束时间：" << setw(15) <<"优先级：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << setw(15) << dw[i].pid << setw(15) << dw[i].arr << setw(15) << dw[i].begin << setw(15) << dw[i].end << setw(15) << dw[i].pri << endl;
	}
}
int main()
{
	for (int i = 1; i <= 4; i++)
	{
		queue<DWORK>que0;
		PC.push_back(que0);
	}
	for (int i = 1; i <= N; i++)
	{
		DWORK a;
		cin  >> a.pid >>a.arr >> a.rest >> a.pri;
		dw[i] = a;
	}
	Show_dw();
	sort(1 + dw, 1 + N + dw,cmp);
	load();
	IR();
	Show_end_dw();
}