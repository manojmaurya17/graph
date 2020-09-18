#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// declaring the parent and the size vector
vector<int> parent;
vector<int> size;

//==================================================================================
// Union set algo
//===================================================================================
// finding the parent of the child
// this is the path compression method
// i can use this method with char and int both
int findParent(int src){
    if(parent[src]==src){// when parent of the src is actually src itself
        return src; // then we just return this because we need to find the parent
    }
    // if src is not parent of itself then we proceed
    // now we will ask the parent of src that who is your parent and 
    int par = findParent(parent[src]); // then it return its parent and we store it to p
    // now i need to find the top parent of this tree so we will set the parent of src to p
    // this means now the parent of src is the parent of the previous parent of src
    // by doing this we are actually reducing the height of the tree so complexity to find parent
    parent[src] = par; // this is the actual compresion line 
    // now we need to return this parent in order make this parent of all the child node
    return par; // and also we need to find the parent of src so this will return par of src
}

// this is the union function to merge the two set into one
void merger(int parent1,int parent2){
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
//===================================================================
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
        int par1 = findParent(v[0]-1); // finding the parent of the first vertex in the v
        // finding the second parent // -1 because in question it starts from 1
        int par2 = findParent(v[1]-1); // finding the parent of the second vertex in the v
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
        merger(par1,par2); // this will merge the both into one set
    }
    // now if it didn't return till this point in the graph it means we didn't have nay cycle 
    // hence we need to return the empty vector
    return base; // hence returning the empty vector
}

//============================================================================
//================================================================================
// leetcode 1061
// smallest lexicographical string
// we will given two string which will be equal now we will given another string 
// and we need to convert that string into smallest lexicographical string
// like if we have parker and morris so it means
// p = m ,a = o, r = r, k = r, e = i,and r = s so now we need to convert the string
// parser into smallest lexicographical  string which will look like makkek
void lexicographicalMerger(char parent1,char parent2){
    // first we will check the lexicagraphical order of the parent1 and parent2
    // then the parent who will be higher in lexicographical order will be child of
    // the parent who has lower order
    
    // on directly applying comparision operation on character so first they cnvert
    // into ascii value then according to that number the compare each other
    // lexicographically
    if(parent1<parent2){ // when the lexicographical order of the parent1 is low
        // since parent1 comes first in lexicographical order
        // hence the parent of the parent2 will be parent1 
        parent[parent2-'a'] = parent[parent2-'a'] < parent1?parent[parent2-'a']:parent1; // changing the parent of parent2
    }else{ // when parent2 comes first in lexicographical order
        parent[parent1-'a'] = parent[parent1-'a'] < parent2?parent[parent1-'a']:parent2; // then changin the parent of the parent1
    }
} 

// Now the main function to find smallest lexicographical string
void smallestLexicographicalString(){
    // initiallising the parent array
    for(int i=0;i<26;i++){
        parent.push_back('a'+i);
    }


    // string to make union set
    // string first = "leetcode";
    // string second = "programs";
    string first = "hello";
    string second = "world";
    // string first = "parker";
    // string second = "morris";
    // string to find lexicographically smallest string
    // string third = "sourcecode";
    string third = "hold";
    // string third = "parser";
    // first we need to find the parent for each of the character into the string
    // so initially we made each character to parent of itself
    // creating the union set
    for(int i=0;i<first.length();i++){ // iterating over the size of the first string
        parent[first[i]-'a'] = first[i]; // initialising first parent
        parent[second[i]-'a'] = second[i]; // initialising second parent
    }

    // now we have the parent vector which consist each character as its parent
    // now we will find the lexicographically smallest parent of these character
    for(int i=0;i<first.length();i++){ // iterating over the first string size
        char parent1 = findParent(first[i]); // finding the parent of the character of first string
        char parent2 = findParent(second[i]); // finding the parent of the character of second string
        if(parent1 != parent2){ // when parent1 is not equal to parent2
            lexicographicalMerger(parent1,parent2); // merging these two set of charcter into one using lexicographical order
        }
    }

    // this string will contain the answer
    string ans = ""; // to store answer string
    for(int i=0;i<third.length();i++){ // iterating over third string
        ans+=findParent(third[i]); // finding the required parent and adding the charcter to answer
    }
    cout<<ans<<endl; // printing the final answer

}

//============================================================
// leetcode 200 number of island using dsu
// to apply dsu we need to thave relation or edge between two vertex
// to make them parent and child and in this case we can assume that each
// each element in matrix have 1 are connected through horizontal and
// vertical path

// now in this island problem we have a matrix which has 1 and 0 so we can
// assume it as the graph adjacency matrix representation so now we have edges
// which has 1 in the value
// so now we can apply dsu here

// now we will use functions findParent and the merger from above and the parent
// and size vector

