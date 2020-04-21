
///Time-0.07s
///Excellent problem , binary_search+RMQ 

#include<bits/stdc++.h>

using namespace std;
const int MAXN=100001;

int sparsemx[MAXN][22];
int lg[MAXN];

 /// sparse[i][j] means that from ith index what is the minimum element of next 2^j elements including ith element

void buildSparseTablemx(int n)
{
    /// Initialize because ,2^0=1 that means from i if we take 1 element ,that is definitely our arr[i] element

    /// Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            if (sparsemx[i][j - 1]>=sparsemx[i + (1 << (j - 1))][j - 1])
                sparsemx[i][j] = sparsemx[i][j - 1];
            else
                sparsemx[i][j] = sparsemx[i + (1 << (j - 1))][j - 1];
        }
    }
}

/// Returns minimum of arr[L..R]

int mx_query(int L,int R)
{
     int j = lg[R - L + 1];

    if (sparsemx[L][j] >= sparsemx[R - (1 << j) + 1][j])
        return sparsemx[L][j];

    else
        return sparsemx[R - (1 << j) + 1][j];
}

// Driver program
int main()
{
       for(int i=2;i<MAXN;++i) lg[i]=lg[i>>1]+1;
       int n;
       scanf("%d",&n);
       int arr[n];
       for(int i=0;i<n;++i)
       {
           scanf("%d",&arr[i]);
       }
       for(int i=0;i<n-1;i++) sparsemx[i][0]=arr[i+1]-arr[i];/// d>=arr[i+1]-arr[i] i.e.ai+d>=ai+1
       buildSparseTablemx(n);
       int q;
       scanf("%d",&q);
       int t,d;
       while(q--)
       {
           scanf("%d%d",&t,&d);
           /// ak+1>t
           int R=upper_bound(arr,arr+n,t)-arr-1;/// finding that k+1 ,if exists
           int l=0,r=R-1;
           int ans=R,mid;/// if there is no i such that d>=b[i],where b[i]=arr[i+1]-arr[i],then ans is obviusly R ,so initially ans is equalled to R 
           while(l<=r)
           {
                mid=(l+r)>>1;
                if(mx_query(mid,R-1)<=d)
                {
                    ans=mid;
                    r=mid-1;
                }
                else l=mid+1;
           }
           /// so this ans is our that i ,but 1 based so print ans+1
           printf("%d\n",ans+1);
       }
   return 0;
}
