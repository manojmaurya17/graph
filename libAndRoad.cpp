#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

vector<int> par;
vector<int> size;
int findParent(int src){
    if(par[src]==src) return src;
    return par[src] = findParent(par[src]);

}

void merger(int p1,int p2){
    if(size[p1]<size[p2]){
        par[p1] = p2;
        size[p2]+=size[p1];
    }else{
        par[p2] = p1;
        size[p1]+=size[p2];
    }
}

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    long long cost = 0;
    long long component = 0;
    for(int i=0;i<n;i++){
        par.push_back(i);
        size.push_back(1);
        component++;
    }
    for(vector<int> v:cities){
        int p1 = findParent(v[0]-1);
        int p2 = findParent(v[1]-1);
        if(p1!=p2){
            component--;
            merger(p1, p2);
        }
    }
    
    cost = (long)((n-component)*c_road) + (long)(component*c_lib);
    long long libCost = (long)n*c_lib;
    par.clear();
    size.clear();
    return min(libCost,cost);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
