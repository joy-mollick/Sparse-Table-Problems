
/// It is basic LCA problem ,it can be solved by sparse table ,segment tree .etc...
/// Time-0.22s

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

const int MAXN=200002;
int sparse[MAXN][22];
int lg[MAXN];
int  V[MAXN+1]={0}, E[2*MAXN]={0}, Lev[2*MAXN]={0}, trav_num[MAXN+1]={0}, P[MAXN+1]={-1}, K=0;
bool disc[MAXN];

vector<int> graph[MAXN];

void SparseTable(int N) {

		for (int j = 1; 1 << j <= N; j++) {
		    for (int i = 0; i + (1 << j) - 1 < N; i++) {
		        if (Lev[sparse[i][j - 1]] < Lev[sparse[i + (1 << (j - 1))][j - 1]]) {
		            sparse[i][j] = sparse[i][j - 1];
		        } else {
		            sparse[i][j] = sparse[i + (1 << (j - 1))][j - 1];
		        }
		    }
		}

	}
 int mn_query(int i, int j) {
        int k = log2(j - i + 1);
        if(Lev[ sparse[i][k] ] <= Lev[ sparse[j - (1<<k) + 1][k] ]) { return sparse[i][k]; }
        else { return sparse[j - (1<<k) + 1][k]; }
    }

    /// It is for finding level number and traversing and keeping those dfs number by trav_num array

void dfs(int v, int d, int &k) {
    trav_num[v] = k;
    E[k] = v;
    Lev[k++] = d;
    disc[v]=true;
    for(int i=0;i<graph[v].size();i++) {
    	int u = graph[v][i];/// u, child of v
        if (!disc[u]) {
            P[u] = v;
            dfs(u, d+1, k);
            E[k] = v;
            Lev[k++] = d;
        }
    }
}
void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();} }

int main() {
    fast;
    for(int i=2;i<MAXN;i++) lg[i]=lg[i>>1]+1;
    int tc,caso=1;
    cin>>tc;
    while(tc--)
    {
    int m,N,x,y;
    cin >> N;
    init_search(N);
    for(int i=1;i<=N;i++)
    {
        cin >> m;
        y=i;
        while(m--)
        {
            cin>>x;
        graph[x].push_back(y);
        graph[y].push_back(x);
        }
    }
    K=0;
    dfs(1, 1, K); //tree is rooted at 1
    int n=2*N;
    for(int i=0;i<n; i++) { sparse[i][0] = i; }
    SparseTable(n);
    cout<<"Case "<<caso<<":"<<endl;
    int q;
    cin>>q;
    /// Per query we have to find out the index of minimum lev's index of the range of trav_num of l and r
    /// Then according to that minimum level's index we will print out E[i] ,which will be our answer
    while(q--)
    {
    int l, r;
    cin>>l>>r;
    int lca = E[mn_query(min(trav_num[l], trav_num[r]), max(trav_num[l], trav_num[r]) )];
    cout<<lca<<endl;
    }
    caso++;
    }
	return 0;
}
