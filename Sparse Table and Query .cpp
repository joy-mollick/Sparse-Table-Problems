
/// The build construction takes O(nlogn) time and space complexity and query takes only O(1) 
/// See Tushar Roy Sparse Table RMQ Tutorial Video for better Understanding 


#include <bits/stdc++.h>
using namespace std;

const int MAX=500;


int sparse[MAX][MAX];
int arr[MAX];

 /// sparse[i][j] means that from ith index what is the minimum element of next 2^j elements including ith element
// Fills sparse table in bottom up manner.
void buildSparseTable(int n)
{
    for (int i = 0; i < n; i++)
        sparse[i][0] = i; /// Initialize because ,2^0=1 that means from i if we take 1 element ,that is definitely our arr[i] element

    /// Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            if (arr[sparse[i][j - 1]]<arr[sparse[i + (1 << (j - 1))][j - 1]])
                sparse[i][j] = sparse[i][j - 1];
            else
                sparse[i][j] = sparse[i + (1 << (j - 1))][j - 1];
        }
    }
}

/// Returns minimum of arr[L..R]
int query(int L, int R)
{
    int j = (int)log2(R - L + 1);

    if (arr[sparse[L][j]] <= arr[sparse[R - (1 << j) + 1][j]])
        return arr[sparse[L][j]];

    else
        return arr[sparse[R - (1 << j) + 1][j]];
}

// Driver program
int main()
{
     ///arr[] = { 7, 2, 3, 0, 5, 10, 3, 12, 18 };
     arr[0]=7;arr[1]=2;arr[2]=3;arr[3]=0;arr[4]=5;arr[5]=10;arr[6]=3;arr[7]=12;arr[8]=18;
    int n = 9;
    buildSparseTable(n);
    cout << query(0, 4) << endl;
    cout << query(4, 7) << endl;
    cout << query(7, 8) << endl;
    return 0;
}
