
/// Time - 1594ms
/// Easy One 

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=50000+1001;

int sparsemx[MAXN][20];
int sparsemn[MAXN][20];
int lg[MAXN];

 /// sparse[i][j] means that from ith index what is the minimum element of next 2^j elements including ith element
// Fills sparse table in bottom up manner.
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
int mx_query(int L,int R)
{
     int j = lg[R - L + 1];

    if (sparsemx[L][j] >= sparsemx[R - (1 << j) + 1][j])
        return sparsemx[L][j];

    else
        return sparsemx[R - (1 << j) + 1][j];
}

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
   int n,q,a;
   while(scanf("%d%d",&n,&q)==2)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a);
            sparsemn[i][0]=a;
            sparsemx[i][0]=a;
        }

        buildSparseTablemx(n);
        buildSparseTablemn(n);

        while(q--)
        {
            int L,R;
            scanf("%d%d",&L,&R);
            L--;
            R--;
            printf("%d\n",mx_query(L,R)-mn_query(L,R));
        }
    }
   return 0;
}
