#include<iostream>
#include<vector>
using namespace std;


vector<int> par;
vector<long long> size;
int findParent(int src){
    if(par[src]==src)return src;
    return par[src] = findParent(par[src]);
}

void merge(int p1,int p2){
    if(size[p1]<size[p2]){
        par[p1] = p2;
        size[p2]+=size[p1];
        size[p1] = 0;
    }else{

        par[p2] = p1;
        size[p1]+=size[p2];
        size[p2] = 0;
    }
}

// Complete the journeyToMoon function below.
long long journeyToMoon(int n, vector<vector<int>> astronaut) {
    if(astronaut.size()==0) return 0;
    for(int i=0;i<n;i++){
        par.push_back(i);
        size.push_back(1.0);
    }
    for(vector<int> v:astronaut){
        int p1 = findParent(v[0]);
        int p2 = findParent(v[1]);
        if(p1!=p2){
            merge(p1,p2);
        }
    }

    // int ways = 0;
    // for(int i=0;i<n;i++){
    //     for(int j=i+1;j<n;j++){
    //         if(size[i]!=0 && size[j]!=0){
    //             ways+=size[i]*size[j];
    //         }
    //     }
    // }
    long long sqs = 0;
    long long sqe = 0;
    for(int i=0;i<n;i++){
        if(size[i]!=0){
            sqs+= size[i];
            sqe += (long long)(size[i]*size[i]);
        }
    }
    return (sqs*sqs-sqe)/2;
}
int main(){
    vector<vector<int>> ast = {{1,2},{3,4}};
    int n = 100000;
    cout<<journeyToMoon(n,ast);
    return 0;
}