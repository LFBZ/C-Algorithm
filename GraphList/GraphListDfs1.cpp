/*
PTA
3-1 地下迷宫探索
分数 20
作者 DS课程组
单位 浙江大学
地道战是在抗日战争时期，在华北平原上抗日军民利用地道打击日本侵略者的作战方式。地道网是房连房、街连街、村连村的地下工事，如下图所示。



我们在回顾前辈们艰苦卓绝的战争生活的同时，真心钦佩他们的聪明才智。在现在和平发展的年代，对多数人来说，探索地下通道或许只是一种娱乐或者益智的游戏。本实验案例以探索地下通道迷宫作为内容。

假设有一个地下通道迷宫，它的通道都是直的，而通道所有交叉点（包括通道的端点）上都有一盏灯和一个开关。请问你如何从某个起点开始在迷宫中点亮所有的灯并回到起点？



输入格式:
输入第一行给出三个正整数，分别表示地下迷宫的节点数N（1<N≤1000，表示通道所有交叉点和端点）、边数M（≤3000，表示通道数）和探索起始节点编号S（节点从1到N编号）。随后的M行对应M条边（通道），每行给出一对正整数，分别是该条边直接连通的两个节点的编号。

输出格式:
若可以点亮所有节点的灯，则输出从S开始并以S结束的包含所有节点的序列，序列中相邻的节点一定有边（通道）；否则虽然不能点亮所有节点的灯，但还是输出点亮部分灯的节点序列，最后输出0，此时表示迷宫不是连通图。

由于深度优先遍历的节点序列是不唯一的，为了使得输出具有唯一的结果，我们约定以节点小编号优先的次序访问（点灯）。在点亮所有可以点亮的灯后，以原路返回的方式回到起点。

输入样例1:
6 8 1
1 2
2 3
3 4
4 5
5 6
6 4
3 6
1 5
输出样例1:
1 2 3 4 5 6 5 4 3 2 1
输入样例2:
6 6 6
1 2
1 3
2 3
5 4
6 5
6 4
输出样例2:
6 4 5 4 6 0
代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
*/

/*
邻接表，深度优先搜索
链表栈存储遍历结果
*/

#include<iostream>

using namespace std;
//邻接表边节点
struct Edge{
    int dest;
    Edge *link;//
    Edge(int num):dest(num),link(NULL){}
};
//邻接表顶点节点
struct Vertex{
    Edge *headlink;
    Vertex():headlink(NULL){}
};
//链表栈遍历顶点节点
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
        for(int i=1;i<=vnum;i++){
            visited[i]=0;
        }
        head=new VisitV(0);
        tail=head;
    }
    ~Graph(){}
    //邻接表插入边节点
    void insertEdge(int v1,int v2){
        Edge *p=new Edge(v2);
        Edge *t=nodetable[v1].headlink;
        if(t==NULL){
            nodetable[v1].headlink=p;
        }
        else if(t->dest>v2){
            p->link=t;
            nodetable[v1].headlink=p;
        }
        else{
            while(t->link!=NULL){
                if(t->link->dest<v2){
                    t=t->link;
                }
                else{
                    break;
                }
            }
            p->link=t->link;
            t->link=p;
        }
    }
    //递归dfs
    void light(int v){
        visit(v);
        Edge *p=nodetable[v].headlink;
        while(p!=NULL){
            if(visited[p->dest]==0){
                light(p->dest);
                visit(v);
            }
            p=p->link;
        }
    }
    //遍历顶点操作
    void visit(int v){
        visited[v]=1;
        tail->link=new VisitV(v);
        tail=tail->link;
    }
    //实现和输出格式
    void lightvisit(int startv){
        light(startv);
        head=head->link;
        if(head!=NULL){
            cout<<head->vv;
            head=head->link;
            while(head!=NULL){
                cout<<" "<<head->vv;
                head=head->link;
            }
        }
        for(int i=1;i<=vertexnum;i++){
            if(visited[i]==0){
                cout<<" 0";
                break;
            }
        }
    }

    private:
    Vertex *nodetable;
    int *visited;
    int vertexnum;
    VisitV *head,*tail;
};

int main(){
    int vn,en,sv,v1,v2;
    cin>>vn>>en>>sv;
    Graph g(vn,en);
    for(int i=0;i<en;i++){
        cin>>v1>>v2;
        g.insertEdge(v1,v2);
        g.insertEdge(v2,v1);
    }
    g.lightvisit(sv);
    system("pause");
    return 0;
}