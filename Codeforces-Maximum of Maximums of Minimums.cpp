#include<bits/stdc++.h>


using namespace std;
const int MAXN=100001;

int sparsemn[MAXN][22];
int lg[MAXN];
int arr[MAXN];

 /// sparse[i][j] means that from ith index what is the minimum element of next 2^j elements including ith element
void buildSparseTablemn(int n)
{
    /// Initialize because ,2^0=1 that means from i if we take 1 element ,that is definitely our arr[i] element

    /// Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            if (sparsemn[i][j - 1]<=sparsemn[i + (1 << (j - 1))][j - 1])
                sparsemn[i][j] = sparsemn[i][j - 1];
            else
                sparsemn[i][j] = sparsemn[i + (1 << (j - 1))][j - 1];
        }
    }
}
/// Returns minimum of arr[L..R]

int mn_query(int L,int R)
{

     int j = lg[R - L + 1];

    if (sparsemn[L][j] <= sparsemn[R - (1 << j) + 1][j])
        return sparsemn[L][j];

    else
        return sparsemn[R - (1 << j) + 1][j];
}

// Driver program
int main()
{
   for(int i=2;i<MAXN;++i) lg[i]=lg[i>>1]+1;
   int n,k;
   scanf("%d%d",&n,&k);
   int arr[n];
   for(int i=0;i<n;i++) {scanf("%d",&sparsemn[i][0]);arr[i]=sparsemn[i][0];}
   buildSparseTablemn(n);
   sort(arr,arr+n);
   if(k==1) printf("%d\n",arr[0]);
   else if(k>2) printf("%d\n",arr[n-1]);
   else
   {
       int ans=INT_MIN;
       for(int i=0;i<n-1;i++)
       {
           ans=max(ans,max(mn_query(0,i),mn_query(i+1,n-1)));
       }
       printf("%d\n",ans);
   }
}
