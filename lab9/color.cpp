#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <fstream>

using namespace std;
ifstream infile;
ofstream outfile;

class Graph{
public:
    bool ans = true; 
    int num_vertex;
    vector<list<int> > AdjList;
    int *color,             // 0:white, 1:red, 2:blue
        *predecessor,
        *discover;         // for DFS()

    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize Adj List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void DFS(int Start);
    void DFSVisit(int vertex);

    void PrintPredecessor();
    void correct();
};

void Graph::AddEdgeList(int from, int to){
    //cout << 1 << endl;
    AdjList[from].push_back(to);
    AdjList[to].push_back(from);
}

void Graph::DFS(int start){
    //cout << num_vertex << endl;
    color = new int[num_vertex];           
    discover = new int[num_vertex];
    predecessor = new int[num_vertex];

    int time = 0;
    for(int i = 0; i < num_vertex; i++){
        color[i] = 0;
        discover[i] = 0;
        predecessor[i] = -1;
    }

    int i = start;
    for( int j = 0; j < num_vertex; j++){
        if(color[i]==0){
            color[i] = 1;
            DFSVisit(i);
        }
        if(!ans){
            outfile << "-1" << endl;
            return;
        }
        i = j;
    }
    
    outfile << "0";
    for(int i = 1; i < num_vertex; i++){
        if(color[i] == color[0]){
            outfile << "," << i;
        }
    }
    outfile << endl;
}

void Graph::DFSVisit(int vertex){

    for(list<int>::iterator itr = AdjList[vertex].begin(); itr != AdjList[vertex].end(); itr++){
        if(color[*itr]==0){
            if(color[vertex] == 1){
                color[*itr] = 2;
            }
            else{
                color[*itr] = 1;
            }
            
            predecessor[*itr] = vertex;
            DFSVisit(*itr);
        }

        else if(color[*itr] == color[vertex]){
            ans = false;
            return;
        }

    }
    //finish[vertex] = ++time;
}


int main(void){
    infile.open("input.txt");
    outfile.open("output.txt");

    int num, i, n;
    infile >>  n;
    while(n--){
        infile >> i;
        Graph ans(110);
        set <int> s;
        while(i--){
            int a, b;
            infile >> a >> b;
            ans.AddEdgeList(a,b);
            //cout << a << b << endl;
            s.insert(a);
            s.insert(b);
            
        }
        ans.num_vertex = s.size();
        ans.DFS(0);
    }
    
    infile.close();
    outfile.close();
    return 0;

}