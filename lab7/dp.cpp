#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;
int ans = 0;
bool check = false;

bool compare(string a, string b){
    return a.length() > b.length();
}

int wordbreak1(string s, unordered_set <string> dict){
    if(dict.size() == 0){
        return 0;
    }

    int longest = 0;
    for(string word : dict){
        longest = max(longest, (int)word.size());
    }

    vector <int> dp(s.size()+1);
    dp[0] = 0;
    for(int i = 1; i < dp.size(); i++){
        dp[i] = -1;
    }

    for(int i = 1; i <= s.size(); i++){
        for(int j = i - 1; j >= max(i-longest, 0); j--){
            if(dp[j] != -1){
                //cout << "j: " << j << endl;
                string word = s.substr(j, i-j);
                //cout << word << endl;
                if(dict.find(word) != dict.end()){
                    if(dp[i] == -1) dp[i] = dp[j] + 1;
                    else dp[i] = min(dp[i], dp[j]+1);
                    //cout << "len " << i << " " << dp[i] << endl;
                }
            }
        }
    }

    return dp[s.size()];
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
        unordered_set <string> dictionary;
        while(n--){
            string a;
            infile >> a;
            dictionary.insert(a);
        }
        //sort(dictionary.begin(), dictionary.end(), compare);
        //for(auto v: dictionary) cout << v << endl;
        string test;
        infile >> test;

        int ans = wordbreak1(test, dictionary);
        if(ans == -1){
            //cout << "-1" << endl;
            outfile << "-1" << endl;
        }
        else{
            //cout << "len :" << ans << endl;
            outfile << ans << endl;
        }
    }
    infile.close();
    outfile.close();
    return 0;
}