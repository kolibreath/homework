#include"jcb.h"
#include"fcfs.h"
#include"hrn.h"
#include"sjf.h"
#include<iostream>
using namespace std;

int main() {
	jcb* head;
	int n;
	cout << "please input the number of the job";
	cin >> n;
	
	jcb *cur = new jcb;
	cur = head;

	for (int i = 0; i < n; i++) {

		jcb *p = new jcb;
		if (i == 0)
			head->next = p;
		cur->next = p;
		cur = p;

		cout << "name";
		cin >> p->name;
		cout << "tin 进入时间 h-m" << endl;
		int a, b;
		cin >> a >> b;
		p->tin.hour = a;
		p->tin.min = b;

		cout << "state" << endl;
		cout << "r-run  w-wait  p-prepar" << endl;
		p->state = 'w';

		cout << "ts估计运行时间" << endl;
		cin >> p->ts;
	}

	fcfs(head,n);
	sjf(head, n);
	hrn(head, n);
}