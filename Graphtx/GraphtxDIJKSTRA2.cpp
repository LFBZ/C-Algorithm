/*
PTA
1-2 直捣黄龙
分数 35
作者 陈越
单位 浙江大学
本题是一部战争大片 —— 你需要从己方大本营出发，一路攻城略地杀到敌方大本营。首先时间就是生命，所以你必须选择合适的路径，以最快的速度占领敌方大本营。当这样的路径不唯一时，要求选择可以沿途解放最多城镇的路径。若这样的路径也不唯一，则选择可以有效杀伤最多敌军的路径。

输入格式：
输入第一行给出2个正整数N（2 ≤ N ≤ 200，城镇总数）和K（城镇间道路条数），以及己方大本营和敌方大本营的代号。随后N-1行，每行给出除了己方大本营外的一个城镇的代号和驻守的敌军数量，其间以空格分隔。再后面有K行，每行按格式城镇1 城镇2 距离给出两个城镇之间道路的长度。这里设每个城镇（包括双方大本营）的代号是由3个大写英文字母组成的字符串。

输出格式：
按照题目要求找到最合适的进攻路径（题目保证速度最快、解放最多、杀伤最强的路径是唯一的），并在第一行按照格式己方大本营->城镇1->...->敌方大本营输出。第二行顺序输出最快进攻路径的条数、最短进攻距离、歼敌总数，其间以1个空格分隔，行首尾不得有多余空格。

输入样例：
10 12 PAT DBY
DBY 100
PTA 20
PDS 90
PMS 40
TAP 50
ATP 200
LNN 80
LAO 30
LON 70
PAT PTA 10
PAT PMS 10
PAT ATP 20
PAT LNN 10
LNN LAO 10
LAO LON 10
LON DBY 10
PMS TAP 10
TAP DBY 10
DBY PDS 10
PDS PTA 10
DBY ATP 10
输出样例：
PAT->PTA->PDS->DBY
3 30 210
代码长度限制
16 KB
时间限制
150 ms
内存限制
64 MB
*/

/*
邻接表，DIJKSTRA算法，贪心
数组记录遍历情况，权重值，路径，路径数量
*/

#include<iostream>
#include<map>
#include<stack>
#include<string>

using namespace std;
//邻接表边节点
struct Edge{
    int dest,length;
    Edge *link;
    Edge(int num1,int num2):dest(num1),length(num2),link(NULL){}
};
//邻接表顶点节点
struct Vertex{
    Edge *headlink;
    Vertex():headlink(NULL){}
};
//图类
class Graph{
    public:
    //构造函数初始化
    Graph(int vnum,int edgenum,string startv){
        nodetable=new Vertex[vnum];
        if(nodetable==NULL){
            cerr<<"存储分配错误"<<endl;
            exit(1);
        }
        vertexnum=vnum;
        vweight=new int[vnum];
        vweight[0]=0;
        vname[startv]=0;
        vid[0]=startv;
    }
    ~Graph(){}
    //插入点
    void insertVertex(string vname1,int v,int wei){
        vname[vname1]=v;
        vid[v]=vname1;
        vweight[v]=wei;
    }
    //插入边
    void insertEdge(string vname1,string vname2,int len){
        int v1=vname[vname1];
        int v2=vname[vname2];
        Edge *p=new Edge(v2,len);
        p->link=nodetable[v1].headlink;
        nodetable[v1].headlink=p;
        p=new Edge(v1,len);
        p->link=nodetable[v2].headlink;
        nodetable[v2].headlink=p;
    }
    //贪心算法实现
    void tx(string evname,int maxl){
        int ev=vname[evname];
        int *txfinish=new int[vertexnum];
        int *txlength=new int[vertexnum];
        int *txnum=new int[vertexnum];
        int *txweight=new int[vertexnum];
        int *txpth=new int[vertexnum];
        int *txpthnum=new int[vertexnum];
        for(int i=1;i<vertexnum;i++){
            txfinish[i]=0;
            txlength[i]=maxl;
            txnum[i]=0;
            txweight[i]=0;
            txpth[i]=-1;
            txpthnum[i]=0;
        }
        txfinish[0]=1;
        txlength[0]=0;
        txnum[0]=0;
        txweight[0]=0;
        txpth[0]=0;
        txpthnum[0]=1;
        int txmin=ev;
        for(Edge *p=nodetable[0].headlink;p!=NULL;p=p->link){
            txlength[p->dest]=p->length;
            txnum[p->dest]=1;
            txweight[p->dest]=vweight[p->dest];
            txpth[p->dest]=0;
            txpthnum[p->dest]=1;
        }
        for(int i=0;i<vertexnum-1;i++){
            if(txfinish[ev]==1){
                break;
            }
            txmin=ev;
            for(int j=1;j<vertexnum;j++){
                if(txfinish[j]==1){
                    continue;
                }
                if(txlength[j]<txlength[txmin]){
                    txmin=j;
                }
                else if(txlength[j]==txlength[txmin]){
                    if(txnum[j]>txnum[txmin]){
                        txmin=j;
                    }
                    else if(txnum[j]==txnum[txmin]){
                        if(txweight[j]>txweight[txmin]){
                            txmin=j;
                        }
                    }
                }
            }
            txfinish[txmin]=1;
            for(Edge *p=nodetable[txmin].headlink;p!=NULL;p=p->link){
                if(txfinish[p->dest]==1){
                    continue;
                }
                if(p->length+txlength[txmin]<txlength[p->dest]){
                    txlength[p->dest]=p->length+txlength[txmin];
                    txnum[p->dest]=txnum[txmin]+1;
                    txweight[p->dest]=txweight[txmin]+vweight[p->dest];
                    txpth[p->dest]=txmin;
                    txpthnum[p->dest]=txpthnum[txmin];
                }
                else if(p->length+txlength[txmin]==txlength[p->dest]){
                    txpthnum[p->dest]+=txpthnum[txmin];
                    if(txnum[txmin]+1>txnum[p->dest]){
                        txnum[p->dest]=txnum[txmin]+1;
                        txweight[p->dest]=txweight[txmin]+vweight[p->dest];
                        txpth[p->dest]=txmin;
                    }
                    else if(txnum[txmin]+1==txnum[p->dest]){
                        if(txweight[txmin]+vweight[p->dest]>txweight[p->dest]){
                            txweight[p->dest]=txweight[txmin]+vweight[p->dest];
                            txpth[p->dest]=txmin;
                        }
                    }
                }
            }
        }
        int *path=new int[txnum[ev]];
        txmin=ev;
        for(int i=txnum[ev]-1;i>=0;i--){
            path[i]=txmin;
            txmin=txpth[txmin];
        }
        cout<<vid[0];
        for(int i=0;i<txnum[ev];i++){
            cout<<"->"<<vid[path[i]];
        }
        cout<<endl<<txpthnum[ev]<<" "<<txlength[ev]<<" "<<txweight[ev];
    }

    private:
    Vertex *nodetable;
    int vertexnum;
    int *vweight;
    map<string,int> vname;
    map<int,string> vid;
};

int main(){
    
    int vn,en,wei,len,maxl;
    string vname1,vname2,endvname;
    maxl=0;
    cin>>vn>>en>>vname1>>endvname;
    Graph g(vn,en,vname1);
    for(int i=1;i<vn;i++){
        cin>>vname1>>wei;
        g.insertVertex(vname1,i,wei);
    }
    for(int i=0;i<en;i++){
        cin>>vname1>>vname2>>len;
        maxl+=len;
        g.insertEdge(vname1,vname2,len);
    }
    g.tx(endvname,maxl);
    system("pause");
    return 0;
}