#include <iostream>
#include <string>
using namespace std;

struct arcnode
{
    int adjvex;
    arcnode *next;
};

struct vnode
{
    string data;
    arcnode *firstarc;
};

struct algraph
{
    vnode list[30];
    int arcnum,vexnum;
};

void createalgraph(algraph &g)
{
    int i=0;
    char n;
    g.arcnum=0;
    g.vexnum=0;
    while(1)
    {
        cin>>n; //输入度数
        if(n=='#')
            break;
        n=n-'0';
        g.arcnum+=n;
        cin>>g.list[i].data;
        g.list[i].firstarc=NULL;
        for(int j=0;j<n;j++)
        {
            arcnode *t=new arcnode;
            cin>>t->adjvex;
            //t->adjvex--;
            t->next=g.list[i].firstarc;
            g.list[i].firstarc=t;
        }
        g.vexnum++;
        i++;
    }
    g.arcnum=g.arcnum/2;
}

void visit(vnode v)
{
    cout<<v.data<<" ";
    while(v.firstarc!=NULL)
    {
        cout<<v.firstarc->adjvex<<" ";
        v.firstarc=v.firstarc->next;
    }
    cout<<endl;
}

bool visited[30];

void dfs(algraph g,int v);	//图的深度遍历

void dfstravel(algraph g)
{
    for(int i=0;i<30;i++)
        visited[i]= false;
    for(int i=0;i<g.vexnum;i++)
        if(!visited[i])
            dfs(g,i);
}

void dfs(algraph g,int v)
{
    visited[v]= true;
    visit(g.list[v]);
    if(g.list[v].firstarc!=NULL)
    {
        int w = g.list[v].firstarc->adjvex;
        arcnode *t=g.list[v].firstarc;
        while(t->next!=NULL)
        {
            if(!visited[w])
                dfs(g,w);
            t=t->next;
        }
    }
}

void bfs(algraph g)	//图的广度遍历
{
    bool bfs_visited[30];
    int i=0,j=0;
    for(i=0;i<30;i++)
        bfs_visited[i]= false;
    arcnode *t;
    for(i=0;i<g.vexnum;i++)
    {
        j=i;
        t=g.list[j].firstarc;
        while(true)
        {
            if(!bfs_visited[j])
                visit(g.list[j]);
            bfs_visited[j]=true;
            t=t->next;
            if(t!=NULL)
                j=t->adjvex;
            else
                break;
        }
    }
}

int main()
{
    algraph g;
    createalgraph(g);
    //dfstravel(g);
    bfs(g);
    return 0;
}
