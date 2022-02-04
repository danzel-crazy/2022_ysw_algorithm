#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
using namespace std;

int ans = 0;
bool finish = false;

bool compare(pair <double, double> a, pair <double, double> b){
    return a.first < b.first;
}

void minimal(vector <pair<double, double>> circle, double l){
    if(circle.empty() || circle[0].first > 0) return;

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
            ans += 1;
            if(left >= l){
                finish = true;
                return;
            }
        }
        else{
            return;
        }
    }
    return;
}

int main(){
    ifstream infile;
    fstream outfile;
    infile.open("input.txt");
    outfile.open("output.txt");
    
    double n, l, w;
    for(int i = 0 ; i < 936; i++){
        infile >> n >> l >> w;
        ans = 0;
        finish = false;
        double half = w/2;
        vector <pair<double, double>> circle;
        while(n--){
            double p, r;
            infile >> p >> r;
            if(r >= half){
                double left = (p - sqrt(r*r - half*half));
                double right = (p + sqrt(r*r - half*half));
                circle.push_back({left, right});
            }
        }
        sort(circle.begin(), circle.end(), compare);
        // sort(circle.begin(), circle.end(), compare);
        // for(auto v:circle){
        //    cout << v.first << " " << v.second << endl;
        // }
        
        minimal(circle, l);
        //cout << good << endl;
        if(finish){
            //cout << ans << "\n";
            outfile << ans << "\n";
        }
        else{
           //cout << "-1" << "\n";
           outfile << "-1\n";
        }
    }

    infile.close();
    outfile.close();
    return 0;
}