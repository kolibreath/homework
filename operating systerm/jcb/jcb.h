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
	char state;//״̬
	float super;//���ȼ�
	int ts;//��������ʱ��
	T tin;//����ʱ��
	T tend;//���н���ʱ��
	T tstart;//���п�ʼʱ��
	float ti;//��תʱ��
	float wi;//��Ȩ��תʱ��
	jcb *next;//��ָ��6
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
		cout<< "����ϵͳʱ��" << cur->tin.hour << ":" << cur->tin.min << endl;
		cout << "��ʼ����ʱ��" << cur->tstart.hour << ":" << cur->tstart.min << endl;
		cout << "��תʱ��" << cur->ti << endl;
		cout << "���н���ʱ��" << cur->tend.hour << ":" << cur->tend.min << endl;

		cur = cur->next;
	}
}

int tchange(T t) {
	return t.hour * 60 + t.min;
}