// this is my approach
int numberOfIslands01(vector<vector<char>> &grids){
    int n = max(grids.size(),grids[0].size()); // getting max of the row or column
    for(int i=0;i<n;i++){ // iterating over
        parent.push_back(i); // filling parent
        size.push_back(1); // filling size
    }
    // assuming as the given gird is the adjacency matrix representation of the graph
    for(int i=0;i<grids.size();i++){ // iterating on rows
        for(int j=0;j<=grids[0].size();j++){ // iterating on columns
            if(grids[i][j] == 1){ // when we get one at the position
                int par1 = findParent(i); // we will find the parent of i
                int par2 = findParent(j); // then parent of j
                if(par1!=par2){ // and if they will be not equal to then 
                    merger(par1,par2); // we will merge
                }
            }
        }
    }
    int count = 0; // count to store the number of islands
    int val = -1; // it stores the component parent
    for(int i=0;i<n-1;i++){ // iterating over the parent array
        int v = parent[i]; // fetching parent of i
        if(val!=v){ // if they are equal
            count++; // we will increment the count
            val = v; // and change the value
        }
    }
    return count; // then we will return the count
}
// this is my approach but this is not efficient so i will not use it

// now another approach 
// now we will make parent array of the size of the number of elements in the grids
// and then we do the same with this 1d parent array
int numberOfIslands02(vector<vector<int>> grids){
    if(grids.size()==0) return 0;// if the grid is empty then islands will be 0
    // now first we need to fill the parent array with the size of the number of 
    // element in the grid and we need to have a variable to store the count of 
    // position where the value is 1
    int oneCount = 0; // count of ones in the grid
    // iterating over the grid to increment the oneCount and to fill the 
    // parent and size array
    int n = grids.size(); // variable tp store the number of rows in the grid
    int m = grids[0].size(); // variable to store the number of columns in the grid

    for(int i=0;i<n;i++){ // iterating over the row
        for(int j=0;j<m;j++){ // iterating over the column
            if(grids[i][j]=='1'){ // when current position have value 1
                oneCount++; // then incrementing the count of ones in grid
            }
            parent.push_back(i*m+j);// filling the parent by its own index value
            size.push_back(1); // filling the size with 1
        }
    }


    for(int i=0;i<n;i++){ // iterating over the rows
        for(int j=0;j<m;j++){ // iterating over the columns
            if(grids[i][j]=='1'){ // when the position have the value 1
                if(j+1<m && grids[i][j+1]=='1'){ // when the right element also have one
                    int par1 = findParent(i*m+j); // finding the parent of the vertex i*m+j in 1d
                    int par2 = findParent(i*m+j+1); // finding the parent of next of above vtx i*m+j+1 in 1d
                    // if par1 and par2 became equals then it means there is a cycle between 
                    // or the vtx already belong to this parent so we didn't need to do anything
                    // and if we asked for the cycle then we can return at this point to tell
                    // that there is a graph in there
                    if(par1!=par2){ // so when they are different
                        oneCount--; // so we need to decrease the count because we are going to merge this par1
                        merger(par1,par2);// then merging these parent on the basis of their size
                    }
                }
                if(i+1<m && grids[i+1][j]=='1'){ // when the below element also have one
                    int par1 = findParent(i*m+j); // finding the parent of the vertex i*m+j in 1d
                    int par2 = findParent((i+1)*m+j+1); // finding the parent of below of above vtx (i+1)*m+j+1 in 1d
                    // if par1 and par2 became equals then it means there is a cycle between 
                    // or the vtx already belong to this parent so we didn't need to do anything
                    // and if we asked for the cycle then we can return at this point to tell
                    // that there is a graph in there
                    if(par1!=par2){ // so when they are different
                        oneCount--; // so we need to decrease the count because we are going to merge this par1
                        merger(par1,par2);// then merging these parent on the basis of their size
                    }
                }

            }
        }
    }
    return oneCount; // then returning the number of component of the islands

}

// ====================================================================================

// kruskal algorithm to find the minimum spanning tree in the graph
// since we are doing this using the union set so we don't need to 
// draw the graph in this case we can work through directed edges vector
// now do perform kruskal we need to first sort the edges vector according to
// the weight of the each edge, to do this we will use this sort function with 
// user defined comaparator
void kruskalAlgoForMST(vector<vector<int>> &edges){
    // using sort function to sort the edges by weight
    // passing the user defined constructor
    sort(edges.begin(),edges.end(),[](vector<int> &a, vector<int> &b){
        return a[2] < b[2];
    });
    int minimumSpanningTreeWeight = 0; // storing the weight of the minimum spanning tree
    int n = edges.size(); // storing the number of edges to build the parent and size arr
    for(int i=0;i<n;i++){ // iterating over the number of edges
        parent.push_back(i); // building the parent array
        size.push_back(1); // building the size array
    }
    for(vector<int> v:edges){ // iterating over the edges
        int par1 = findParent(v[0]); // finding the parent of u
        int par2 = findParent(v[1]); // find the parent of v
        if(par1!=par2){ // if their parent is not same then we merge them
            // this is where we build the kruskal graph
            // newGraph[v[0]].push_back(new Edge(v[1],v[2]));
            // newGraph[v[0]].push_back(new Edge(v[1],v[2]));
            minimumSpanningTreeWeight+=v[2]; // adding weight to spanning tree weight
            merger(par1,par2); // mergin both parents
        }
    }
}

