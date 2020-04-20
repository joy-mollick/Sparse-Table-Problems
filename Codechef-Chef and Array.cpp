
/// Time limit is so strict ,you have to optimize all things 
/// Here ,I have optimized my log2 factor by precalculating 
/// Time - 0.870000s

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
            if (sparse[i][j - 1]>sparse[i + (1 << (j - 1))][j - 1])
                sparse[i][j] = sparse[i][j - 1];
            else
                sparse[i][j] = sparse[i + (1 << (j - 1))][j - 1];
        }
    }
}

/// Returns minimum of arr[L..R]
int mx_query(int L,int R)
{
     int j = lg[R - L + 1];

    if (sparse[L][j] >= sparse[R - (1 << j) + 1][j])
        return sparse[L][j];

    else
        return sparse[R - (1 << j) + 1][j];
}

// Driver program
int main()
{
   int n,q;
   scanf("%d",&n);
   for(int i=0;i<n;i++) scanf("%d",&sparse[i][0]);
   buildSparseTable(n);
   for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;/// lg value has been precalculated to reduce time complexity 
   int l,r;
   long long  ans=0;
   scanf("%d%d%d",&q,&l,&r);
   /// xi = (xi-1 + 7) mod (N - 1)
   /// yi = (yi-1 + 11) mod N
   int L,R;
   long long ansi;
   for(int i=0;i<q;i++)
   {
       if(l<r){L=l;R=r;}
       else {L=r;R=l;}
       ans+=mx_query(L,R);
       l=(l+7);
       if(l>=(n-1)){ l=l%(n-1);}
       r=(r+11);
       if(r>=n) {r=r%(n);}
   }
   printf("%lld\n",ans);
   return 0;
}
