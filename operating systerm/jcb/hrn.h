
#pragma once
#include"jcb.h"
#include<algorithm>
using namespace std;
void hrn(jcb* head, int m) {
	int time3 = 0;//系统时间hrn

	jcb *p = head->next;
	time3 = tchange(p->tin);
	int fin = 0;
	jcb* q = p;
	while (fin < m)
	{
		vector<int> ra;
		for (int i = 0; i < m; i++)
		{
			int tq = tchange(q->tin);//p进入系统的时间
			if (q->state = 'w' && time3 <= tq)
			{
				ra.push_back(ratio(time3, tq,q->ts));
			}
		}
		int index = *max_element(ra.begin(), ra.end());//求vector中的最大值

		jcb* l = p;
		for (int k = 0; k <= index; k++) {
			l = l->next;
		}
		running(*l,time3);
		q = q->next;

	}
	print(head);
}
int ratio(int now,int in,int yun) {//now 此时系统时间，in 进入系统时间，yun 需要的运行时间
	return (1 + (now - in) / yun);
}