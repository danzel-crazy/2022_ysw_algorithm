#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <list>

using namespace std;

int main() {
//    ifstream fin("/Users/guoyun/Desktop/演算法上課資料/Algorithm code/HW 9/input.txt");
    ifstream fin("input.txt");
//    ofstream fout("/Users/guoyun/Desktop/演算法上課資料/Algorithm code/HW 9/output.txt");
    ofstream fout("output.txt");
    int t; fin >> t;
    while (t--) {
        int e; fin >> e;
        map<string, pair<bool, list<string>>> vertex;
        while (e--) {
            string v1, v2; fin >> v1 >> v2;
            vertex[v1].first = 0;
            vertex[v1].second.push_back(v2);
            vertex[v2].first = 0;
            vertex[v2].second.push_back(v1);
        }
        set<string> s1, s2;
        queue<pair<string, bool>> q;
        q.push({"0", false});
        vertex["0"].first = 1;
        int total = 0;
        while (!q.empty()) {
            string front = q.front().first;
            bool ff = q.front().second;
            q.pop();
            for (auto i : vertex[front].second) {
                if (vertex[i].first == 0) {
                    q.push({i, !ff});
                    vertex[i].first = 1;
                }
            }
            if (ff) {
                s1.insert(front);
                total++;
            }else {
                s2.insert(front);
                total++;
            }
            if (total == vertex.size()) {
                break;
            }
        }
//        for (auto i : s1) cout << i << " "; cout << endl;
//        for (auto i : s2) cout << i << " "; cout << endl;
        if ((s1.size() == 2 && s2.size() != 0) || (s2.size() == 2 && s1.size() != 0)) {
            if (*s1.begin() == "0") {
                fout << "0";
                auto it = s1.begin(); it++;
                for (; it != s1.end(); it++) {
                    fout << "," << *it;
                }
                fout << "\n";
            }else {
                fout << "0";
                auto it = s2.begin(); it++;
                for (; it != s2.end(); it++) {
                    fout << "," << *it;
                }
                fout << "\n";

            }
        }else {
            fout << "-1\n";
        }
    }
    return 0;
}