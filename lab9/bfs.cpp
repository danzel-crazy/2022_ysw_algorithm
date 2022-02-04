#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <list>

using namespace std;

ifstream infile;
ofstream outfile;

class Graph{
public:
    int num_vertex;
    std::vector< std::list<int> > AdjList;
    int *color,             // 0:白色, 1:灰色, 2:黑色
        *distance,          // 0:起點, 無限大:從起點走不到的vertex
        *predecessor;       // -1:沒有predecessor, 表示為起點vertex

    Graph():num_vertex(0){};           // default constructor
    Graph(int N):num_vertex(N){        // constructor with input: number of vertex
        // initialize Adjacency List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void BFS(int Start);
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
    AdjList[to].push_back(from);
}

void Graph::BFS(int Start){
    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    distance = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++) {  // 初始化，如圖二(b)
        color[i] = 0;                       // 0:白色;
        predecessor[i] = -1;                // -1表示沒有predecessor
        distance[i] = num_vertex+1;         // num_vertex個vertex, 
    }                                       // 最長距離 distance = num_vertex -1條edge

    std::queue<int> q;
    int i = Start;

    for (int j = 0; j < num_vertex; j++) {  // j從0數到num_vertex-1, 因此j會走過graph中所有vertex
        if (color[i] == 0) {                // 第一次i會是起點vertex, 如圖二(c)
            color[i] = 1;                   // 1:灰色
            distance[i] = 0;                // 每一個connected component的起點之距離設成0
            predecessor[i] = -1;            // 每一個connected component的起點沒有predecessor
            q.push(i);
            while (!q.empty()) {
                int u = q.front();                  // u 為新的搜尋起點
                for (std::list<int>::iterator itr = AdjList[u].begin();        // for loop 太長
                     itr != AdjList[u].end(); itr++) {                         // 分成兩段
                    if (color[*itr] == 0) {                // 若被「找到」的vertex是白色
                        if(color[u] == 1){
                            color[*itr] = 2;
                        }
                        else{
                            color[*itr] = 1;
                        }
                        //color[*itr] = 1;                   // 塗成灰色, 表示已經被「找到」
                        distance[*itr] = distance[u] + 1;  // 距離是predecessor之距離加一
                        predecessor[*itr] = u;             // 更新被「找到」的vertex的predecessor
                        q.push(*itr);                      // 把vertex推進queue
                    }
                    else if(color[*itr] == color[u]){
                        outfile << "-1" << endl;
                        return;
                    }
                }
                q.pop();        // 把u移出queue
                //color[u] = 2;   // 並且把u塗成黑色
            }
        }
        // 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
        // 就把i另成j, 繼續檢查graph中的其他vertex是否仍是白色, 若是, 重複while loop
        i = j;
    }
    
    outfile << "0";
    for(int i = 1; i < num_vertex; i++){
        if(color[i] == color[0]){
            outfile << "," << i;
        }
    }
    outfile << endl;

    for(int i = 0; i < num_vertex; i++){
        cout << i << " " << color[i] << " ";
    }
    cout << endl;
}

int main(){
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
        cout <<  ans.num_vertex << endl;
        ans.BFS(0);
    }
    infile.close();
    outfile.close();
    return 0;
}
