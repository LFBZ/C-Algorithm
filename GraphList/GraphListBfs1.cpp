/*
PTA
3-2 六度空间
分数 20
作者 DS课程组
单位 浙江大学
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通过五个人你就能够认识任何一个陌生人。”如图1所示。


图1 六度空间示意图
“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的研究具有太大的局限性和困难。随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的百分比。

输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10 
3
 ，表示人数）、边数M（≤33×N，表示社交关系数）。随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
代码长度限制
16 KB
时间限制
2500 ms
内存限制
64 MB
*/

/*
邻接表，广度优先搜索
链表队列辅助
数组存储结果
*/

#include<iostream>

using namespace std;
//邻接表边节点
struct Edge{
    int dest;
    Edge *link;
    Edge(int num):dest(num),link(NULL){}
};
//邻接表顶点节点
struct Vertex{
    Edge *headlink;
    Vertex():headlink(NULL){}
};
//链表队列顶点节点
struct VisitV{
    int vv;
    VisitV *link;
    VisitV(int num):vv(num),link(NULL){}
};
//图类
class Graph{
    public:
    //构造函数初始化
    Graph(int vnum,int edgenum){
        nodetable=new Vertex[vnum+1];
        if(nodetable==NULL){
            cerr<<"存储分配错误"<<endl;
            exit(1);
        }
        vertexnum=vnum;
        visited=new int[vnum+1];
        visitnum=new int[vnum+1];
        for(int i=1;i<=vnum;i++){
            visited[i]=0;
            visitnum[i]=0;
        }
        head=new VisitV(0);
        tail=head;
    }
    ~Graph(){}
    //插入边
    void insertEdge(int v1,int v2){
        Edge *p=new Edge(v2);
        p->link=nodetable[v1].headlink;
        nodetable[v1].headlink=p;
    }
    //广度优先搜索循环实现
    void bfs(int v){
        for(int i=1;i<=vertexnum;i++){
            visited[i]=0;
        }
        visited[v]=1;
        tail->link=new VisitV(v);
        tail=tail->link;
        VisitV *p=tail;
        VisitV *q=head;
        for(int i=0;i<6;i++){
            while(head!=p){
                head=head->link;
                visit(head->vv);
            }
            p=tail;
        }
        head=tail;
        while(q!=head){
            visitnum[v]++;
            p=q;
            q=q->link;
            delete p;
        }
    }
    //遍历顶点操作
    void visit(int v){
        Edge *p=nodetable[v].headlink;
        while(p!=NULL){
            if(visited[p->dest]==0){
                visited[p->dest]=1;
                tail->link=new VisitV(p->dest);
                tail=tail->link;
            }
            p=p->link;
        }
    }
    //实现和输出格式
    void bfsvisit(){
        for(int i=1;i<=vertexnum;i++){
            bfs(i);
            printf("%d: %.2f%\n",i,100.0*visitnum[i]/vertexnum);
        }
    }

    private:
    Vertex *nodetable;
    int *visited;
    int vertexnum;
    int *visitnum;
    VisitV *head,*tail;
};

int main(){
    int vn,en,v1,v2;
    cin>>vn>>en;
    Graph g(vn,en);
    for(int i=0;i<en;i++){
        cin>>v1>>v2;
        g.insertEdge(v1,v2);
        g.insertEdge(v2,v1);
    }
    g.bfsvisit();
    system("pause");
    return 0;
}