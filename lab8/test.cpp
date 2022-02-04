#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct node{
    public:
        double first, second;
        node(double p, double half, double r){
            first = (p - sqrt(r*r - half*half));
            second = (p + sqrt(r*r - half*half));
        }
};

bool compare(node a, node b){
    return a.first < b.first;
}

int minimal(vector <node> circle, double l){
    if(circle.empty()) return -1;
    if(circle[0].first > 0) return -1;
    
        int ans = 0;
        double right_max = 0;
        double left = 0;
        
        // for(auto v:circle){
        //    cout << v.first << " " << v.second << endl;
        // }

        for(int i = 0; i < circle.size(); i++){
            bool good = false;
            for(int j = i; j < circle.size() && circle[j].first <= left; j++){
                if(right_max < circle[j].second){
                    good = true;
                    right_max = circle[j].second;
                    i = j;
                }
            }
            if(good){
                left = right_max;
                ans = ans + 1;
                if(left >= l) return ans;
            }
            else{
                return -1;
            }
            
        }
    return -1;
    
}

int main(){
    ifstream infile;
    fstream outfile;
    infile.open("input.txt");
    outfile.open("output.txt");
    int n;
    double l, w;
    
    for(int i = 0 ;i < 936; i++){
        infile >> n >> l >> w;
        double half = w/2;
        vector <node> circle;
        while(n--){
            double p, r;
            infile >> p >> r;
            if(r >= half){
                circle.push_back(node(p, half, r));
            }
        }
        sort(circle.begin(), circle.end(), compare);
        // for(auto v:circle){
        //    cout << v.first << " " << v.second << endl;
        // }
        
        outfile << minimal(circle, l) << endl;
    }
        
    

    infile.close();
    outfile.close();
    return 0;
}