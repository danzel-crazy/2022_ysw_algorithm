#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define M 2147483649
long long int counter = 0;

void merge(long int *a, int front , int mid, int end){
    int left_size = mid-front+2;
    int right_size = end-mid+1;
    long int (*left) = new long int[left_size];
    long int (*right) = new long int[right_size];

    cout << "left: ";
    for(int i = front; i <= mid; i++){
        left[i-front] = a[i];
        cout << i-front << " " << left[i-front] << " ";
    }
    cout << "right: ";
    for(int i = mid+1 ; i <= end; i++){
        right[i-mid-1] = a[i];
        cout << i-mid-1 << " " << right[i-mid-1] << " ";
    }

    left[left_size-1] = M;
    right[right_size-1]= M;

    int idxLeft = 0, idxRight = 0;

    int j = 0;
    int last = 0;
    for(int i = 0 ; i < left_size; i++){
            for(j = last; j < right_size; j++){
                if(((left[i])*2) <= right[j]){
                    //cout << i << " " << j << endl;
                    //cout << left[i] << " " << right[j] << " " << right_size-j-1 << " " << endl;
                    counter += right_size-j-1;
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

    delete []left;
    delete []right;
}

void mergesort(long int *a, int front , int end){
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
    int q = 1;
    while(q--){
        counter = 0;
        int len;
        infile >> len;
        long int* a = new long int[len];
        int i = 0;
        while(len--){
            infile >> val;
            a[i] = val;
            i++;
        }
        /*for(int j = 0 ; j < i; j++){
            cout << a[j] << " ";
        }
        cout << endl;*/
        //cout << i << endl;
        mergesort(a, 0, i-1);
        cout << counter << endl;
        outfile << counter << endl;
        delete []a;
    }

    infile.close();
    outfile.close();
    return 0;
}