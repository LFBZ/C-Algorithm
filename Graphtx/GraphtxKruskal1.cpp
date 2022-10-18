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
邻接表，快速排序边，Kruskal算法，贪心
数组记录遍历情况和顶点分组情况，判断是否连通
相同权重边滑动窗口比较判断是否唯一路径
*/

#include<iostream>

using namespace std;

struct Edge{
    int startv,endv,length;
	Edge(){}
    Edge(Edge *p){
		startv=p->startv;
		endv=p->endv;
		length=p->length;
	}
};

class Graph{
    public:
    Graph(int vertexn,int edgen){
		earray=new Edge[edgen];
        vertexnum=vertexn;
		edgenum=edgen;
		int v1,v2,len;
		for(int i=0;i<edgen;i++){
			cin>>v1>>v2>>len;
			earray[i].startv=v1;
			earray[i].endv=v2;
			earray[i].length=len;
		}
		sortEdge(0,edgenum-1);
    }
    ~Graph(){}

    void sortEdge(int left,int right){
		if(left>=right){
			return;
		}
		int key=earray[left].length;
		int lp=left+1;
		int rp=right;
		Edge *p;
		while(lp<rp){
			while(earray[rp].length>key&&lp<rp){
				rp--;
			}
			while(earray[lp].length<=key&&lp<rp){
				lp++;
			}
			if(lp<rp){
				p=new Edge(earray[lp]);
				earray[lp]=earray[rp];
				earray[rp]=p;
				delete p;
			}
		}
		if(earray[lp].length>key){
			lp--;
		}
		p=new Edge(earray[lp]);
		earray[lp]=earray[left];
		earray[left]=p;
		delete p;
		sortEdge(left,lp-1);
		sortEdge(lp+1,right);
    }

	void tx(){
		int *txvisit=new int[vertexnum+1];
		int num=0,totallen=0,only=1,samenum=0,tag,tag0;
		for(int i=1;i<=vertexnum;i++){
			txvisit[i]=0;
		}

		for(int i=0;i<edgenum;i++){
			if(only==1&&samenum<=0){
				samenum=0;
				int len=earray[i].length;
				while(earray[i+samenum+1].length==len){
					samenum++;
				}
			}
			if(txvisit[earray[i].startv]==0&&txvisit[earray[i].endv]==0){
				num++;
				txvisit[earray[i].startv]=num;
				txvisit[earray[i].endv]=num;
				totallen+=earray[i].length;
			}
			else if(txvisit[earray[i].startv]==0&&txvisit[earray[i].endv]!=0){
				if(only==1){
					for(int j=1;j<=samenum;j++){
						if(earray[i].startv==earray[i+j].startv&&txvisit[earray[i].endv]==txvisit[earray[i+j].endv]){
							only=0;
							break;
						}
						else if(earray[i].startv==earray[i+j].endv&&txvisit[earray[i].endv]==txvisit[earray[i+j].startv]){
							only=0;
							break;
						}
					}
				}
				txvisit[earray[i].startv]=txvisit[earray[i].endv];
				totallen+=earray[i].length;
			}
			else if(txvisit[earray[i].startv]!=0&&txvisit[earray[i].endv]==0){
				if(only==1){
					for(int j=1;j<=samenum;j++){
						if(earray[i].endv==earray[i+j].startv&&txvisit[earray[i].startv]==txvisit[earray[i+j].endv]){
							only=0;
							break;
						}
						else if(earray[i].endv==earray[i+j].endv&&txvisit[earray[i].startv]==txvisit[earray[i+j].startv]){
							only=0;
							break;
						}
					}
				}
				txvisit[earray[i].endv]=txvisit[earray[i].startv];
				totallen+=earray[i].length;
			}
			else if(txvisit[earray[i].startv]>txvisit[earray[i].endv]){
				tag0=txvisit[earray[i].startv];
				tag=txvisit[earray[i].endv];
				if(only==1){
					for(int j=1;j<=samenum;j++){
						if(txvisit[earray[i+j].startv]==tag&&txvisit[earray[i+j].endv]==tag0){
							only=0;
							break;
						}
						else if(txvisit[earray[i+j].startv]==tag0&&txvisit[earray[i+j].endv]==tag){
							only=0;
							break;
						}
					}
				}
				for(int j=1;j<=vertexnum;j++){
					if(txvisit[j]==tag0){
						txvisit[j]=tag;
					}
					else if(txvisit[j]>tag0){
						txvisit[j]--;
					}
				}
				num--;
				totallen+=earray[i].length;
			}
			else if(txvisit[earray[i].startv]<txvisit[earray[i].endv]){
				tag=txvisit[earray[i].startv];
				tag0=txvisit[earray[i].endv];
				if(only==1){
					for(int j=1;j<=samenum;j++){
						if(txvisit[earray[i+j].startv]==tag&&txvisit[earray[i+j].endv]==tag0){
							only=0;
							break;
						}
						else if(txvisit[earray[i+j].startv]==tag0&&txvisit[earray[i+j].endv]==tag){
							only=0;
							break;
						}
					}
				}
				for(int j=1;j<=vertexnum;j++){
					if(txvisit[j]==tag0){
						txvisit[j]=tag;
					}
					else if(txvisit[j]>tag0){
						txvisit[j]--;
					}
				}
				num--;
				totallen+=earray[i].length;
			}
			samenum--;
		}
		for(int i=1;i<=vertexnum;i++){
			if(txvisit[i]==0){
				num++;
			}
		}
		if(num==1){
			if(only==1){
				cout<<totallen<<endl<<"Yes";
			}
			else{
				cout<<totallen<<endl<<"No";
			}
		}
		else{
			cout<<"No MST"<<endl<<num;
		}
	}

    private:
	Edge *earray;
    int vertexnum,edgenum;
};

int main(){
    
    int vn,en;
    cin>>vn>>en;
    Graph g(vn,en);
    g.tx();
    system("pause");
    return 0;
}