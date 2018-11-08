#pragma once
#include"jcb.h"

//先来先服务
void fcfs(jcb* head, int m) {
	int time = 0;//系统时间fxfs
	time = head->tin.hour * 60 + head->tin.min;//系统此时的时间
	jcb* cur = head->next;
	for (int i = 0; i < m; i++) {
		jcb* p = cur;
		int tp = p->tin.hour * 60 + p->tin.min;
		if (p->state == 'w' && tp <= time)
			running(*p,time);
		cur = p->next;
	}
	print(head);
}