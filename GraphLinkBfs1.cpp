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
        p->link=nodetable[v1].headlink;
        nodetable[v1].headlink=p;
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