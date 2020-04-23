
/// Time-2.210s
/// Same as SPOJ distance query of two nodes 

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;


const int MAXN=100005;
int sparse[MAXN][20];
int sparsemx[MAXN][20];
int sparsemn[MAXN][20];
int lg[MAXN];
int  Lev[MAXN]={0},par[MAXN]={-1};
bool disc[MAXN];
int Maxlog;
int mxlength,mnlength;
int dist[MAXN];

vector< pair<int,int> > graph[MAXN];

 void buildsparsetable(int N)
{
      int i, j;

    for (i = 0; i < N; i++){
    for (j = 0; 1 << j < N; j++){
    sparsemn[i][j]=INT_MAX;
    sparsemx[i][j]=INT_MIN;
    sparse[i][j] = -1;/// initialize with -1, that means there is no ancestor of i node
    }
    }
    for (i = 0; i < N; i++){
    sparse[i][0] = par[i];
    sparsemn[i][0]=dist[i];
    sparsemx[i][0]=dist[i];
    /// initialize all node i ,for 2^0 (=1) th ancestor of i ,that is obviously ith parent
    }
    ///bottom up dynamic programing
    for (j = 1; 1 << j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            if (sparse[i][j - 1] != -1)
                {/// if 2^(j-1) th ancestor of ith node is available then proceed
                    sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];
                    sparsemx[i][j]=max(sparsemx[i][j-1],sparsemx[sparse[i][j-1]][j-1]);/// keep maximum length among the roads towards the jth ancestor of ith node
                    sparsemn[i][j]=min(sparsemn[i][j-1],sparsemn[sparse[i][j-1]][j-1]);/// keep minimum length among the roads towards the jth ancestor of ith node
                }///for first one,sparse[i][j-1] for 2^j-1 ,so for 2^j-1 *2^j-1=2^j , sparse[i][j] means 2^j the ancestor found
        }

    }

}


    void lca(int a, int b)
    {
        int log,i;
        if(Lev[a]>Lev[b]) {swap(a,b);}
        mxlength=INT_MIN;
        mnlength=INT_MAX;
        int dif_between_lev=Lev[b]-Lev[a];
        /// we have to find out the same level of a which is also ancestor of b
        while(dif_between_lev>0) /// if difference between b and a is above zero , we can reduce it by binary lifting
        {
            int max_mum_power_of_i=log2(dif_between_lev);
            mxlength=max(mxlength,sparsemx[b][max_mum_power_of_i]);
            mnlength=min(mnlength,sparsemn[b][max_mum_power_of_i]);
            b=sparse[b][max_mum_power_of_i];
            dif_between_lev-=(1<<max_mum_power_of_i);
        }
        if(b==a) return;
        /// if a is itself ancestor of a and b

 ///Now,two are on same level,so trying to reduce the level  just before that ancestor node
        for( i=Maxlog;i>=0;i--)
        {
            if(sparse[a][i]!=-1 && sparse[a][i]!=sparse[b][i])
            {
                mxlength=max(mxlength,max(sparsemx[a][i],sparsemx[b][i]));
                mnlength=min(mnlength,min(sparsemn[a][i],sparsemn[b][i]));
                a=sparse[a][i];
                b=sparse[b][i];
            }
        }
        /// now just check the length of the road adjacent with both sides of ancestor of a and b
        mxlength=max(mxlength,max(sparsemx[a][0],sparsemx[b][0]));
        mnlength=min(mnlength,min(sparsemn[a][0],sparsemn[b][0]));
        ///return par[a];/// sparse[a][0] , now print the just parent of this node
    }

    ///
void dfs(int v , int parent ,int length, int lvl)
{
    Lev[v] = lvl ;
    int i , sz = graph[v].size();
    int  u ;
    disc[v] = true;
    dist[v]=length;
    par[v]=parent;
    for ( i = 0 ; i < sz ; i++ )
    {
        u = graph[v][i].first;
        if( disc[u]) continue;
        dfs(u,v,graph[v][i].second,lvl+1);
    }
}
void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();} }

int main() {
    fast;
    int tc,caso=1;
    cin>>tc;
    while(tc--)
    {
    int m,N,x,y,c;
    cin >> N;
    init_search(N+1);
    for(int i=0;i<N-1;i++)
    {
        cin>>x>>y>>c;
        graph[x].push_back(make_pair(y,c));
        graph[y].push_back(make_pair(x,c));
    }
    par[1]=-1;
    dfs(1, -1,0, 0); //tree is rooted at 1
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    cout<<"Case "<<caso<<":"<<endl;
    int q;
    cin>>q;
    while(q--)
    {
    int l, r;
    cin>>l>>r;
    lca(l,r);
    cout<<mnlength<<" "<<mxlength<<endl;
    }
    caso++;
    }
	return 0;
}
