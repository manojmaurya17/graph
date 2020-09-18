#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;

int main(){
    // vector<string> words = {"POON","PLEE","SAME","PLEA","POIE","PLIE","POIN"};
    vector<string> words = {"hot","dot","dog","lot","log","cog"};
    // string start = "TOON";
    string start = "hit";
    // string target = "PLEA";
    string target = "cog";
    // queue<string> q;
    // q.push(start);
    // set<string> st;
    // st.insert(start);
    // int level = 0;
    // while(!q.empty()){
    //     int size = q.size();
    //     while(size--){
    //         string rm = q.front();
    //         q.pop();
    //         if(rm==target){
    //             cout<<level+1<<endl;
    //             return 0;
    //         }
    //         for(string s:words){
    //             int diff = 0;
    //             int strLen = s.length();
                
    //             for(int i=0;i<strLen;i++){
    //                 if(rm[i]!=s[i]){
    //                     diff++;
    //                 }
    //             }
    //             if(diff==1){
    //                 if(st.find(s)==st.end()){
    //                     q.push(s);
    //                     st.insert(s);
    //                 }
    //             }
    //         }
    //     }
    //     for(auto i = st.begin();i!=st.end();i++){
    //         cout<<*i<<" ";
    //     }
    //     cout<<endl;
    //     level++;
    //     // cout<<level<<endl;
    // }

    // creating the graph
    queue<string> q;
    q.push(start);
    int level = 0;
    // map<string,bool> mp;
    //     for(string s:words){
    //         mp[s] = false;
    //     }
    set<string> st;
    st.insert(start);
    for(string s:words){
        st.insert(s);
    }
        // mp[start] = true;
        string alpha = "abcdefghijklmnopqrstuvwxyz";
    while(!q.empty()){
        int size = q.size();
        while(size--){
            string rm = q.front();
            q.pop();
            if(rm==target){
                return level+1;
            }
            for(char ch:alpha){
                for(int i=0;i<rm.size();i++){
                    string s = rm.substr(0,i)+ch+rm.substr(i+1);
                    if(st.find(s)!=st.end()){
                        // mp[s] = true;
                        st.erase(s);
                        q.push(s);
                    }
                }
            }
            
        }
        level++;
        for(auto i = st.begin();i!=st.end();i++){
            cout<<*i<<" ";
        }
        cout<<endl;
    }return 0;
}