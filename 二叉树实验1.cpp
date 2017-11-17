#include<iostream>
using namespace std;

typedef struct btnode
{
	char date;
	btnode *lc,*rc;
}*bitree;

typedef struct lsnode
{
	bitree date;
	lsnode *next;
}*linkstack;

void initbitree(bitree &b)
{
	btnode *t=new btnode;
	t->date=0;
	t->lc=NULL;
	t->rc=NULL;
	b=t;
}

void creatbt(bitree &b)
{
	char c=getchar();
	if(c=='#')
		b=NULL;
	else
	{
		int t=c;
		b=new btnode;
		b->date=t;
		creatbt(b->lc);
		creatbt(b->rc);
	}
}

void initlinkstack(linkstack &l)
{
	lsnode *t=new lsnode;
	t->next=NULL;
	l=t;
}

void push(linkstack &l,btnode *b)
{
	lsnode *t=new lsnode;
	t->date=b;
	t->next=l->next;
	l->next=t;
}

int gettop(linkstack &l,bitree &b)
{
	if(b=l->next->date)
		return 0;
	else
		return 1;
}

void pop(linkstack &l,bitree &b)
{
	lsnode *t=l->next;
	l->next=l->next->next;
	b=t->date;
}

int checkempty(linkstack l)
{
	if(l->next)
		return 0;
	else
		return 1;
}

void visit(btnode *b)
{
	cout<<b->date<<" ";
}

void pretraver(bitree &b) //Ç°Ğò¶ş²æÊ÷µİ¹é±éÀú
{
	if(b)
	{
		visit(b);
			pretraver(b->lc);
			pretraver(b->rc);
	}
}

void midtraver(bitree &b)//ÖĞĞò¶ş²æÊ÷µİ¹é±éÀú
{
	if(b)
	{
		midtraver(b->lc);
		visit(b);
		midtraver(b->rc);
	}
}

void afttraver(bitree &b)//ºóĞò¶ş²æÊ÷µİ¹é±éÀú
{
	if(b)
	{
		afttraver(b->lc);
		afttraver(b->rc);
		visit(b);
	}
}

void midtraver_normal(bitree &b)//ÖĞĞò·Çµİ¹é±éÀú¶ş²æÊ÷
{
	linkstack l;
	bitree bt=b;
	initlinkstack(l);
	while(bt||!checkempty(l))
	{
		if(bt)
		{
			push(l,bt);
			bt=bt->lc;
		}
		else
		{
			pop(l,bt);
			visit(bt);
			bt=bt->rc;
		}
	}
}

int main()
{
	bitree b;
	initbitree(b);
	creatbt(b);
	pretraver(b);
	cout<<endl;
	midtraver(b);
	cout<<endl;
	afttraver(b);
	cout<<endl;
	midtraver_normal(b);
	cout<<endl;
	return 0;
}