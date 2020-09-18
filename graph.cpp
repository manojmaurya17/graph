#include<iostream>
#include<vector>
#include<queue>

using namespace std;

// class to represent edge of the graph
class Edge{
    //Instance variable
    public:
    int v = 0;
    int w = 0;
    // constructor
    Edge(int v,int w){
        this->v = v;
        this->w = w;
    }
};

// global graph to make sure we don't need to pass it every where
const int n = 7;
// this is the array of vector<Edge*>
vector<Edge*>graph[7]; // vector<vector<Edge*>> graph(7,vector<Edge*>()); 

//function to add the edge in the graph
void addEdge(int u,int v,int w){
    // since it is a bidirectional graph so we need to add edge in both list
    graph[u].push_back(new Edge(v,w));
    graph[v].push_back(new Edge(u,w));
}
 
// function to display the graph
void display(){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(int j=0;j<graph[i].size();j++){
            cout<<" ("<<graph[i][j]->v<<","<<graph[i][j]->w<<") ";
        }
        cout<<"\n";
    }
}

// function to create the graph
void createGraph(){
    // adding edges to graph
    addEdge(0,1,10);
    addEdge(0,3,10);
    addEdge(1,2,10);
    addEdge(2,3,40);
    addEdge(3,4,2);
    addEdge(4,5,2);
    addEdge(4,6,8);
    addEdge(5,6,3);
    // adding edge to make a cycle in graph
    // addEdge(0,6,20);
    // displaying the graph
    // display();
}

// removing the an edge from the graph
void removeEdge(int u,int v){
    // first finding the edge connected with vertex u
    for(int i=0;i<graph[u].size();i++){
        if(graph[u][i]->v==v){
            // after finding poping the edge from the graph
            graph[u].erase(graph[u].begin()+i);
            break;
        }
    }
    // then finding the edge connected with vertex v
    for(int i=0;i<graph[v].size();i++){
        if(graph[v][i]->v==u){
            // after finding poping the edge
            graph[v].erase(graph[v].begin()+i);
            break;
        }
    }
}

// removing vertex from the graph
void removeVertex(int v){
    // first calculating the size of the array
    int len = graph[v].size(); 
    for(int i=len-1;i>=0;i--){// then finding the neighbors of this vertex
        removeEdge(graph[v][i]->v,v); // and then erasing the all edges of the neighbors
    }
}

// function to find if there is a path between two node or not
bool hasPath(int src,int dest,vector<bool> &vis,string ans){
    if(src==dest){ // base case when src becomes equal to destination
        cout<<ans<<to_string(dest)<<endl; // then first we will print the path
        return true; // and then returning true that we find the answer
    }
    vis[src] = true; // marking the src vertex that it is now visited
    bool res = false; // bool variable which stops the call when we found the answer
    for(Edge* e:graph[src]){// then iterating to all the neighbors of the src node
        if(!vis[e->v]){ // when the node we are going to visit is not visited
            res = res || hasPath(e->v,dest,vis,ans+to_string(src)+" "); // then we call to this node
        }
    }
    return res; // and finally returning the result that either we found the path or not
}

// function to find the all path between to vertex in the graph
int allPath(int src,int dest,vector<bool> &vis,string ans){
    if(src==dest){ // base case when src becomes equal to destination
        cout<<ans<<to_string(dest)<<endl; // then first we will print the path
        return 1; // and then returning 1 that means we find one answer
    }
    vis[src] = true; // marking the src vertex that it is now visited
    int count = 0;// variable to store the count of the number of path
    for(Edge* e:graph[src]){// then iterating to all the neighbors of the src node
        if(!vis[e->v]){ // when the node we are going to visit is not visited
            count += allPath(e->v,dest,vis,ans+to_string(src)+" "); // then we call to this node
        }
    }
    vis[src] = false; // on returning again marking as false that we can again visit this vertex 
    return count; // and finally returning the result that either we found the path or not
}

