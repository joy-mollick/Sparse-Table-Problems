
/// Time-0.60s

#include <bits/stdc++.h>
using namespace std;

const int MAX=100002;
const int k=(int)log2(MAX)+1;


int sparse[MAX][k];
int lg[MAX];

 /// sparse[i][j] means that from ith index what is the minimum element of next 2^j elements including ith element
// Fills sparse table in bottom up manner.
void buildSparseTable(int n)
{
    /// Initialize because ,2^0=1 that means from i if we take 1 element ,that is definitely our arr[i] element

    /// Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            if (sparse[i][j - 1]<sparse[i + (1 << (j - 1))][j - 1])
                sparse[i][j] = sparse[i][j - 1];
            else
                sparse[i][j] = sparse[i + (1 << (j - 1))][j - 1];
        }
    }
}

/// Returns minimum of arr[L..R]
int mn_query(int L,int R)
{
     int j = lg[R - L + 1];

    if (sparse[L][j] <= sparse[R - (1 << j) + 1][j])
        return sparse[L][j];

    else
        return sparse[R - (1 << j) + 1][j];
}

// Driver program
int main()
{
   for(int i=2;i<MAX;++i) lg[i]=lg[i>>1]+1;
   int tc;
   scanf("%d",&tc);
   int caso=1;
   while(tc--)
   {
   int n,q,l,r;
   scanf("%d%d",&n,&q);
   for(int i=0;i<n;++i) scanf("%d",&sparse[i][0]);
   buildSparseTable(n);
   printf("Scenario #%d:\n",caso++);
   while(q--)
   {
       scanf("%d%d",&l,&r);
       l--;r--;
       printf("%d\n",mn_query(l,r));
   }
   }
   return 0;
}
