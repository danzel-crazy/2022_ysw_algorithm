#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Circle{
    double start,end;
    Circle(double pos, double radius, double half_w2){
        start = pos - sqrt(radius*radius - half_w2);
        end = pos + sqrt(radius*radius - half_w2);
    }    
};

int MinimalCover(vector<Circle> circles, double l){
    if(circles.empty()) return -1;
    if(circles[0].start > 0) return -1;
    
    int num = 0;
    double newLeft = 0;
    double maxRight = 0;
    for(int i=0; i<circles.size(); i++){
        bool nextCircle = false;
        for(int j=i; j<circles.size() && circles[j].start <= newLeft; j++){
            if(circles[j].end > maxRight){
                maxRight = circles[j].end;
                nextCircle = true;
                i = j;
            }
        }
        if(nextCircle){
            num++;
            newLeft = maxRight;
            if(newLeft >= l){
                return num;
            }
        }
        else return -1;
    }
    return -1;
}

bool compare(Circle c1, Circle c2){
    return c1.start < c2.start; //increasing
}

int main(){
    ifstream file("input.txt");
    ofstream ofile("output.txt");
    for(int i=0; i<936; i++){
        int n;
        double l, w, half_w, half_w2;
        file >> n >> l >> w;
        half_w = w /2;
        half_w2 = half_w * half_w;

        vector<Circle> circles;
        int count = 0;
        for(int j=0; j<n; j++){
            double p, r; file >> p >> r;
            if(r >= half_w){
                circles.push_back(Circle(p,r,half_w2));
            }
        }
        sort(circles.begin(), circles.end(),compare);
        ofile << MinimalCover(circles,l) << endl;
    }

    file.close();
    ofile.close();
    return 0;
}