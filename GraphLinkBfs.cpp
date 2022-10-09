#include<iostream>

using namespace std;

struct Edge{
    int dest;
    Edge *link;
    Edge(int num):dest(num),link(NULL){}
};

struct Vertex{
    Edge *headlink;
    Vertex():headlink(NULL){}
};

struct VisitV{
    int vv;
    VisitV *link;
    VisitV(int num):vv(num),link(NULL){}
};

class Graph{
    public:
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