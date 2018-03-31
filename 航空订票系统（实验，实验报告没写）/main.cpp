#include <iostream>
#include <string>
using namespace std;

struct customer
{
    string name;
    long long phone;
    int sum=0;  //单个人定了几张票
    int airclass;
    long long order; //订单号
};

typedef struct custnode
{
    customer data;
    int need=0; //所需票量
    custnode *next;
}*custlist;

struct airline
{
    string end;
    string airnum;
    string plane;
    string day;
    int customernum;    //乘客定额
    int leftticket;
    custlist customer_list=NULL; //乘客名单
    custlist b_customer_list=NULL;   //候补乘客名单
};

typedef struct alnode
{
    airline data;
    alnode *next;
}*allist;

void create_airline_list(allist &airline_list)
{
    char ans='Y';
    airline_list=new alnode;
    alnode *p=airline_list;
    while(ans=='Y')
    {
        alnode *t=new alnode;
        cin >> t->data.end;
        cin >> t->data.airnum;
        cin >> t->data.plane;
        cin >> t->data.day;
        cin >> t->data.customernum;
        t->data.leftticket = t->data.customernum;
        t->data.customer_list=NULL;
        t->next=NULL;
        p->next=t;
        p=p->next;
        cout<<"继续吗"<<endl;
        cin>>ans;
    }
    airline_list=airline_list->next;
}

void check_leftticket(allist airline_list)
{
    cout<<endl<<"请输入你要到达的目的地"<<endl;
    string end;
    cin>>end;
    alnode *t=airline_list;
    while(t!=NULL)
    {
        if(t->data.end==end)
        {
            cout<<"航班号："<<t->data.airnum<<endl;
            cout<<"机型："<<t->data.plane<<endl;
            cout<<"周几："<<t->data.day<<endl;
            cout<<"余票数量："<<t->data.leftticket<<endl;
            return;
        } else
            t=t->next;
    }
    cout<<"并没有该航班"<<endl;
}

void book_ticket(allist &airline_list)
{
    cout<<endl<<"请输入预订的航班号和预订票数："<<endl;
    string airnum;
    int sum;
    cin>>airnum>>sum;
    alnode *head=airline_list;
    alnode *alt=airline_list;
    while(alt!=NULL)
    {
        if(alt->data.airnum==airnum)
        {
            if(sum<=alt->data.leftticket)
            {
                alt->data.leftticket=alt->data.leftticket-sum;
                break;
            }
            else
                alt=alt->next;
        }
        else
            alt=alt->next;
    }
    if(alt==NULL)
    {
        cout << "订票失败,是否进入候补名单？" << endl;
        char t;
        cin>>t;
        if(t=='Y')
        {
            alt=head;
            while(alt!=NULL)
            {
                if(alt->data.airnum==airnum)
                    break;
                else
                    alt=alt->next;
            }
            if(alt==NULL)
            {
                cout<<"查找的航班不存在"<<endl;
                return;
            }
            custnode *customer = new custnode;
            custnode *p=alt->data.b_customer_list;
            cout<<"请输入个人信息"<<endl;
            cin >> customer->data.name;
            cin >> customer->data.phone;
            cin >> customer->data.airclass;
            customer->data.sum = sum;
            customer->data.order=0;
            customer->next = NULL;
            if(p==NULL)
                alt->data.b_customer_list=customer;
            else
            {
                while(p->next!=NULL)
                    p=p->next;
                p->next=customer;
            }
            alt->data.b_customer_list->need+=sum;
            cout<<"加入候补序列成功"<<endl;
        }
        else return;
    }
    else
    {
        airline_list = head;
        custnode *customer = new custnode;
        custnode *p=alt->data.customer_list;
        cin >> customer->data.name;
        cin >> customer->data.phone;
        cin >> customer->data.airclass;
        customer->data.sum = sum;
        customer->data.order=customer->data.phone*100+customer->data.airclass;
        customer->next = NULL;
        if(p==NULL)
            alt->data.customer_list=customer;
        else
        {
            while(p->next!=NULL)
                p=p->next;
            p->next=customer;
        }
        cout<<"订票成功，订单号为："<<customer->data.order<<endl;
    }
}

void refund(allist &airline_list)
{
    string airnum;
    long long order;
    int flag=0;
    cin>>airnum>>order;
    alnode *head=airline_list;
    alnode *alt=airline_list;
    custnode *cust;
    while(alt!=NULL)
    {
        if(alt->data.airnum==airnum)
        {
            if(alt->data.customer_list==NULL)
            {
                flag=1;
                cout<<"订单不存在"<<endl;
                break;
            }
            else
            {
                cust = alt->data.customer_list;
                if (cust->data.order == order)
                {
                    alt->data.leftticket += cust->data.sum;
                    alt->data.customer_list = cust->next;
                    cout << "退票成功" << endl;
                    flag=1;
                    break;
                }
                else
                {
                    while (cust->next != NULL)
                    {
                        if (cust->next->data.order == order)
                        {
                            alt->data.leftticket = +cust->next->data.sum;
                            alt->data.customer_list->next = cust->next->next;
                            cout << "退票成功" << endl;
                            flag=1;
                            goto here;
                        }
                        else
                            cust = cust->next;
                    }
                    if(cust->next==NULL)
                    {
                        flag=1;
                        cout<<"订单不存在"<<endl;
                        break;
                    }
                }
            }
        }
        else
            alt=alt->next;
    }
    here:
    if(flag==0)
        cout<<"订单不存在"<<endl;
    //airline_list=head;

    if(alt->data.b_customer_list!=NULL)
    {
        cust=alt->data.b_customer_list;
        if(cust->data.sum<=alt->data.leftticket)    //当候补旅客列表第一个旅客满足条件时
        {
            alt->data.b_customer_list->need -= cust->data.sum;
            alt->data.leftticket -= cust->data.sum;
            custnode *t = alt->data.customer_list;
            while (t->next != NULL)
                t=t->next;
            t->next=cust;
            alt->data.b_customer_list=cust->next;
        }
    }
}

int main() {
    allist airline_list;
    create_airline_list(airline_list);
    check_leftticket(airline_list);
    book_ticket(airline_list);
    book_ticket(airline_list);
    refund(airline_list);
    return 0;
}