// hamiltonian path is a path in which the path consist all vertex such that they all are visited only once
int count = 0; // it will store that number of vertex are visited
void hamiltonianPath(int src,vector<bool> &vis,string ans){
    vis[src] = true; // first marking the source node is visited
    count++; // incrementing the count of visited vertex
    if(count == vis.size()){ // when the count of visited will became equal to the number of vertex
        cout<<ans+to_string(src)<<endl; // when all vertex gets visited then printing that path
        return; // and after that returning to the parent 
    }
    for(Edge* e:graph[src]){// visiting all of the neighbors of the src to 
        if(!vis[e->v]){// when next node is not visited
            hamiltonianPath(e->v,vis,ans+to_string(src)+" "); // then going to the neighbor vertex
        }
    }
    count--; // we will be here when the path is not exist with this node so decreasing the count 
    vis[src] = false; // and making it again false
}

int countOfHP = 0; // variable to store the count of the number of the path
// this helper function will help to find number of hamiltonian path exist in a graph
bool helper(int src,vector<bool> &vis,string ans){
    vis[src] = true; // first marking the source node is visited
    count++; // incrementing the count of visited vertex
    if(count == vis.size()){ // when the count of visited will became equal to the number of vertex
        cout<<ans+to_string(src)<<endl; // when all vertex gets visited then printing that path
        vis[src] = false; // before returning marking it as unvisited
        count--; // so decrementing the count also
        countOfHP++;
        return true; // and after that returning to the parent 
    }
    bool res = false; // to store either the path exist or not
    for(Edge* e:graph[src]){// visiting all of the neighbors of the src to 
        if(!vis[e->v]){// when next node is not visited
            res = helper(e->v,vis,ans+to_string(src)+" "); // then going to the neighbor vertex
        }
    }
    count--; // we will be here when the path is not exist with this node so decreasing the count 
    vis[src] = false; // and making it again false
    return res; // returning the result
}

// function to find the number of hamiltonian cycle in a graph
int countHamiltonianPath(){
    for(int i=0;i<n;i++){ // iterating over all vertex to find HP from all vertex
        vector<bool> vis(n,false); //bool array to store the visited vertex
        count = 0; // always starting count from zero
        bool isExist = helper(i,vis,""); // this call helper and it will return either true or false
    }
    return countOfHP; // and then finally returning the count
}

int countOfCycle = 0; // variable to store the count of the hamiltonian cycle
// this is the helper function to calculate the number of cycle in a graph
bool helperHamiltonianCycle(int src,int st,vector<bool> &vis,string ans){
    vis[src] = true; // first marking the src vertex visited
    count++; // incrementing the count of the number of visited node
    if(count == vis.size()){ // when the count become equals to the number of vertex
        for(Edge* e:graph[src]){ // iterating over the neighbors of the src
            if(e->v == st){ // checking if there is a direct edge between the start and last vertex or not
                cout<<ans+to_string(src)+" "+to_string(e->v)<<endl; // then first printing the answer
                vis[src] = false; // making it univisited
                count--; // and decrementing the count
                countOfCycle++; // incrementing the count of number of cycle
                return true; // and then returning true to the parent
            }
        }
        vis[src] = false; // making it univisited
        count--; // and decrementing the count
        return false;
    }
    // cout<<to_string(count)+" "+to_string(src)<<endl;
    bool res = false; // assuming that till now i dont have the answer
    for(Edge* e:graph[src]){ // iterating over the neighbors of the src
        if(!vis[e->v]){ // checking if the neighbor vertex is visited or not
            res = helperHamiltonianCycle(e->v,st,vis,ans+to_string(src)+" "); // going to visit neighbor
        }
    }
    vis[src] = false; // on retuning we need to make this vertex non - visited to visit it again
    count--; // so we decrementing the count also
    return res; // returning the result
}

// function to find the hamiltonian cycle in a graph
int hamiltonianCycle(){
    for(int i=0;i<n;i++){
        count = 0; // starting count each time from 0
        vector<bool> vis(n,false); // bool array to store visited vertex
        bool isCycle = helperHamiltonianCycle(i,i,vis,""); // finding cycle
    }
    return countOfCycle; // and at last returning the count
}


void solve(){
    createGraph();
    // removeEdge(3,2);
    // removeVertex(3);
    // display();
    vector<bool> vis(n,false);
    // cout<<hasPath(6,5,vis,"");
    // cout<<allPath(2,6,vis,"");
    // hamiltonianPath(5,vis,"");
    // cout<<countHamiltonianPath()<<endl;
    // cout<<helper(0,vis,"");
    cout<<hamiltonianCycle()<<endl;
}

