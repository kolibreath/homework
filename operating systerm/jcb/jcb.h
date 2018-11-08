#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
struct T {
	int hour;
	int min;
};
struct jcb {
	char name[10];//jcb name
	char state;//状态
	float super;//优先级
	int ts;//估计运行时间
	T tin;//进入时间
	T tend;//运行结束时间
	T tstart;//运行开始时间
	float ti;//周转时间
	float wi;//带权周转时间
	jcb *next;//链指针6
};
	
void running(jcb p,int time0) {
	cout << "running" << p.name << endl;
	int t = time0 / 60;
	int m = time0 % 60;
	p.tstart.hour = t;
	p.tstart.min = m;
	p.state = 'r';
	time0 += p.ts;
	int pin = p.tin.hour * 60 + p.tin.min;
	p.ti =(float) (time0 - pin);

	int hour = time0 / 60;
	int min = time0 % 60;
	p.tend.hour = hour;
	p.tend.min = min;
	
	}
void print(jcb* head) {
	jcb* cur = head->next;
	while (cur != NULL) {
		cout << "name  " << cur->name << endl;
		cout<< "进入系统时间" << cur->tin.hour << ":" << cur->tin.min << endl;
		cout << "开始运行时间" << cur->tstart.hour << ":" << cur->tstart.min << endl;
		cout << "周转时间" << cur->ti << endl;
		cout << "运行结束时间" << cur->tend.hour << ":" << cur->tend.min << endl;

		cur = cur->next;
	}
}

int tchange(T t) {
	return t.hour * 60 + t.min;
}