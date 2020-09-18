#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


vector<int> par;
vector<int> size;
int findParent(int src){
    if(par[src] == src) return src;
    return par[src] = findParent(par[src]);
}

void merger(int par1,int par2){
    if(size[par1]<size[par2]){
        size[par2] += size[par1];
        par[par1] = par2;
    }else{
        size[par1] += size[par2];
        par[par2] = par1;
    }
}

int main(){
    int n,m;
    long long k;
    cin>>n>>m>>k;
    if(m==0){
        return -1;
    }
    vector<vector<int>> arr;
    vector<vector<int>> narr;
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        arr.push_back({a,b,c});
    }

    sort(arr.begin(),arr.end(),[](vector<int> &a,vector<int> &b){
        return a[2]<b[2];
    });

    for(int i=0;i<n;i++){
        par.push_back(i);
        size.push_back(1);
    }

    long long totalCost = 0;
    for(vector<int> v:arr){
        int p1 = findParent(v[0]);
        int p2 = findParent(v[1]);
        if(p1!=p2){
            merger(p1,p2);
            narr.push_back(v);
            totalCost += v[2];
        }
    }
    if(totalCost<k){
        return 0;
    }
    int count = 0;
    for(int i=0;i<n;i++){
        if(i==par[i]){
            count++;
        }
    }
    if(count>1){
        return -1;
    }
    sort(narr.begin(),narr.end(),[](vector<int> &a,vector<int> &b){
        return a[2]>b[2];
    });

    int trans = 0;
    for(int i=0;i<n;i++){
        if(totalCost<k){
            break;
        }
        trans++;
        totalCost = totalCost-narr[i][2]+1;
    }
    int ans = totalCost<k?trans:-1;
    cout<<ans<<endl;
    return 0;
}