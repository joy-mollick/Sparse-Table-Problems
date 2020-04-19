
/// Time - 0.08s

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
   int n;
   scanf("%d",&n);
   for(int i=0;i<n;i++) scanf("%d",&arr[i]);
   buildSparseTable(n);
   int q,l,r;
   scanf("%d",&q);
   while(q--)
   {
       scanf("%d%d",&l,&r);
       printf("%d\n",query(min(l,r),max(l,r)));
   }
   return 0;
}
