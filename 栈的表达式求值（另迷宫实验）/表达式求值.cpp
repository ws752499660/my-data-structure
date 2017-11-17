#include<iostream>
#include<cmath>
using namespace std;

typedef struct lsnode
{
	char date;
	int num;
	lsnode *next;
}*linkstack;

void initstack(linkstack &s)
{
	lsnode *t=new lsnode;
	t->next=NULL;
	s=t;
}

char gettop(linkstack s)
{
	return s->next->date;
}

int gettopn(linkstack s)
{
	return s->next->num;
}

void del(linkstack &s)
{
	lsnode *t=s->next;
	s->next=s->next->next;
	delete t;
}

void push(char c,int n,linkstack &s)
{
	lsnode *t=new lsnode;
	t->date=c;
	t->num=n;
	t->next=s->next;
	s->next=t;
}

void pop(char &c,int &n,linkstack &s)
{
	lsnode *t;
	t=s->next;
	s->next=s->next->next;
	c=t->date;
	n=t->num;
	delete t;
}

int opra(char o,int a,int b)
{
	switch(o)
	{
	case'+':return a+b;
	case'-':return a-b;
	case'*':return a*b;
	case'/':return a/b;
	}
}

char per(linkstack s,char c)
{
	if(c=='+' || c=='-')
	{
		if(gettop(s)=='+' || gettop(s)=='-' || gettop(s)==')' || gettop(s)=='*' || gettop(s)=='/')
			return '>';
		if(gettop(s)=='(' || gettop(s)=='#')
			return '<';
	}
	if(c=='*' || c=='/')
	{
		if(gettop(s)==')' || gettop(s)=='*' || gettop(s)=='/')
			return '>';
		if(gettop(s)=='(' || gettop(s)=='#' || gettop(s)=='+' || gettop(s)=='-')
			return '<';
	}
	if(c=='(')
		if(gettop(s)=='+' || gettop(s)=='-' || gettop(s)=='(' || gettop(s)=='*' || gettop(s)=='/' || gettop(s)=='#')
			return '<';
	if(c==')')
	{
		if(gettop(s)=='+' || gettop(s)=='-' || gettop(s)=='*' || gettop(s)=='/' || gettop(s)=='#')
			return '>';
		if(gettop(s)=='(')
			return '=';
	}
	if(c=='#')
	{
		if(gettop(s)=='+' || gettop(s)=='-' || gettop(s)=='(' || gettop(s)=='*' || gettop(s)=='/')
			return '>';
		if(gettop(s)=='#')
			return '=';
	}
}

void getnext(char &c1,linkstack &opr,linkstack &num)
{
	/*if(c1<'0' || c1>'9')
	{
		push(c1,0,opr);
	}
	else
	{*/
		linkstack s;
		initstack(s);
		int n=c1-'0';
		int i=0,t;
		push(0,n,s);
		while(1)
		{
			c1=getchar();
			if(c1>='0' && c1<='9')
			{
				n=c1-'0';
				push(0,n,s);
			}
			else
			{
				//ungetc(c1,stdin);
				break;
			}
		}
		n=0;
		while(s->next)
		{
			char ads;
			pop(ads,t,s);
			n=n+t*pow(10,i);
			i++;
		}
		push(0,n,num);
	//}
}

void calculate(linkstack &num,linkstack &opr,char &c)
{
	if(c>='0' &&  c<='9')
	{
		getnext(c,opr,num);
	}
	else
	{
		if(per(opr,c)=='>')
		{
			char o;
			int q=0;
			pop(o,q,opr);
			q=opra(o,num->next->next->num,num->next->num);
			del(num);
			del(num);
			push(0,q,num);
			if(per(opr,c)=='=')
			{
				del(opr);
				c=getchar();
				return;
			}
			c=getchar();
			return;
		}
		if(per(opr,c)=='<')
		{
			push(c,0,opr);
			c=getchar();
			return;
		}
		if(per(opr,c)=='=')
		{
			del(opr);
			c=getchar();
			return;
		}
	}
}

int main()
{
	linkstack num,opr;
	initstack(num);
	initstack(opr);
	push('#',1,opr);
	char c=getchar();
	do//while(c!='#' || gettop(opr)!='#')
	{
		calculate(num,opr,c);
	}while(c!='\n');
	cout<<gettopn(num)<<endl;
	return 0;
}