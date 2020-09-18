#include<iostream>
#include<vector>
using namespace std;

class Edge{
    public:
    int v = 0;
    int w = 0;

    Edge(int v,int w){
        this->v= v;
        this->w = w;
    }
};

int N = 7;
vector<vector<Edge>> graph(N,vector<Edge>());

void addEdge(vector<vector<Edge>> &graph,int u,int v,int w){
    Edge e1(u,w);
    Edge e2(v,w);
    graph[u].push_back(e2);
    graph[v].push_back(e1);
}

void display(vector<vector<Edge>> &graph){
    for(int i=0;i<N;i++){
        cout<<i<<" --> ";
        for(Edge e:graph[i]){
            cout<<" ("<<e.v<<","<<e.w<<"), ";
        }
        cout<<endl;
    }
}
void createGraph(){
    addEdge(graph,0,1,10);
    addEdge(graph,0,3,10);
    addEdge(graph,1,2,10);
    addEdge(graph,2,3,40);
    addEdge(graph,3,4,2);
    addEdge(graph,4,5,2);
    addEdge(graph,4,6,8);
    addEdge(graph,5,6,3);
    display(graph);
}

int main(){
    createGraph();
    return 0;
}