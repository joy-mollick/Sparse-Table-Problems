
/// Time -0.124s

class Solution {
public:
static const int MAXN=100001;
int sparsemn[MAXN][30];
int lg[MAXN];
int arr[MAXN];
 /// sparse[i][j] means that from ith index what is the minimum element of next 2^j elements including ith element
void buildSparseTablemn(int n)
{
    /// Initialize because ,2^0=1 that means from i if we take 1 element ,that is definitely our arr[i] element

    /// Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; (i + (1 << j) - 1) < n; ++i) {
            if (arr[sparsemn[i][j - 1]]<=arr[sparsemn[i + (1 << (j - 1))][j - 1]])
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

    if (arr[sparsemn[L][j]] <= arr[sparsemn[R - (1 << j) + 1][j]])
        return sparsemn[L][j];

    else
        return sparsemn[R - (1 << j) + 1][j];
}

int getMaxAreaRec( int l, int r)
{
    if (l > r)  return INT_MIN;
    if (l == r)  return arr[l]; /// both boundary is same

    int m = mn_query( l, r);
    /* Return maximum of following three possible cases
       a) Maximum area in Left of min value (not including the min)
       a) Maximum area in right of min value (not including the min)
       c) Maximum area including min */
    return max(getMaxAreaRec( l, m-1), max(getMaxAreaRec( m+1, r), (r-l+1)*(arr[m]) ));
}
    int largestRectangleArea(vector<int>& heights) {
        int n=heights.size();
        if(n==0) return 0;
        for(int i=0;i<n;i++) { arr[i]=heights[i];sparsemn[i][0]=i;if(i>1)lg[i]=lg[i>>1]+1;}
        lg[n]=lg[n>>1]+1;
        buildSparseTablemn(n);
        return getMaxAreaRec(0,n-1);
    }
};
