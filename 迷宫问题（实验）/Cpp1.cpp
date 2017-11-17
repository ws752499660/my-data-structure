#include<iostream>
using namespace std;

int q[11][10]={{1,1,1,1,1,1,1,1,1,1},{1,0,0,1,0,0,0,1,0,1},{1,0,0,1,0,0,0,1,0,1},
{1,0,0,0,0,1,1,0,1,1},{1,0,1,1,1,0,0,1,0,1},{1,0,0,0,1,0,0,0,0,1},{1,0,1,0,0,0,1,0,1,1},
{1,0,1,1,1,1,0,0,1,1},{1,1,1,0,0,0,1,0,1,1},{1,1,1,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1}};

typedef struct lsnode
{
	int h,l,d;
	lsnode *next;
}*linkstack;

void init(linkstack &s)
{
	lsnode *t=new lsnode;
	t->next=NULL;
	s=t;
}

void push(linkstack &s,int e1,int e2,int e3)
{
	lsnode *t=new lsnode;
	t->h=e1;
	t->l=e2;
	t->d=e3;
	t->next=s->next;
	s->next=t;
}

void pop(linkstack &s,int &e1,int &e2,int &e3)
{
	lsnode *t;
	t=s->next;
	e1=t->h;
	e2=t->l;
	e3=t->d;
	s->next=t->next;
	delete t;
}

void del(linkstack &s)
{
	lsnode *t;
	t=s->next;
	s->next=t->next;
	delete t;
}

int length(linkstack s)
{
	lsnode *t;
	t=s;
	int i=0;
	while(s->next!=NULL)
	{
		i++;
		s=s->next;
	}
	s=t;
	return i;
}


int judge(linkstack &s,int &i,int &j)
{
	if(s->next->d==1 && q[i][j+1]==0)
	{
		j++;
		return 1;
	}
	if(s->next->d==2 && q[i+1][j]==0)
	{
		i++;
		return 1;
	}
	if(s->next->d==3 && q[i][j-1]==0)
	{
		j--;
		return 1;
	}	
	if(s->next->d==4 && q[i-1][j]==0)
	{
		i--;
		return 1;
	}
	return 0;
}

void guide(linkstack &s,int &i,int &j)
{
	if(judge(s,i,j))	
	{
		push(s,i,j,1);
		q[i][j]=1;
	}
	else
		if(s->next->d<=4)
			s->next->d=s->next->d+1;
		else
		{
			del(s);
			i=s->next->h;
			j=s->next->l;
			q[i][j]=1;
		}
}

int main()
{
	linkstack s;
	init(s);
	int i=1,j=1,g=1;
	push(s,i,j,g);
	do
	{
		guide(s,i,j);
	}while(i!=9 || j!=8);
	linkstack t;
	init(t);
	do
	{
		pop(s,i,j,g);
		push(t,i,j,g);
	}while(s->next);
	while(t->next!=NULL)
	{
		i=t->next->h;
		j=t->next->l;
		g=t->next->d;
		cout<<"("<<i<<","<<j<<","<<g<<")"<<" ";
		del(t);
		cout<<endl;
	}
	return 0;
}