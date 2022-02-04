#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int ans = 0;
bool check = false;

bool compare(string a, string b){
    return a.length() > b.length();
}

void backtracking(string s, vector <string> dictionary, int total){
    if(s.length() == 0){
        if(ans == 0) ans = total;
        else if(ans > total) ans = total;
        check = true;
        return;
    }
    
    for(int i = 0; i < dictionary.size(); i++){
        string word = dictionary[i];
        string temp = s.substr(0, word.length());
        if(temp == word){
            total += 1;
            //cout << word  << " " << total << endl;
            backtracking(s.substr(word.length()), dictionary, total);
            total -= 1;
            //cout << word  << " " << total << endl;
        }
        
    }
    //if(check) return;
}

int main(){
    ifstream infile;
    ofstream outfile;
    infile.open("input.txt");
    outfile.open("output.txt");
    int t;
    infile >> t;
    while(t--){
        ans = 0;
        check = false;
        int n;
        infile >> n;
        vector <string> dictionary;
        while(n--){
            string a;
            infile >> a;
            dictionary.push_back(a);
        }
        sort(dictionary.begin(), dictionary.end(), compare);
        //for(auto v: dictionary) cout << v << endl;
        string test;
        infile >> test;

        backtracking(test, dictionary, 0);
        if(check == false){
            //cout << "-1" << "\n";
            outfile << "-1" << "\n";
        }
        else{
            //cout << ans << endl;
            outfile << ans << "\n";
        }
    }
    infile.close();
    outfile.close();
    return 0;
}