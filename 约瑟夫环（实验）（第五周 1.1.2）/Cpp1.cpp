#include<iostream>
using namespace std;

struct linklist
{
	int code;
	int num;
	linklist *next;
};

linklist *creat(int n) //����һ����ͷ����ѭ������
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

linklist *del_behind(linklist *l)  //ɾ������������һ�����
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
		for(int i=0;i<n-1;i++) //ʹ��lָ�����������һ����㣬ʹ��һ��forѭ����l->nextָ��ǰ����ĵ�һ�����
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