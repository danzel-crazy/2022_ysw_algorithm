#include <iostream>
#include <algorithm>
#include <vector>
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
    	
    	        sort(temp.begin(), temp.end());
    	
                for(int i = 0; i < temp.size(); i++){
    	            output << temp[i] << " ";
    	        }
    	        output << "\n" ;
    	    }
    	
    	    output.close();
}
	
