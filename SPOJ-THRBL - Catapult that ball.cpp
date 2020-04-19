/// Time-0.04s
/// Very Nice problem of RMQ 
/// You have to just find out the index of maximum element of that range 

#include <bits/stdc++.h>
using namespace std;

const int MAX=100001;
const int k=(int)log2(MAX)+1;


int sparse[MAX][k];
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
            if (arr[sparse[i][j - 1]]>arr[sparse[i + (1 << (j - 1))][j - 1]])
                sparse[i][j] = sparse[i][j - 1];
            else
                sparse[i][j] = sparse[i + (1 << (j - 1))][j - 1];
        }
    }
}

/// Returns minimum of arr[L..R]
int mx_query(int L,int R)
{
     int j = (int)log2(R - L + 1);

    if (arr[sparse[L][j]] >= arr[sparse[R - (1 << j) + 1][j]])
        return sparse[L][j];

    else
        return sparse[R - (1 << j) + 1][j];
}

// Driver program
int main()
{
   int n,q;
   scanf("%d%d",&n,&q);
   for(int i=0;i<n;i++) scanf("%d",&arr[i]);
   buildSparseTable(n);
   int l,r;
   int ans=0;
   while(q--)
   {
       scanf("%d%d",&l,&r);
       l--;r--;
       if(l<r){
       int mx_indx=mx_query(l,r-1);
       if(arr[mx_indx]==arr[l]) {ans++;}
       }
       else
       {
           int mx_indx=mx_query(r+1,l);
       if(arr[mx_indx]==arr[l]) {ans++;}
       }
   }
   printf("%d\n",ans);
   return 0;
}
