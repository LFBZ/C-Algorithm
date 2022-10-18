/*
PTA
1-3 最小生成树的唯一性
分数 35
作者 陈越
单位 浙江大学
给定一个带权无向图，如果是连通图，则至少存在一棵最小生成树，有时最小生成树并不唯一。本题就要求你计算最小生成树的总权重，并且判断其是否唯一。

输入格式：
首先第一行给出两个整数：无向图中顶点数 N（≤500）和边数 M。随后 M 行，每行给出一条边的两个端点和权重，格式为“顶点1 顶点2 权重”，其中顶点从 1 到N 编号，权重为正整数。题目保证最小生成树的总权重不会超过 2 
30
 。

输出格式：
如果存在最小生成树，首先在第一行输出其总权重，第二行输出“Yes”，如果此树唯一，否则输出“No”。如果树不存在，则首先在第一行输出“No MST”，第二行输出图的连通集个数。

输入样例 1：
5 7
1 2 6
5 1 1
2 3 4
3 4 3
4 1 7
2 4 2
4 5 5
输出样例 1：
11
Yes
输入样例 2：
4 5
1 2 1
2 3 1
3 4 2
4 1 2
3 1 3
输出样例 2：
4
No
输入样例 3：
5 5
1 2 1
2 3 1
3 4 2
4 1 2
3 1 3
输出样例 3：
No MST
2
代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
*/

/*
邻接表，Prim算法，贪心
数组记录遍历情况，相同权重边同一轮次比较得出是否唯一路径，遍历情况查看是否连通
算法时间复杂度O(n^2)，运行超时！
*/

#include<iostream>

using namespace std;

struct Edge{
    int dest,length;
    Edge *link,*pre;
    Edge(int num1,int num2):dest(num1),length(num2),link(NULL),pre(NULL){}
};

struct Vertex{
    Edge *headlink;
    Vertex():headlink(NULL){}
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
		maxl=0;
    }
    ~Graph(){}

    void insertEdge(int v1,int v2,int len){
		if(len>=maxl){
			maxl=len+1;
		}
        Edge *p=new Edge(v2,len);
		if(nodetable[v1].headlink!=NULL){
			nodetable[v1].headlink->pre=p;
			p->link=nodetable[v1].headlink;
		}
        nodetable[v1].headlink=p;
        p=new Edge(v1,len);
        if(nodetable[v2].headlink!=NULL){
			nodetable[v2].headlink->pre=p;
			p->link=nodetable[v2].headlink;
		}
        nodetable[v2].headlink=p;
    }

    void tx(){
		int v1,v2,len,only,i,j;
		int sumlen=0;
		int result=0;
		Edge *p,*t;
        int *ingraph=new int[vertexnum];
		int *txvisit=new int[vertexnum+1];
		for(i=1;i<=vertexnum;i++){
			txvisit[i]=0;
		}
		ingraph[0]=1;
		txvisit[1]=1;
		for(i=0;i<vertexnum-1;i++){
			len=maxl;
			for(j=0;j<=i;j++){
				for(p=nodetable[ingraph[j]].headlink;p!=NULL;){
					if(txvisit[p->dest]==1){
						if(p->pre==NULL){
							if(p->link==NULL){
								nodetable[ingraph[j]].headlink=NULL;
							}
							else{
								nodetable[ingraph[j]].headlink=p->link;
								p->link->pre=NULL;
							}
						}
						else{
							if(p->link==NULL){
								p->pre->link=NULL;
							}
							else{
								p->pre->link=p->link;
								p->link->pre=p->pre;
							}
						}
						t=p;
						p=p->link;
						delete t;
						continue;
					}
					if(p->length<len){
						v1=ingraph[j];
						v2=p->dest;
						len=p->length;
						only=1;
					}
					else if(p->length==len){
						if(p->dest==v2){
							only=0;
						}
					}
					p=p->link;
				}
			}
			if(only==0){
				result=1;
			}
			if(len<maxl){
				ingraph[i+1]=v2;
				txvisit[v2]=1;
				sumlen+=len;
			}
			else{
				result=2;
				break;
			}
		}
		if(result==0){
			cout<<sumlen<<endl<<"Yes";
		}
		else if(result==1){
			cout<<sumlen<<endl<<"No";
		}
		else{
			int num=1;
			for(int k=1;k<=vertexnum;k++){
				if(txvisit[k]==0){
					num++;
					ingraph[++i]=k;
					txvisit[k]=1;
					break;
				}
			}
			for(;i<vertexnum-1;i++){
				for(j=i;j<=i;j++){
					for(p=nodetable[ingraph[j]].headlink;p!=NULL;p=p->link){
						if(txvisit[p->dest]==0){
							ingraph[++i]=p->dest;
							txvisit[p->dest]=1;
						}
					}
				}
				for(int k=1;k<=vertexnum;k++){
					if(txvisit[k]==0){
						num++;
						ingraph[i+1]=k;
						txvisit[k]=1;
						break;
					}
				}
			}
			cout<<"No MST"<<endl<<num;
		}
    }

    private:
    Vertex *nodetable;
    int vertexnum,maxl;
};

int main(){
    
    int vn,en,v1,v2,len;
    cin>>vn>>en;
    Graph g(vn,en);
    for(int i=0;i<en;i++){
        cin>>v1>>v2>>len;
        g.insertEdge(v1,v2,len);
    }
    g.tx();
    system("pause");
    return 0;
}