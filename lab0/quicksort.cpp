#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "data.hpp"
using namespace std;

void solve(tTestData *test_data){
    	    fstream output;
    	    output.open("output.txt", ios::app);
    	    
    	    int num = test_data->cnt;
    	
    	    for(int j = 0 ; j < num; j++){
    	        vector <int> temp;
    	        for(int i = 0 ; i < test_data->seq_size[j]; i++){
    	            temp.push_back(test_data->data[j][i]);
    	        }
    	
    	        quicksort(temp, 0, temp.size() - 1);
    	
                for(int i = 0; i < temp.size(); i++){
    	            output << temp[i] << " ";
    	        }
    	        output << "\n" ;
    	    }
    	
    	    output.close();
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *a, int front, int end){
    int i = front - 1;
    int pivot = end;

    for(int j = front; j < end; j++){
        if(a[j] < a[pivot]){
            i++;
            swap(&a[i], &a[j]);
        }
        else 
            j++;
    }

    i++;
    swap(&a[i], &a[pivot]);
    return i;

}

void quicksort(int *a, int front, int end){
    if(front < end){
        int pivot = partition(a, front, end);
        quicksort(a, 0, pivot - 1);
        quicksort(a, pivot + 1, end);
    }
}
