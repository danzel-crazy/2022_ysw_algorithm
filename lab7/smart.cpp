#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<int> wordBreak(string s, vector<string> wordDict) {
    //vector<pair<bool, vector<string>>> dp(s.size() + 1);
    vector<pair<bool, vector<int>>> dp(s.size() + 1);
    dp[0].first = true;
    dp[0].second;
    unordered_map<string, bool> mp;
    for (int i = 0; i < wordDict.size(); i++)   mp[wordDict[i]] = true;
    for (int i = 1; i <= s.size(); i++) {
        for (int j = 0; j < i; j++) {
            string sub = s.substr(j, i - j);
            if ((dp[j].first) && mp[sub]) {
                //cout << sub << endl;
                dp[i].first = true;
                vector <int> ans = dp[j].second;
                //vector<string> v;
                for (int k = 0; k < ans.size(); k++) {
                    //v[k].push_back(' ');
                    //v[k].append(sub);
                    ans[k] += 1;
                }
                //if (v.empty())  v.push_back(sub);
                if(ans.empty()) ans.push_back(1);
                dp[i].second.insert(dp[i].second.begin(), ans.begin(), ans.end());
            }
        }
    }
    return dp.back().second;
}

int main(){
    ifstream infile;
    ofstream outfile;
    infile.open("input.txt");
    outfile.open("output.txt");
    int t;
    infile >> t;
    while(t--){
        int n;
        infile >> n;
        vector <string> dictionary;
        while(n--){
            string a;
            infile >> a;
            dictionary.push_back(a);
        }
        string test;
        infile >> test;

        vector <int> ans = wordBreak(test, dictionary);
        if(ans.size() == 0){
            //cout << "-1" << endl;
            outfile << "-1" << "\n";
            continue;
        }

        int a = ans[0];
        for(int i = 1; i < ans.size(); i++){
            if(a > ans[i]) a = ans[i];
        }
        //cout << a << endl;
        outfile << a << "\n";
    }
    infile.close();
    outfile.close();
    return 0;
}