#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
// directed graph implementation
// class edge
class Edge{
    public:
    int v;
    int w;

    Edge(int v,int w){
        this->v = v;
        this->w = w;
    }
};

// Graph
int n = 8;
vector<vector<Edge*>> graph(n,vector<Edge*>());

// function to add edge in the graph
void addEdge(int u,int v,int w){
    graph[u].push_back(new Edge(v,w));
}

// function to display the graph
void display(){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(Edge* e:graph[i]){
            cout<<"("<<e->v<<","<<e->w<<") ";
        }
        cout<<endl;
    }
}

// creating all edge or graph
void createGraph(){
    // graph 1
    // addEdge(7,5,1);
    // addEdge(7,6,1);
    // addEdge(5,2,1);
    // addEdge(5,4,1);
    // addEdge(6,4,1);
    // addEdge(6,3,1);
    // addEdge(2,1,1);
    // addEdge(3,1,1);
    // addEdge(1,0,1);
    
    // graph 2
    addEdge(0,1,1);
    addEdge(1,2,1);
    addEdge(2,3,1);
    addEdge(0,6,1);
    addEdge(7,4,1);
    addEdge(4,5,1);
    addEdge(5,3,1);
    addEdge(7,6,1);
}

// topological sort or level order traversal helper function
void topologicalSortDFS(int src,vector<bool>& vis,stack<int> &st){
    vis[src] = true; // first marking this vertex visited
    for(Edge* e:graph[src]){ // then going to the nbr's
        if(!vis[e->v]){ // if the are not visited
            topologicalSortDFS(e->v,vis,st); // then visit them
        }
    }
    st.push(src); // when we reach end from where we have to go back then we add src into stack
}

// function to print graph in topological order
void findTopoDFS(){
    stack<int> st;  // creating stack or we can use vector also
    vector<bool> vis(n,false); // creating boolean vector to store the visited vtx
    for(int i=0;i<n;i++){ // iterating for each vtx
        if(!vis[i]){ // and if it it not visited
            topologicalSortDFS(i,vis,st); // then calling topology to it
        }
    }
    while(!st.empty()){ // we will iterate untill we get the stack empty
        cout<<st.top()<<" "; // printing the stacks top element
        st.pop(); // and removing the top element from the stack
    }
}

void khansAlgo(){
    vector<int> incomming(n,0); // this vector is used to store the incoming edge of the vertex
    for(vector<Edge*> v:graph){ // iterating over all vertex of the graph
        for(Edge* e:v){ // visiting the each edge to find the number of incoming edge
            incomming[e->v]++; // incrementing the no of incoming edge to vertex
        }
    }

    queue<int> q,ans; // declaring the queue to store visited and answer
    for(int i=0;i<n;i++){ // iterating over the incoming array to find vtx 
        if(incomming[i]==0){ // whose incoming value is zero 
            q.push(i); // we will add that vtx to the queue
        }
    }

    while(!q.empty()){ // now we will iterate over the queue untill it will get empty
        int vtx = q.front(); // first fetching the first element
        q.pop(); // then removing the first element
        ans.push(vtx); // adding that vtx into the answer
        for(Edge* e:graph[vtx]){ // now we will iterate over the nbrs of the removed vtx
            if(--incomming[e->v]==0){ // first we will decrement its value then if it became 0
                q.push(e->v);// then we will add it to the queue
            }
        }
    }
    while(!ans.empty()){// iterating over  the answer queue
        cout<<ans.front()<<" "; // and then printing the topological sort
        ans.pop(); // and poping the element from the queue
    }
}



void solve(){
    createGraph();
    // display();
    // findTopoDFS();
    cout<<endl;
    // khansAlgo();
}


int main(){
    solve();
    return 0;
}