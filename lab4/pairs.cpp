#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define M 2147483649
long long int counter = 0;

void merge(vector <long long int> &a, int front , int mid, int end){
    vector <long long int> left(a.begin()+front, a.begin()+mid+1);
    vector <long long int> right(a.begin()+mid+1, a.begin()+end+1);

    left.insert(left.end(), M);
    right.insert(right.end(), M);

    int idxLeft = 0, idxRight = 0;

    int j = 0;
    int last = 0;
    int no_answer= 0;
    for(int i = 0 ; i < left.size(); i++){
            for(j = last; j < right.size(); j++){
                if((left[i]*2) <= right[j]){
                    //cout << LeftSub[i] << " " << RightSub[j] << " " << RightSub.size()-j << " ";
                    counter += right.size()-j-1;
                    last = j;
                    break;
                }
            }
    }

    for (int i = front; i <= end; i++){
        if(left[idxLeft] <= right[idxRight] ) {
            a[i] = left[idxLeft];
            idxLeft++;
        }
        else{
            a[i] = right[idxRight];
            idxRight++;
        }
    }
}

void mergesort(vector <long long int> &a, int front , int end){
    if(front < end){
        int mid = (front + end) / 2;
        //cout << mid << endl;
        mergesort(a, front, mid);
        mergesort(a, mid + 1, end);
        merge(a, front, mid, end);
    }
}

int main(){
    ifstream infile;
    infile.open("input.txt");
    ofstream outfile("output.txt");
    
    int test;
    long long int val;
    infile >> test;
    while(test--){
        counter = 0;
        int len;
        vector <long long int> a;
        infile >> len;
        while(len--){
            infile >> val;
            a.push_back(val);
        }
        mergesort(a, 0, a.size()-1);
        
        outfile << counter << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}