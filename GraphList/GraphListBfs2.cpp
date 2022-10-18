/*
PTA
3-3 社交网络图中结点的“重要性”计算
分数 25
作者 DS课程组
单位 浙江大学
在社交网络中，个人或单位（结点）之间通过某些关系（边）联系起来。他们受到这些关系的影响，这种影响可以理解为网络中相互连接的结点之间蔓延的一种相互作用，可以增强也可以减弱。而结点根据其所处的位置不同，其在网络中体现的重要性也不尽相同。

“紧密度中心性”是用来衡量一个结点到达其它结点的“快慢”的指标，即一个有较高中心性的结点比有较低中心性的结点能够更快地（平均意义下）到达网络中的其它结点，因而在该网络的传播过程中有更重要的价值。在有N个结点的网络中，结点v 
i
​
 的“紧密度中心性”Cc(v 
i
​
 )数学上定义为v 
i
​
 到其余所有结点v 
j
​
  (j

=i) 的最短距离d(v 
i
​
 ,v 
j
​
 )的平均值的倒数：



对于非连通图，所有结点的紧密度中心性都是0。

给定一个无权的无向图以及其中的一组结点，计算这组结点中每个结点的紧密度中心性。

输入格式:
输入第一行给出两个正整数N和M，其中N（≤10 
4
 ）是图中结点个数，顺便假设结点从1到N编号；M（≤10 
5
 ）是边的条数。随后的M行中，每行给出一条边的信息，即该边连接的两个结点编号，中间用空格分隔。最后一行给出需要计算紧密度中心性的这组结点的个数K（≤100）以及K个结点编号，用空格分隔。

输出格式:
按照Cc(i)=x.xx的格式输出K个给定结点的紧密度中心性，每个输出占一行，结果保留到小数点后2位。

输入样例:
9 14
1 2
1 3
1 4
2 3
3 4
4 5
4 6
5 6
5 7
5 8
6 7
6 8
7 8
7 9
3 3 4 9
输出样例:
Cc(3)=0.47
Cc(4)=0.62
Cc(9)=0.35
代码长度限制
16 KB
时间限制
20000 ms
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
        int d=0;
        while(head!=tail){
            while(head!=p){
                head=head->link;
                visitnum[head->vv]=d;
                visit(head->vv);
            }
            p=tail;
            d++;
        }
        while(q!=head){
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
    void bfsvisit(int v){
        bfs(v);
        int sumd=0;
        for(int i=1;i<=vertexnum;i++){
            if(visited[i]==0){
                printf("Cc(%d)=%.2f\n",v,0.0);
                return;
            }
            sumd+=visitnum[i];
        }
        printf("Cc(%d)=%.2f\n",v,1.0*(vertexnum-1)/sumd);
    }

    private:
    Vertex *nodetable;
    int *visited;
    int vertexnum;
    int *visitnum;
    VisitV *head,*tail;
};

int main(){
    int vn,en,v1,v2,n,v;
    cin>>vn>>en;
    Graph g(vn,en);
    for(int i=0;i<en;i++){
        cin>>v1>>v2;
        g.insertEdge(v1,v2);
        g.insertEdge(v2,v1);
    }
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>v;
        g.bfsvisit(v);
    }
    system("pause");
    return 0;
}