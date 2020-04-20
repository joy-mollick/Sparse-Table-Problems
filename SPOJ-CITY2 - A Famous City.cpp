
/// Just you have to check ,if there is any height greater than two same height buldings between them then they are encountered as different buildings 
/// Time-0.320s


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
   int caso=1,n;
   while(scanf("%d",&n)!=EOF)
   {
   for(int i=0;i<n;++i) scanf("%d",&sparse[i][0]);
   buildSparseTable(n);
   map<int,int>M;
   int ans=0;
   for(int i=0;i<n;i++)
   {
       if(sparse[i][0])/// if it has height ,then enters
       {
           if(M.find(sparse[i][0])==M.end())/// this height isn't encountered ,so count this as new
           {
               ++ans;
               M[sparse[i][0]]=i;
           }
           else
           {
               int prev_position_of_this_height=M[sparse[i][0]];
               int mn_between_two_heights=mn_query(prev_position_of_this_height,i);
               if(mn_between_two_heights<sparse[i][0])/// so there is minimum height buildings between two same height buildings ,so two same height buildings are different
               {
                   ++ans;
                   M[sparse[i][0]]=i;
               }
           }
       }
   }
   printf("Case %d: %d\n",caso++,ans);
   }
   return 0;
}
