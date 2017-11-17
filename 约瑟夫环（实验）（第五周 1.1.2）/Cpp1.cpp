#include<iostream>
using namespace std;

struct linklist
{
	int code;
	int num;
	linklist *next;
};

linklist *creat(int n) //创建一个无头结点的循环链表
{
	linklist *l,*s,*r;
	l=new linklist;
	cin>>l->code;
	l->num=1;
	l->next=NULL;
	r=l;
	for(int i=1;i<n;i++)
	{
		s=new linklist;
		cin>>s->code;
		s->num=i+1;
		s->next=NULL;
		r->next=s;
		r=s;
	}
	r->next=l;
	return l;
}

linklist *del_behind(linklist *l)  //删除该链表结点后的一个结点
{
	linklist *r;
	r=l->next->next;
	delete l->next;
	l->next=r;
	l=l->next;
	return l;
}

int main()
{
	linklist *l,*t;
	int m=20,n=7;
	l=new linklist;
	l=creat(n);
	t=l;
	while(l->next!=l)
	{
		for(int i=0;i<n-1;i++) //使得l指向链表中最后一个结点，使下一个for循环的l->next指向当前链表的第一个结点
			l=l->next;
		
		for(i=1;i<m;i++)
			l=l->next;
		
		m=(l->next)->code;
		cout<<l->next->num<<" ";
		
		//if(l->next!=l)		
		//{
			/*linklist *r;
			r=(l->next)->next;
			delete l->next;
			l->next=r;
			l=l->next;*/
		//}

		l=del_behind(l);

		n--;
	}
	cout<<l->num;
	cout<<endl;
	return 0;
}