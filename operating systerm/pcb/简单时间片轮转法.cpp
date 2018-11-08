#include<iostream>
#include<algorithm>

using namespace std;

struct Time {
	int h;
	int m;
};
struct pcb {
	char name[10];
	char state;
	int super;
	Time ntime;//进入时间
	int rtime;//运行时间长度
	int fintime;//已经运行的时长
	int wtime;//运行周转时间
	struct pcb* next;

	Time endtime;//结束时间
}
*ready = NULL, *p;
int n;//进程总的个数
void init() {
	cout << "please inpur the nunm of pcb";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "NO." << i << endl;
		cout << "please input name-state-super-ntime.H-ntime.M-rtime-fintime" << endl;
		cin >> p->name;
		cin >> p->state;
		cin>> p->super;
		cin >> p->ntime.h;
		cin >> p->ntime.m;
		cin >> p->rtime;
		cin>> p->fintime;
	}
	p = ready;//p指向队列的最开始位置
}
void turntime() {
	int pt;
	cout << "please input the time ";
	cin >> pt;
	int fullt = 0;//系统运行时间
	Time first = ready->ntime;
	int finish = 0;//记录完成的进程个数
	while (finish <= n) {
		pcb *cur;
		pcb *q = ready;
		for (int i = 0; i < n; i++) {
			fullt += pt;//系统运行时间加
			cur = q;
			if (cur->state == 'w') {
				cur->fintime += pt;
				if (cur->fintime >= cur->rtime)
				{
					cur->state = 'f';
					finish++;
					cur->endtime = maketime(first,fullt);
					//第一个进入的时间加上系统已经运行的时间等于此刻的时间
					cur->wtime = wait(cur->ntime, cur->endtime);
					//运行周转时间
				}
			}
			else {
				q = q->next;
			}
		}
	}
}
void show() {
	pcb *cur;
	cur = ready;
	for (int i = 0; i < n; i++)
	{
		cout << "name" << cur->name << "state" << cur->state << "intime" << cur->ntime.h << ":" << cur->ntime.m << "runtime" << cur->rtime << "waittime" << cur->wtime << "endtime" << cur->endtime.h << ":" << cur->endtime.m << endl;
		cur = cur->next;
	}
}
Time maketime(Time a, int b) {
	Time t;
	t.m = (a.m + b % 60) % 60;
	t.h = a.h + b / 60 + (a.m + b % 60) / 60;
	return t;
}

int wait(Time a, Time b) {
	int ah = a.h;
	int am = a.m;
	int bh = b.h;
	int bm = b.m;
	return ((bh * 60 + bm) - (ah * 60 + am));
}


int main() {
	init();
	turntime();
	show();
	return 0;
}