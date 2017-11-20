#include <iostream>
using namespace std;

typedef struct lsnode
{
    int data;
    lsnode *next;
}*linklist;

void init(linklist &l)
{
    lsnode *t=new lsnode;
    t->next=NULL;
    l=t;
}

void adddata(linklist &l,int i)//带头结点
{
    lsnode *tail=l;
    lsnode *p;
    int data;
    for(int t=0;t<i;t++)
    {
        p=new lsnode;
        p->next=NULL;
        cin>>data;
        p->data=data;
        tail->next=p;
        tail=p;
    }
}

void show(linklist l)
{
    l=l->next;
    do
    {
        cout<<l->data<<" ";
        l=l->next;
    }while(l!=NULL);
    cout<<endl;
}

int main()
{
    linklist l;
    init(l);
    adddata(l,3);
    show(l);
    return 0;
}
