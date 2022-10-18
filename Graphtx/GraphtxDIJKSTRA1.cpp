/*
PTA
1-1 旅游规划
分数 30
作者 陈越
单位 浙江大学
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。随后的M行中，每行给出一条高速公路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40
代码长度限制
16 KB
Java (javac)
时间限制
800 ms
内存限制
64 MB
其他编译器
时间限制
400 ms
内存限制
64 MB
*/

/*
邻接表，DIJKSTRA算法，贪心
数组记录遍历情况，权重值
*/

#include<iostream>

using namespace std;
//邻接表边节点
struct Edge{
    int dest,length,weight;
    Edge *link;
    Edge(int num1,int num2,int num3):dest(num1),length(num2),weight(num3),link(NULL){}
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
    Graph(int vnum,int edgenum){
        nodetable=new Vertex[vnum];
        if(nodetable==NULL){
            cerr<<"存储分配错误"<<endl;
            exit(1);
        }
        vertexnum=vnum;
    }
    ~Graph(){}
    //插入边
    void insertEdge(int v1,int v2,int len,int wei){
        Edge *p=new Edge(v2,len,wei);
        p->link=nodetable[v1].headlink;
        nodetable[v1].headlink=p;
    }
    //贪心算法实现
    void tx(int sv,int ev,int maxl,int maxw){
        int *txfinish=new int[vertexnum];
        int *txlength=new int[vertexnum];
        int *txweight=new int[vertexnum];
        for(int i=0;i<vertexnum;i++){
            txfinish[i]=0;
            txlength[i]=maxl;
            txweight[i]=maxw;
        }
        txfinish[sv]=1;
        txlength[sv]=0;
        txweight[sv]=0;
        int txmin=ev;
        Edge *p=nodetable[sv].headlink;
        while(p!=NULL){
            txlength[p->dest]=p->length;
            txweight[p->dest]=p->weight;
            p=p->link;
        }
        for(int i=0;i<vertexnum-1;i++){
            if(txfinish[ev]==1){
                break;
            }
            else{
                txmin=ev;
            }
            for(int j=0;j<vertexnum;j++){
                if(txfinish[j]==1){
                    continue;
                }
                else{
                    if(txlength[j]<txlength[txmin]){
                        txmin=j;
                    }
                    else if(txlength[j]==txlength[txmin]){
                        if(txweight[j]<txweight[txmin]){
                            txmin=j;
                        }
                    }
                }
            }
            txfinish[txmin]=1;
            p=nodetable[txmin].headlink;
            while(p!=NULL){
                if(txfinish[p->dest]==1){
                    p=p->link;
                    continue;
                }
                else{
                    if(txlength[txmin]+p->length<txlength[p->dest]){
                        txlength[p->dest]=txlength[txmin]+p->length;
                        txweight[p->dest]=txweight[txmin]+p->weight;
                    }
                    else if(txlength[txmin]+p->length==txlength[p->dest]){
                        if(txweight[txmin]+p->weight<txweight[p->dest]){
                            txweight[p->dest]=txweight[txmin]+p->weight;
                        }
                    }
                }
                p=p->link;
            }
        }
        cout<<txlength[ev]<<" "<<txweight[ev];
    }

    private:
    Vertex *nodetable;
    int vertexnum;
};

int main(){
    int vn,en,startv,endv,v1,v2,len,wei,maxl,maxw;
    maxl=0;
    maxw=0;
    cin>>vn>>en>>startv>>endv;
    Graph g(vn,en);
    for(int i=0;i<en;i++){
        cin>>v1>>v2>>len>>wei;
        maxl+=len;
        maxw+=wei;
        g.insertEdge(v1,v2,len,wei);
        g.insertEdge(v2,v1,len,wei);
    }
    g.tx(startv,endv,maxl,maxw);
    system("pause");
    return 0;
}