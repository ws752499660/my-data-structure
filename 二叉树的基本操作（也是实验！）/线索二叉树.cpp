#include <iostream>
#include <cstdio>
using namespace std;

typedef struct btnode
{
    int data;
    btnode *lk,*rk;
    int ltype,rtype;  //type=0--link（有孩子）, type=1--thread（有线索）
}*bitree;

void creatbt(bitree &b)
{
    char c=getchar();
    if(c=='#')
        b=NULL;
    else
    {
        int n = c - '0';
        btnode *t = new btnode;
        t->data=n;
        b=t;
        creatbt(b->lk);
        creatbt(b->rk);
    }
}

void visit(btnode *b)
{
    cout<<b->data<<" ";
}

void travel(bitree b)
{
    if(b)
    {
        travel(b->lk);
        visit(b);
        travel(b->rk);
    }
}

void inthread(bitree &b,btnode* &pre) //中序线索化二叉树（核心递归部分）
{
    if(b)
    {
        inthread(b->lk,pre);
        if(!b->lk)
        {
            b->ltype=1;
            b->lk=pre;
        }
        else
            b->ltype=0;
        if(!pre->rk)
        {
            pre->rtype=1;
            pre->rk=b;
        }
        else
            pre->rtype=0;
        pre=b;
        inthread(b->rk,pre);
    }
}

void thread(bitree &thrt,bitree &b)  //中序线索化二叉树（头结点部分）
{
    if(b->lk)
        b->ltype=0;
    else
        b->ltype=1;
    if(b->rk)
        b->rtype=0;
    else
        b->rtype=1;
    thrt=new btnode;
    thrt->ltype=0;
    thrt->rtype=1;
    thrt->rk=thrt;
    if(!b)
        thrt->lk=thrt;
    else
    {
        thrt->lk=b;
        btnode *pre=thrt;
        inthread(b,pre);
        pre->rk=thrt;
        pre->rtype=1;
        thrt->rk=pre;
    }

}

void threadtravel(bitree tb)
{
    btnode *t=tb->lk;
    while(t!=tb)
    {
        while(t->ltype==0)
        {t=t->lk;}
        visit(t);
        while(t->rtype==1 && t->rk!=tb)
        {
            t=t->rk;
            visit(t);
        }
        t=t->rk;
    }
}

int main()
{
    bitree b,tb;
    creatbt(b);
    travel(b);
    cout<<endl;
    thread(tb,b);
    threadtravel(tb);
    cout<<endl;
    return 0;
}
