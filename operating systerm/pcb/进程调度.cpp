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
	Time ntime;//����ʱ��
	int rtime;//����ʱ�䳤��
	struct pcb* next;

	Time endtime;//����ʱ��
}
*ready=NULL,*p;

//��pcb��˳�����ready����
void sort(){
	pcb* first, *second;
	int insert = 0;
	if (ready == NULL || (p->super > ready->super))//���ȼ�����ڶ�����
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
	p = ready;//pָ����е��ʼλ��
}

Time maketime(Time a, int b) {
	Time t;
	t.m = (a.m + b % 60)%60;
	t.h = a.h + b / 60 + (a.m + b % 60) / 60;
	return t;
}

void check() {
	cout << "�������е���" << p->name << endl;
	cout << "���ȼ�Ϊ" << p->super << endl;
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