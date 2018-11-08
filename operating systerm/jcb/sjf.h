#pragma once
#include"jcb.h"
//最短作业优先
int fin = 0;
int cmp(const jcb a, const jcb b) {
	if (a.ts < b.ts)
		return 1;
	else
		return 0;
}
void sjf(jcb* head, int m) {
	int time2 = 0;//系统时间sjf

	jcb *p = head->next;
	time2 = tchange(p->tin);

	vector<jcb> jcbarray;
	for (int i = 0; i < m; i++)
	{
		jcb *now = p;
		jcbarray.push_back(*now);
		now = now->next;
	}
	sort(jcbarray.begin(), jcbarray.end(), cmp);

	while (fin < m)
	{
		vector<jcb>::iterator iter;
		for(iter=jcbarray.begin();iter!=jcbarray.end();iter++)
		{
			if ((*iter).state='w'&& tchange((*iter).tin) <= time2)
			{
				running((*iter),time2);
				fin++;
			}
		}
	}
	print(head);
}