// =============================================================
// Journey to moon
// we need to make pair such that they both should not belong to the same country
// so we can use dsu here to group all of the people of same country
// then we will calculate the no of ways by combination of 2 people from different group

// this is the union function to merge the two set into one
void mergerMoon(int parent1,int parent2){
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
        size[parent1] = 0; // making its value zero

    }else{// when either the parent1 size is greater than parent2 or equal
        // then we will add the size of the parent2 to the parent1
        // since the size of the parent2 will be greater than parent1
        // and when they both have same size then we can't decide which needs to be the child of 
        // other so we will do same in that case also as in parent2 smaller case.
        size[parent1] += size[parent2];
        // and now changing the parent of the parent2 to be the parent1
        parent[parent2] = parent1; // now the parent of parent2 will be parent1 
        size[parent2] = 0;// making it zero
    }
}

// function to find number of ways to send a pair such that they both 
// belong to different country
int journeyToMoon(vector<vector<int>> &sameRegionPeople){
    for(int i=0;i<sameRegionPeople.size();i++){ // iterating over the edges
        parent.push_back(i); // building the parent array
        size.push_back(1); // building the size array
    }

    for(vector<int> v:sameRegionPeople){ // iterating over the number of edges
        int par1 = findParent(v[0]); // finding parent of u
        int par2 = findParent(v[1]); // finding parent of v
        if(par1!=par2){ // if their parents are different
            merger(par1,par2); // so we merge them
        }
    }
    // to calculate number of ways we need to multiply every+
     
    // every possible non zero pair and then add then
    // so to do this we will use the mathematical formula
    // (a+b+c)^2 = a^2+b^2+c^2+2(a*b+b*c+c*a)
    // therefor a*b+b*c+c*a = ((a+b+c)^2-(a^2+b^2+c^2))/2
    long long sumOfSquare = 0; // so these variable will store sum of the squares
    long long sqaureOfSum = 0; // this will store the square of the sum
    for(int i=0;i<sameRegionPeople.size();i++){ // now iterating over the size arr
        if(size[i]!=0){ // if this is not zero
            sumOfSquare+=size[i]*size[i]; // adding square of size into sum of square
            sqaureOfSum+=size[i]; // and adding size to square of sum
        }
    }
    return (sqaureOfSum*sqaureOfSum-sumOfSquare)/2; // this is the sum of product of each pair
}

//=========================================================
// adding pipe or well
// we need to find the minimum cost to give the access of the water to the every city
// either we can join the pipe or we can create the well also 
// so we will use the dsu here to form it

// function to find the ways to add well and pipe
long pipesAndWell(int n,long c_pipe,long c_well,vector<vector<int>> cities){
    int component = n; // initial there will be n components
    for(int i=0;i<n;i++){ 
        parent.push_back(i); // building the parent
        size.push_back(1); // building the size
    }
    for(vector<int> v:cities){ // iterating over the cities 
        int par1 = findParent(v[0]); // finding parent of u
        int par2 = findParent(v[1]); // finding parent of v
        if(par1!=par2){ // if their parent is not equal
            component--; // decreasing component as we are merging them
            merger(par1,par2); // merging these parents
        }
    }
    // now we have to calculate the cost to build the pipe or well
    // so we need to decide either we will build wells at all places or 
    // we will add pipes with some wells, so we need to calculate
    // the number of pipes or edges we need so it will be always
    // the number of vertices minus the number of component
    // in the dsu because in dsu we make tree and the number od=f edges in the
    // tree always will be the one less than the number of vertices
    // and if we have more than one component then it will decreases that
    // many edges from the graph, after calculating the no of edges or pipes needed
    // we multiply it with the cost of making pipe and the number of wells needed
    // by multiplying them with their cost
    // now there may be chances that the cost of pipes is grater then making well so
    // then we will prefer making well at each cities rather to connect them throug pipes
    long long cost = (long)((n-component)*c_pipe)+(long)(component*c_well); // cost with pipes
    long long costOnlyWell = (long)n*c_well; // cost without pipes
    parent.clear(); //clearing the par for other test case because we have global parent
    size.clear(); // also global size
    return min(cost,costOnlyWell); //now returning the minimum cost
}


// ===========================================================================
// mr president problem
// we need to convert the roads into the super roads such that we can make the cost of maintainance
// reach only to k cost
// to do this we will use the dsu approach

    

//============================================================
int main(){
    smallestLexicographicalString();
    return 0;
}   