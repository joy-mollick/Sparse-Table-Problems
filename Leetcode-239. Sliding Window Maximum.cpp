/// Easy One 
/// Time-0.720s

class Solution {
public:
    
static const int MAXN=100001;
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

    if (sparsemx[L][j] > sparsemx[R - (1 << j) + 1][j])
        return sparsemx[L][j];

    else
        return sparsemx[R - (1 << j) + 1][j];
}

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int>ans;
        int n=nums.size();
        if(n==1) {ans.push_back(nums[0]);return ans;}
        for(int i=0;i<n;i++) {sparsemx[i][0]=nums[i];if(i>1)lg[i]=lg[i>>1]+1;}
        if(n>1) lg[n]=lg[n>>1]+1;
        buildSparseTablemx(n);
        int l=0;
        int r=l+k-1;
        while(r<=n-1)
        {
            ///cout<<l<<" "<<r<<" "<<mx_query(l,r)<<endl;
            ans.push_back(mx_query(l,r));
            l++;
            r++;
        }
        return ans;
    }
};
