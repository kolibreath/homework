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
	struct pcb* next;

	Time endtime;//结束时间
}
*ready=NULL,*p;

//将pcb按顺序放入ready队列
void sort(){
	pcb* first, *second;
	int insert = 0;
	if (ready == NULL || (p->super > ready->super))//优先级大插在队列首
	{
		p->next = ready;
		ready = p;
	}
	else {
		first = ready;
		second = first->next;
		while (second != NULL) {
			if (p->super < second->super)
			{
				first = first->next;
				second = second->next;
			}
			else
			{
				first->next = p;
				p->next = second;
			}
		}
	}
}
void init() {
	cout << "please inpur the nunm of pcb";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		cout << "NO." << i << endl;
		cout << "please input name-state-super-ntime-rtime" << endl;
		cin >> p->name >> p->state >> p->super >> p->ntime.h>>p->ntime.m>> p->rtime;

		sort();
	}
	p = ready;//p指向队列的最开始位置
}

Time maketime(Time a, int b) {
	Time t;
	t.m = (a.m + b % 60)%60;
	t.h = a.h + b / 60 + (a.m + b % 60) / 60;
	return t;
}

void check() {
	cout << "现在运行的是" << p->name << endl;
	cout << "优先级为" << p->super << endl;
}
void run() {
	p->state = 'r';
	p->endtime = maketime(p->ntime, p->rtime);
	check();
}
void dispatch() {
	while (p!=NULL)
	{
		run();
		if(p->next!=NULL)
		p = p->next;
	}
}


int main() {
	init();
	dispatch();

	return 0;
}