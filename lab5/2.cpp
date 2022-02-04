#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "data.hpp"
using namespace std;

#define NONE -10000001

unordered_map <int, vector <int>> chain;

void ingraph (int first, int second){
    chain[first].push_back(second);
    chain[second].push_back(first);
}   

int check(){
    int endpoint1 = NONE, endpoint2 = NONE;
    for(auto v: chain){
        if(endpoint1 == NONE && v.second.size() == 1){
            endpoint1 = v.first;
        }
        else if(endpoint2 == NONE && v.second.size() == 1){
            endpoint2 = v.first;
            break;
        }
    }
    return endpoint1 > endpoint2 ? endpoint1 : endpoint2;
}

void solve(tTestData *test_data){
    ofstream outfile("output.txt");
    int test = test_data->t;
    //cout << test_data->t << endl;
    for(int i = 0; i < test_data->t; i++){
        int num, ith;
        num = test_data->testcase[i].n - 1;
        ith = test_data->testcase[i].i;
        //cout << num << " " << ith << endl;

        for(int j = 0; j < num; j++){
            int first = test_data->testcase[i].edges[j][0], second = test_data->testcase[i].edges[j][1];
            ingraph(first, second);
        }
        
        int start = check();
        //cout << start << endl;
        int ans = start;
        if(ith==0) outfile << ans << endl;
        else{
            while(ith--){
                if(start != chain[ans][0]){
                    int temp = ans;
                    ans = chain[ans][0];
                    start = temp;
                    //cout << "0" << start << " " <<  ans << endl;
                }
                else if(start != chain[ans][1]){
                    int temp = ans;
                    ans = chain[ans][1];
                    start = temp;
                    
                    //cout << "1" << start << " " <<  ans << endl;
                }
            }
            outfile << ans;
            outfile << endl;
        }
        chain.clear();
    }
    outfile.close();
}