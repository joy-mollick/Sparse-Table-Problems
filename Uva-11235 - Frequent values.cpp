#include <bits/stdc++.h>

using namespace std;

const int MAX=100002;
const int k=(int)log2(MAX)+1;


int sparse[MAX][k];
int lg[MAX];
int arr[MAX];

 /// sparse[i][j] means that from ith index what is the minimum element of next 2^j elements including ith element
// Fills sparse table in bottom up manner.
void buildSparseTable(int n)
{
    /// Initialize because ,2^0=1 that means from i if we take 1 element ,that is definitely our arr[i] element

    /// Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            if (sparse[i][j - 1]>=sparse[i + (1 << (j - 1))][j - 1])
                sparse[i][j] = sparse[i][j - 1];
            else
                sparse[i][j] = sparse[i + (1 << (j - 1))][j - 1];
        }
    }
}

/// Returns minimum of arr[L..R]
int mx_query(int L,int R)
{
     if(L>R) return 0;

     int j = lg[R - L + 1];

    if (sparse[L][j] >= sparse[R - (1 << j) + 1][j])
        return sparse[L][j];

    else
        return sparse[R - (1 << j) + 1][j];
}

// Driver program
int main()
{
   for(int i=2;i<MAX;++i) lg[i]=lg[i>>1]+1;
   int caso=1,n,q,l,r;
   while(scanf("%d%d",&n,&q)!=EOF && n)
   {
       for(int i=0;i<n;i++) scanf("%d",&arr[i]);
      int num_of_occurences_from_left[n];
      num_of_occurences_from_left[0]=1;/// it will store consecutively how many same numbers are together i.e. side by side
      for(int i=1;i<n;i++)
      {
          if(arr[i]==arr[i-1]) num_of_occurences_from_left[i]=num_of_occurences_from_left[i-1]+1;
          else num_of_occurences_from_left[i]=1;
      }
      for(int i=0;i<n;i++) sparse[i][0]=num_of_occurences_from_left[i];
      buildSparseTable(n);
      while(q--)
      {
          scanf("%d%d",&l,&r);
          l--;r--;
          int iterat=l;
          while(iterat<=r && arr[iterat]==arr[iterat-1]) iterat++;
          /// now just compare this iterat-l with RMQ of other part of this interval,because only starting part is the problem so clear that problem by iterating over the same value now other all part is counted from left side so , there is no need to change anything else
          int ans=max(mx_query(iterat,r),iterat-l);
          printf("%d\n",ans);
      }
   }
   return 0;
}
