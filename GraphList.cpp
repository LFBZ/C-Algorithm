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
        for(int i=1;i<=vnum;i++){
            visited[i]=0;
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

    void visit(int v){
        visited[v]=1;
        tail->link=new VisitV(v);
        tail=tail->link;
    }

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