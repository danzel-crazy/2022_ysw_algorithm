#include <iostream>
#include <fstream>

using namespace std;

bool valid(int n, int row, int col, int rboard[], int cboard[], int left[], int right[]){
    if(rboard[row] == 0 && cboard[col] == 0 && left[row+col] == 0 && right[(row-col + n*2 -1) % (n*2 - 1)] == 0){
        return true;
    }
    else return false;
}

int queen(int n, int m, int rboard[], int cboard[], int left[], int right[])
{
    int count = 0;
    int row = 0, col = 0;
    int preRow[50] = {0};
    int preCol[50] = {0};
    int putQueen = 0;

    while(row < n)
    {
        if(rboard[row] == 1) //exist
        {
            row++;
            continue;
        }

        while(col < n)
        {
            if(valid(n,row, col, rboard, cboard, left, right)){
                rboard[row] = 1;
                cboard[col] = 1;
                left[row+col] = 1;
                right[(row-col + n*2 -1) % (n*2 - 1)] = 1;
                
                putQueen++;
                
                preRow[putQueen] = row;
                preCol[putQueen] = col;
                
                col = 0;
                break;
            }
            col++;
        }

        if(rboard[row] == 0) 
        {
            if(putQueen == 0) break;
            if(putQueen == 0 && row == (n-1)) return count;  
            row = preRow[putQueen];
            
            col = preCol[putQueen];
            rboard[row] = 0;
            cboard[col] = 0;
            left[row+col] = 0;
            right[(row-col + n*2 -1) % (n*2 - 1)] = 0;
            //cout << "pre: " << row << col << endl;
            col++;
            putQueen--;
            continue;
        }

        if(putQueen == n-m) //find queen
        {
            count++;
            
            rboard[preRow[putQueen]] = 0;
            cboard[preCol[putQueen]] = 0;
            left[preRow[putQueen]+preCol[putQueen]] = 0;
            right[(preRow[putQueen]-preCol[putQueen] + n*2 - 1)  % (n*2 - 1)] = 0;

            col = preCol[putQueen] + 1;
            
            putQueen--;
            continue;
        }
        row++;
    }
    return count;
}

int main()
{
    int test;

    ifstream infile;
    infile.open("input.txt");
    ofstream outfile("output.txt");

    infile >> test;
    while(test--)
    {
        int n;
        int m;
        int rboard[50] = {0};
        int cboard[50] = {0};
        int left[100] = {0};
        int right[100] = {0};

        infile >> n >> m;

        int r,c;

        for(int i=0; i<m; i++)
        {
            infile >> r >> c;
            rboard[r] = 1;
            cboard[c] = 1;
            left[r+c] = 1;
            right[(r-c + n*2 - 1) % (n*2 - 1)] = 1;
        }

        int num = queen(n, m, rboard, cboard, left, right);
        outfile <<  num << endl;
        
    }

    infile.close();
    outfile.close();
    return 0;
}