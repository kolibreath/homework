#pragma once
#include"jcb.h"

//�����ȷ���
void fcfs(jcb* head, int m) {
	int time = 0;//ϵͳʱ��fxfs
	time = head->tin.hour * 60 + head->tin.min;//ϵͳ��ʱ��ʱ��
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