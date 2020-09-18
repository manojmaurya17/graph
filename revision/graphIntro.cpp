#include<iostream>
#include<vector>
using namespace std;

// class to represent the edge of the graph
class Edge{
    public:
    int v=0; // v -> destination vertex
    int w=0; // w -> weight of the edge between src and dest

    Edge(int v,int w){
        this->v = v; // initialising the dest vertex
        this->w = w; // initialising the weight of the edge
    }
};

// size of the graph
int N = 7;
// graph representation using adjacency list
vector<vector<Edge*>> graph(N,vector<Edge*>());

// function to add the edge in the graph
void addEdge(vector<vector<Edge*>>& gp,int u,int v,int w){
    gp[u].push_back(new Edge(v,w)); /// adding the edge from u to v
    gp[v].push_back(new Edge(u,w)); // adding the edge from v to u
}

// function to print the graph
void display(vector<vector<Edge*>> gp){
    for(int i=0;i<gp.size();i++){
        cout<<i<<" -> ";
        for(Edge* e:gp[i]){
            cout<<"("+to_string(e->v)+","+to_string(e->w)+") ";
        }
        cout<<endl;
    }
    cout<<endl;
}
// creating the graph by adding the edge in it
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

void removeEdge(int u,int v){
    for(int i=0;i<graph[u].size();i++){
        if(graph[u][i]->v == v){
            graph[u].erase(graph[u].begin()+i);
            break;
        }
    }

    for(int i=0;i<graph[v].size();i++){
        if(graph[v][i]->v == u){
            graph[v].erase(graph[v].begin()+i);
            break;
        }
    }
}

void removeVertex(int vtx){
    int si = graph[vtx].size();
    for(int i=si-1;i>=0;i--){
        removeEdge(vtx,graph[vtx][i]->v);
    }
}

bool hasPath(int src,int dest,vector<bool>& vis){
    if(src==dest){
        return true;
    }
    vis[src] = true;
    bool res = false;
    for(Edge* e:graph[src]){
        if(!vis[e->v]){
            res = res || hasPath(e->v,dest,vis);
        }
    }
    // vis[src] = false;
    return res;
}

int allPaths(int src,int dest,int wt,string ans,vector<bool>&vis){
    if(src==dest){
        cout<<ans+to_string(src)+"@"+to_string(wt)<<endl;
        return 1;
    }
    bool res = false;
    vis[src] = true;
    int count = 0;
    for(Edge* e:graph[src]){
        if(!vis[e->v]){
            count += allPaths(e->v,dest,wt+e->w,ans+to_string(src)+" ",vis);
        }
    }
    vis[src] = false;
  return count;

}

class Gpair{
    public:
    string path = "";
    int wsf = 0;

    Gpair(int wsf,string path){
        this->path = path;
        this->wsf = wsf;
    }
};

Gpair longestWeightPath(int src,int dest,vector<bool>& vis){
    if(src==dest){
        return Gpair(0,to_string(src));
    }
    Gpair myAns(0,"");
    vis[src] = true;
    for(Edge* e:graph[src]){
        if(!vis[e->v]){
            Gpair recAns = longestWeightPath(e->v,dest,vis);
            if(recAns.wsf+e->w>myAns.wsf){
                myAns.wsf = recAns.wsf + e->w;
                myAns.path = to_string(src)+" "+recAns.path;
            }
        }
    }
    vis[src] = false;
    return myAns;
}

Gpair smallestWeightPath(int src,int dest,vector<bool>& vis){
    if(src==dest){
        return Gpair(0,to_string(src));
    }
    Gpair myAns(10000,"");
    vis[src] = true;
    for(Edge* e:graph[src]){
        if(!vis[e->v]){
            Gpair recAns = smallestWeightPath(e->v,dest,vis);
            if(recAns.wsf+e->w<myAns.wsf){
                myAns.wsf = recAns.wsf + e->w;
                myAns.path = to_string(src)+" "+recAns.path;
            }
        }
    }
    vis[src] = false;
    return myAns;
}


int hamiltonianPath(int src,vector<bool>& vis,int count,string ans){
    if(count==N-1){
        cout<<ans+to_string(src)<<endl;
        return 1;
    }
    vis[src] = true;
    int ways = 0;
    for(Edge* e:graph[src]){
        if(!vis[e->v]){
            ways += hamiltonianPath(e->v,vis,count+1,ans+to_string(src));
        }
    }
    vis[src] = false;
    return ways;
}


int hamiltonianCycle(int src,int oSrc,vector<bool>&vis,string ans,int count){
    if(count==N-1){
        for(Edge* e:graph[src]){
            if(e->v == oSrc){
                cout<<ans+to_string (src)<<endl;
                return 1;
            }
        }
        return 0;
    }
    int ways = 0;
    vis[src] = true;
    for(Edge* e:graph[src]){
        if(!vis[e->v]){
            ways += hamiltonianCycle(e->v,oSrc,vis,ans+to_string(src),count+1);
        }
    }
    vis[src] = false;
    return ways;
}



void solve(){
    createGraph();
    // removeEdge(3,4);
    // removeVertex(3);
    vector<bool> vis(N,false);
    // cout<<hasPath(0,6,vis)<<endl;
    // cout<<allPaths(0,6,0,"",vis)<<endl;
    // Gpair ans = longestWeightPath(0,6,vis);
    // Gpair ans = smallestWeightPath(0,6,vis);
    // cout<<ans.path+" @ "+to_string(ans.wsf)<<endl;
    // display(graph);
    cout<<hamiltonianPath(0,vis,0,"")<<endl;
    // addEdge(graph,0,6,11);
    // cout<<hamiltonianCycle(0,0,vis,"",0)<<endl;
}

int main(){
    solve();
    return 0;
}