// function which traverse breadth first 
void bfs(int src,vector<bool>& vis){
    queue<int> q; // initialising the queue to store the vtx's
    q.push(src); // adding src to the queue
    int level = 0; // it stores the level
    while(!q.empty()){ // we iterate untill we get the queue empty
        int size = q.size(); // storing the current size of the queue
        while(size-->0){ // iterating untill the size is greater than 0
            int rmvtx = q.front(); //getting the front element in the queue
            q.pop(); // removing the front element of the queue

            if(rmvtx == 6){ // check if the removed vertex is 6
                cout<<"detected at level : "<<level<<endl; // printing the it detect on which level
            }

            if(vis[rmvtx]){ // if this node is alredy ready 
                cout<<" Cycle detected at "<<src<<" : "<<rmvtx<<endl; // it means there is cycle
                continue; // if there is cycle then we should not add their neighbour because it already 
                 // added so we continue from top
            }

            vis[rmvtx] = true; // now marking it visited so we will not visit again
            for(Edge* e:graph[rmvtx]){ // now getting neighbours of this vertex
                if(!vis[e->v]){ // then checking if the nbr vtx is visited or not
                    q.push(e->v); // if not visited than adding it to the queue
                }
            }
        }
        level++; // and then increment the level
    }
}

// gcc finding the number of connected component
int getConnectedComponent(vector<bool> &vis){
    int count = 0; // count to store the number of connected component
    for(int i=0;i<n;i++){ // iterating over all the vertex
        if(!vis[i]){ // if it is not visited previously then we will visited
            bfs(i,vis); // then applying the bfs to it
            count++; // if we enter in this condition then it means there will be one connected component
        }
    }
    return count; // then returning the count of the get connected component
}

// class to store the color of the vertex with vertex
class ColorVtx{
    // instance variable
    public:
    int v;
    int c;
    // constructor
    ColorVtx(int v,int c){
        this->v = v;
        this->c = c;
    }
};

// helper function to find if a component of a graph is bipartite or not
bool biPartite(int src,vector<int>& vis){
    queue<ColorVtx> q; // initialising the queue
    q.push(ColorVtx(src,0)); // adding source node into the queue
    while (!q.empty()){ // iterating over the queue untill we get the empty queue
        ColorVtx rm = q.front(); // fetching the first data of the queue
        q.pop(); // then removing the first element of the queue
        if(vis[rm.v]!=-1){ // if the current node is already visited
            if(vis[rm.v]!=rm.c){ //conflict // and even it has different color than it has now
                return false; // then we will return the false that means it can't be bipartite
            }
            continue; // if the color is same as the current color then we jst need to continue
                        // to our execution without again adding the child of the previous node
        }
        vis[rm.v] = rm.c; //now marking this node as visited by assigning color to the visit vector
        for(Edge* e:graph[rm.v]){ // now iterating over vertex to find its all child
            if(vis[e->v]==-1){ // and if the child is not previously visited
                q.push(ColorVtx(e->v,1-rm.c)); // then we just add it to the queue
            }
        }
    }
    return true; // now if we came out from the loop it means this graph can be bipartite 
                    // so we returning the true
}

// function to find if a graph is bipertite or not
bool isBipartite(){
    vector<int> vis(n,-1); // initialising visited vector
    bool res = true; // // storing the res
    for(int i=0;i<n;i++){ // iterating over all of the vertex to make all once a src
        if(vis[i]==-1){ // if the vtx is not visited then we will check for bipartite for it
            res = biPartite(i,vis); // calling bipartite component check function
            cout<<res<<endl; // printing what result it give
        }
        if(!res) return false; // if result is false then it can't be bipartite so returning false
    }
    return true; // else means it is bipartite
}
//==================================================================================
// Union set algo
//===================================================================================
// finding the parent of the child
// this is the path compression method
int findParent(int src, vector<int> &parent){
    if(parent[src]==src){// when parent of the src is actually src itself
        return src; // then we just return this because we need to find the parent
    }
    // if src is not parent of itself then we proceed
    
    // now we will ask the parent of src that who is your parent and 
    int par = findParent(parent[src],parent); // then it return its parent and we store it to p
    // now i need to find the top parent of this tree so we will set the parent of src to p
    // this means now the parent of src is the parent of the previous parent of src
    // by doing this we are actually reducing the height of the tree so complexity to find parent
    parent[src] = par; // this is the actual compresion line 
    // now we need to return this parent in order make this parent of all the child node
    return par; // and also we need to find the parent of src so this will return par of src
}

