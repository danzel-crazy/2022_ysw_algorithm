#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct node{
    double first, second;
    node(double p, double r, double half){
        first = p - sqrt(r * r - half * half);
        second = p + sqrt(r * r - half * half);
    }    
};

bool compare(node a, node b){
    return a.first < b.first; 
}

int minimal(vector<node> circle, double l){
    if(circle.empty()) return -1;
    if(circle[0].first > 0) return -1;
    
    int ans = 0;
    double right_max = 0;
    double left = 0;
    for(int i = 0; i < circle.size(); i++){
        bool good = false;
        for(int j = i; j <circle.size() && circle[j].first <= left; j++){
            if(circle[j].second > right_max){
                right_max = circle[j].second;
                good = true;
                i = j;
            }
        }
        if(good){
            ans++;
            left = right_max;
            if(left >= l){
                return ans;
            }
        }
        else return -1;
    }
    return -1;
}

int main(){
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    for(int i=0; i<936; i++){
        int n;
        double l, w, half;
        infile >> n >> l >> w;
        half = w /2;

        vector<node> circle;
        while(n--){
            double p, r; 
            infile >> p >> r;
            if(r >= half){
                circle.push_back(node(p,r,half));
            }
        }
        sort(circle.begin(), circle.end(),compare);
        outfile << minimal(circle,l) << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}