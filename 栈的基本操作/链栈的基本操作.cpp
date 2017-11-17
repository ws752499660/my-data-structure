#include<iostream>
using namespace std;

typedef struct lsnode
{
	int data;
	lsnode *next;
}*linkstack;

void init(linkstack &s)
{
	lsnode *t=new lsnode;
	s=t;
	t->next=NULL;
}

int gettop(linkstack s)
{
	if(s->next==NULL) return 1;
	return s->next->data;
}

void push(linkstack &s, int e)
{
	lsnode *t=new lsnode;
	t->data=e;
	t->next=s->next;
	s->next=t;
}

int pop(linkstack &s)
{
	if(s->next==NULL) return 1;
	int t=s->next->data;
	lsnode *p=s->next;
	s->next=p->next;
	delete p;
	return t;
}

int length(linkstack &s)
{
	if(s->next==NULL) return 0;
	int j=0;
	lsnode *t=s;
	while(s->next!=NULL)
	{
		s=s->next;
		j++;
	}
	s=t;
	return j;
}

int main()
{
	linkstack s;
	int e;
	init(s);
	for(int i=0;i<5;i++)
	{
		cin>>e;
		push(s,e);
	}
	cout<<length(s)<<endl;
	cout<<gettop(s)<<endl;
	for(i=0;i<5;i++)
		cout<<pop(s)<<" ";
	cout<<endl;
	cout<<length(s)<<endl;
	return 0;
}