// this is the union function to merge the two set into one
void merger(int parent1,int parent2, vector<int>&size,vector<int>&parent){
    // now first we need to check which parent has the greater size
    // and the parent which will have the smaller size then that parent will merge
    // to the the other parent
    if(size[parent1]<size[parent2]){// when the size of the first parent is small
        // in this case we will first increase the size of the parent which has greater size
        // now in this case since the size of the parent1 is smaller hence
        // we will add this size of the parent1 to the size of the parent2
        size[parent2]+=size[parent1];  // increasing the size of the parent2
        // now also we need to change the parent of the parent1 will be parent2
        // inorder to merge this set
        parent[parent1] = parent2; // changing the parent of the parent1 set
    }else{// when either the parent1 size is greater than parent2 or equal
        // then we will add the size of the parent2 to the parent1
        // since the size of the parent2 will be greater than parent1
        // and when they both have same size then we can't decide which needs to be the child of 
        // other so we will do same in that case also as in parent2 smaller case.
        size[parent1] += size[parent2];
        // and now changing the parent of the parent2 to be the parent1
        parent[parent2] = parent1; // now the parent of parent2 will be parent1 
    }
}

// leetcode 684 redundant edge
// problem to find the edge in the tree that causes the cycle
vector<int> redundantEdge(vector<vector<int>> &edges){
    vector<int> base; // empty vector to return if no edge is found 
    if(edges.size() == 0){ // when there is not edge in the edges
        return base; // then returning the empty edge or vector
    }

    // now declaraing the vector to store the size and the parent of the each vertex in the tree
    vector<int> size, parent; // size vector to store size and parent ot store parent of each vertex
    // now since this is a tree it means it will have the one less edge than the number of vertex
    // in the tree and in this case it has one extra edge it will have same number of edges as vertex
    for(int i=0;i<edges.size();i++){ // iterating over the number of edges given
        size.push_back(1); // initialising all vertex with the size one
        parent.push_back(i); // making each vertex to parent of itself
    }

    // now fetching each edge from edges and checking its parent and if they are same then it means
    // that we have a cycle and then we return that edge
    for(vector<int> v:edges){ // fetching each edge from edges
        // finding first parent1
        int par1 = findParent(v[0]-1,parent); // finding the parent of the first vertex in the v
        // finding the second parent // -1 because in question it starts from 1
        int par2 = findParent(v[1]-1,parent); // finding the parent of the second vertex in the v
        // checking if they are same or not
        if(par1 == par2){ // and if they are same 
            // that means we have cycle in this graph
            // it means this vertex v causing the cycle in the graph do returning it 
            return  v;  // because we want to find this vertex
        }
        // if the parent are not same then we need to merge it into one or we need to union it
        // such that it gets into same set
        // and if finally we have the same parnet of all of the vertex in the graph it means we have
        // only one component in the graph and but if we have maore than one different parents in the 
        // graph then that leads to that number of component in the graph
        // so we can find the niumber of connected component in the graph
        merger(par1,par2,size,parent); // this will merge the both into one set
    }
    // now if it didn't return till this point in the graph it means we didn't have nay cycle 
    // hence we need to return the empty vector
    return base; // hence returning the empty vector
}


//================================================================
// djkstras algorithm
// In djkstra algorithm we find minimum weight distance from source to any node, to do this we will
// use the BFS approach to find minimum distance but with a chnage that when we use BFS 
// we usualy use the queue to traverse but in the djkstra we use priority queue instead,
// priority queue always pop the minimum weight element from it so we get the minimum distance
// between source and distance

// Now to find the minimum distance we need to maintain the vertex and the weight so far(wsf)
// such that priority queue finds the minimum weight so far distance element but we will
// maintain the parent vertex ,edge weight and psf also, we will create a class to store these

// function to display the new graph
vector<Edge*> newGraph[n];
void displayDjkstra(){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(int j=0;j<newGraph[i].size();j++){
            cout<<" ("<<newGraph[i][j]->v<<","<<newGraph[i][j]->w<<") ";
        }
        cout<<"\n";
    }
}


