
/// Normal Problem ,not good at all.
/// Time - 0.130s

#include<bits/stdc++.h>

using namespace std;
const int MAXN=100001;

int sparsemn[MAXN][40];
int sparsemx[MAXN][40];
int lg[MAXN];

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

int mn_query(int L,int R)
{

     int j = lg[R - L + 1];

    if (sparsemn[L][j] <= sparsemn[R - (1 << j) + 1][j])
        return sparsemn[L][j];

    else
        return sparsemn[R - (1 << j) + 1][j];
}

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
       for(int i=0;i<n;++i)
       {
           scanf("%d",&sparsemn[i][0]);
           sparsemx[i][0]=sparsemn[i][0];
       }
       buildSparseTablemn(n);
       buildSparseTablemx(n);
       int q;
       scanf("%d",&q);
       int l,r;
       int mx_outsde_the_range_left=0,mx_outsde_the_range_right=0,mn_int_the_range,mx_int_the_range;
       while(q--)
       {
           scanf("%d%d",&l,&r);
            mn_int_the_range=mn_query(l,r);/// m
            mx_int_the_range=mx_query(l,r);/// M
           if(l!=0)
            mx_outsde_the_range_left=mx_query(0,l-1);
           if(r!=n-1)
            mx_outsde_the_range_right=mx_query(r+1,n-1);

           int outside=max(mx_outsde_the_range_left,mx_outsde_the_range_right);///M~
           double m=mn_int_the_range;
           double M=mx_int_the_range;
           double M_minus_m_by_two=(M-m)/2.0;
           double xM=outside;
           double ans=m+max(M_minus_m_by_two,xM);
           ///cout<<xM<<" "<<M_minus_m_by_two<<endl;
           printf("%0.01lf\n",ans);
           mx_outsde_the_range_left=0;
           mx_outsde_the_range_right=0;
       }
   return 0;
}
