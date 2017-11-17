#include<iostream>
using namespace std;

const int q[11][10]={{1,1,1,1,1,1,1,1,1,1},{1,0,0,1,0,0,0,1,0,1},{1,0,0,1,0,0,0,1,0,1},
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

void pop(linkstack &s,int e1,int e2,int e3)
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

void guide(int &i,int &j,linkstack &s,int g)
{
	if(g==1)
			push(s,i,++j,g);
	if(g==2)
			push(s,++i,j,g);
	if(g==3)
			push(s,i,--j,g);
	if(g==4)
			push(s,--i,j,g);
	/*case'5':
		{
			del(s);
		}*/
}

int findway(linkstack &s)
{
	int i=s->next->h;
	int j=s->next->l;
	if(q[i][++j]==0) 
		return 1;
	if(q[++i][j]==0)
		return 2;
	if(q[i][--j]==0)
		return 3;
	if(q[--i][j]==0)
		return 4;
	return 5;
}

int main()
{
	linkstack s;
	init(s);
	int i=1,j=1,g=1;
	push(s,i,j,g);
	do
	{
		int t=findway(s);
		guide(i,j,s,t);
		//cout<<length(s)<<" ";
	}while(i!=8 || j!=9);
	while(s->next!=NULL)
	{
		i=s->next->h;
		j=s->next->l;
		g=s->next->d;
		cout<<"("<<i<<","<<j<<","<<g<<")"<<" ";
		del(s);
	}
	cout<<endl;
	return 0;
}