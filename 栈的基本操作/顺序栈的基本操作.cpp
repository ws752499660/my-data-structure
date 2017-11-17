#include<iostream>
using namespace std;

struct sqstack
{
	int *base,*top;
	int size;
};

void initstack(sqstack &s,int n)
{
	s.size=n;
	s.base=new int[s.size];
	s.top=s.base;
}

int gettop(sqstack s)
{
	return *(s.top-1);
}

void push(sqstack &s,int e)
{
	if((s.top-s.base)>=s.size)
		return;
	*s.top=e;
	s.top++;
}

int pop(sqstack &s)
{
	if(s.top==s.base) return 0;
	int t=*(s.top-1);
	s.top--;
	return t;
}

int length(sqstack s)
{
	return (s.top-s.base);
}

int main()
{
	sqstack s;
	int e;
	initstack(s,7);
	for(int i=0;i<5;i++)
	{
		cin>>e;
		push(s,e);
	}
	cout<<gettop(s)<<endl;
	cout<<length(s)<<endl;
	for(i=0;i<5;i++)
	{
		cout<<pop(s)<<" ";
	}
	cout<<endl<<length(s)<<endl;
	return 0;
}