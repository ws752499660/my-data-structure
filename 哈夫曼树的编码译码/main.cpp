#include <iostream>
#include <fstream>

using namespace std;

typedef struct htnode
{
    int weight;
    int parent,lkid,rkid;
    char name;
}*huffmantree;

typedef struct hfcodenode
{
    char codename;
    char *code;
}*huffmancode;

void select(huffmantree ht,int n,int &s1,int &s2)
{
    struct htline
    {
        htnode tree;
        int loc;
    };
    int q=0,i;
    for(i=1;i<=n;i++)
        if(ht[i].parent==0)
            q++;
    htline *line=new htline[q+1];
    q=1;
    for(i=1;i<=n;i++)
    {
        if(ht[i].parent==0)
        {
            line[q].tree=ht[i];
            line[q].loc=i;
            q++;
        }
    }
    for(i=1;i<=q-1;i++)
        for(int j=1;j<q-i;j++)
        {
            if(line[j].tree.weight>=line[j+1].tree.weight)
            {
                htline t=line[j];
                line[j]=line[j+1];
                line[j+1]=t;
            }
        }
    s1=line[1].loc;
    s2=line[2].loc;
    delete line;
}

void create_huffmantree(huffmantree &ht,int *w,int n,char *cline)
{
    if(n<=1)
        return;
    int m=2*n-1;
    ht=new htnode[m+1]; //No.0 will not be used.
    int i;
    for(i=1;i<=n;i++)
    {
        ht[i].weight=w[i-1];
        ht[i].name=cline[i-1];
        ht[i].parent=0;
        ht[i].lkid=0;
        ht[i].rkid=0;
    }
    for(;i<=m;i++)
    {
        ht[i].weight=0;
        ht[i].name='#';
        ht[i].parent=0;
        ht[i].lkid=0;
        ht[i].rkid=0;
    }
    int s1,s2;
    for(i=n+1;i<=m;i++)
    {
        select(ht,i-1,s1,s2);
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].lkid=s1;
        ht[i].rkid=s2;
        ht[i].weight=ht[s1].weight+ht[s2].weight;
    }
    ofstream out ("out.txt");
    for(i=1;i<=m;i++)
    {
        out<<ht[i].weight<<" ";
    }
    out<<endl;
    for(i=1;i<=m;i++)
    {
        out<<ht[i].parent<<" ";
    }
    out<<endl;
    for(i=1;i<=m;i++)
    {
        out<<ht[i].lkid<<" ";
    }
    out<<endl;
    for(i=1;i<=m;i++)
    {
        out<<ht[i].rkid<<" ";
    }
    out<<endl;
    for(i=1;i<=m;i++)
    {
        out<<ht[i].name<<" ";
    }
}

void create_huffmancode(huffmantree &ht,huffmancode &hc,int n,char *cline)
{

    hc=new hfcodenode[n+1];
    char *cd=new char[n]; //code workspace
    cd[n-1]='\0';
    for(int i=1;i<=n;i++)
    {
        int start=n-1;
        int c=i,f=ht[i].parent;
        while(f!=0)
        {
            if(ht[f].lkid==c)
                cd[start]='0';
            else
                cd[start]='1';
            start--;
            c=f;
            f=ht[c].parent;
        }
        start++;
        hc[i].code=new char[n-start];
        //strcpy(hc[i].code,&cd[start]);
        int j=1;
        while(cd[start]=='0'||cd[start]=='1')
        {
            hc[i].code[j]=cd[start];
            j++;
            start++;
        }
        hc[i].codename=cline[i-1];
    }
    delete cd;
}

void encoding(huffmancode hc,int n)
{
    ifstream in ("text.txt");
    ofstream out ("aftercode.txt");
    char ch;
    int i=1,j=1;
    while(in.get(ch))
    {
        for(i=1;i<=n;i++)
            if(ch==hc[i].codename)
            {
                while (hc[i].code[j] == '0' || hc[i].code[j] == '1')
                {
                    out << hc[i].code[j];
                    j++;
                }
                j = 1;
            }
    }
}

void decoding(huffmantree ht,int n)
{
    ifstream in("aftercode.txt");
    ofstream out("afterdecode.txt");
    char read_char;
    int point=2*n-1;
    while(in.get(read_char))
    {
        if(read_char=='0')
            point=ht[point].lkid;
        else
            point=ht[point].rkid;
        if(ht[point].name!='#')
        {
            out<<ht[point].name;
            point=2*n-1;
        }
    }
    out.close();
    in.close();
}

int main()
{
    int n,*w,i;
    cin>>n;
    w=new int[n];
    char c;
    char *cline=new char[n];
    //cin.clear();
    getchar(); //吃掉回车
    for(i=0;i<n;i++)
    {
        c=getchar();
        cline[i]=c;
    }
    for(i=0;i<n;i++)
        cin>>w[i];

    huffmantree ht;
    huffmancode hc;
    create_huffmantree(ht,w,n,cline);
    create_huffmancode(ht,hc,n,cline);

    for(i=1;i<=n;i++)
        cout<<hc[i].codename<<" ";
    cout<<endl;

    int j=1;
    for(i=1;i<=n;i++)
    {
        j = 1;
        while (hc[i].code[j]=='0'|| hc[i].code[j]=='1')
        {
            cout<<hc[i].code[j];
            j++;
        }
        cout<<" ";
    }
    cout<<endl;

    encoding(hc,n);
    decoding(ht,n);

    return 0;
}