// class djkstra pair to maintain the weight so far and other properties
class dPair{
    public:
    int src=0; // source vertex
    int par=0; // parent of the source vertex
    int w=0; // weight of the edge between the src and the parent
    int wsf=0; // weight so far
    string psf = ""; // storing the path so far

    // constructor to initialise the instance variable
    dPair(int src,int par,int w,int wsf,string psf){
        this->src = src;
        this->par = par;
        this->w = w;
        this->wsf = wsf;
        this->psf = psf;
    }
    // operator overloading in the priority queue for the djkstras algorithm
    // bool operator<(dPair const &o) const // dijikstra
    // {
    //     return this->wsf > o.wsf;
    // }

    // operator overloading for the prims algo
    bool operator<(dPair const &o) const // for Prims
    {
        return this->w > o.w;
    }
};

// function to implement the djkstra algorithm
// it will take the source as an argument 
void djkstra(int src){
    vector<bool> vis(n,false); // to lookup for the visited vertex
    priority_queue<dPair> q; // queue to perform the BFS
    // at this point there is only single pt which is source hence it will doesnot have weight
    // and the parent vertex
    q.push(dPair(src,-1,0,0,to_string(src))); // adding the pair to the pq
    while(!q.empty()){// untill the queue is not empty
        dPair rm = q.top(); // fetching the element which have the minimum weight
        q.pop(); // removing the pair from the queue
        if(!vis[rm.src]){ // if the src is not visited
            if(rm.par!=-1){ // and also the parent is not null
                // then we will create the new djkstra graph
                newGraph[rm.src].push_back(new Edge(rm.par,rm.w));
                newGraph[rm.par].push_back(new Edge(rm.src,rm.w));
            }
        }else{ // and if the src is already is visited then we will continue from 
                // the starting of the while loop
            continue;
        }
        vis[rm.src] = true; // now maeking it as visited
        for(Edge* e:graph[rm.src]){ // now roaming to the neighbors 
            if(!vis[e->v]){ // if they are already not visited
                // then we will add them to the queue
                q.push(dPair(e->v,rm.src,e->w,rm.wsf+e->w,rm.psf+to_string(e->v)));
            }
        }
    } 
    // displaying the djkstra graph
    displayDjkstra();

}

// now prims algo is exactly same from the previous djkstra 
// but we will use weight only not weight so far to find minimum element
// so we will use exactly same code of the djkstra and we will just change the 
// comparator in class dPair to find with respect to weight of the edge only
void prims(int src){
    vector<bool> vis(n,false); // to lookup for the visited vertex
    priority_queue<dPair> q; // queue to perform the BFS
    // at this point there is only single pt which is source hence it will doesnot have weight
    // and the parent vertex
    q.push(dPair(src,-1,0,0,to_string(src))); // adding the pair to the pq
    while(!q.empty()){// untill the queue is not empty
        dPair rm = q.top(); // fetching the element which have the minimum weight
        q.pop(); // removing the pair from the queue
        if(!vis[rm.src]){ // if the src is not visited
            if(rm.par!=-1){ // and also the parent is not null
                // then we will create the new djkstra graph
                newGraph[rm.src].push_back(new Edge(rm.par,rm.w)); // v w
                newGraph[rm.par].push_back(new Edge(rm.src,rm.w));
            }
        }else{ // and if the src is already is visited then we will continue from 
                // the starting of the while loop
            continue;
        }
        vis[rm.src] = true; // now maeking it as visited
        for(Edge* e:graph[rm.src]){ // now roaming to the neighbors 
            if(!vis[e->v]){ // if they are already not visited
                // then we will add them to the queue
                q.push(dPair(e->v,rm.src,e->w,rm.wsf+e->w,rm.psf+to_string(e->v)));
            }
        }
    } 
    // displaying the prims graph
    displayDjkstra();

}

//========================================================================

void solveBfs(){
    createGraph(); // creating the graph
    // vector<bool> vis(n,false);
    // bfs(0,vis);
    // cout<<getConnectedComponent(vis)<<endl;
        // cout<<(boolalpha)<<isBipartite()<<endl;
        // display();
        // cout<<"==================================================\n";
        // djkstra(0);
        prims(0);

}


int main(){
    // solve();
    solveBfs();
    return 0;
}




