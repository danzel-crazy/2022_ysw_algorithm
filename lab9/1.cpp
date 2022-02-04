#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;

ifstream infile;
ofstream outfile;
void possibleBipartition(int n, unordered_map<int , vector<int>> graph) {
    //unordered_map<int, vector<int>> graph;
    vector<bool> color(n, false);
    vector<bool> isVisited(n, false);
    queue<int> q;
    
    for(int i=0; i<n; i++){
        if(isVisited[i])
            continue;
        color[i]=true;
        q.push(i);
        while(!q.empty()){
            int curNode = q.front();
            q.pop();
            isVisited[curNode] = true;
            for(auto child: graph[curNode]){
                if(isVisited[child]){
                    if(color[child] != !color[curNode]){
                        outfile << -1 << endl;
                        return;
                    }
                    continue;
                }
                color[child] = !color[curNode];
                q.push(child);
            } 
        }
    }

    outfile << "0";
    for(int i = 1 ; i < color.size(); i++){
        if(color[i] == color[0]){
            outfile << "," << i;
        }
        //cout << i << " " << color[i] << endl;
    }
    outfile << endl;
    return;
}


int main(){
    infile.open("input.txt");
    outfile.open("output.txt");
    int i, n;
    //infile >>  n;
        unordered_map<int , vector<int>> adj;
        vector<vector<int>> d;
        //infile >> i;
        while(infile >> i){
            while(i--){
                int a, b;
                infile >> a >> b;
                //cout << a << b << endl;
                adj[a].push_back(b);
                adj[b].push_back(a);
            } 
            possibleBipartition(adj.size(), adj);
        }
    infile.close();
    outfile.close();
    return 0;
}