/// Time- 0.359s
/// Nice problem

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

typedef long long ll;

const int MAXN=50005;
int sparse[MAXN][20];
int lg[MAXN];
int  Lev[MAXN]={0},par[MAXN]={-1};
bool disc[MAXN];
int Maxlog;
int mxlength,mnlength;
ll dist[MAXN];

vector< pair<int,ll> > graph[MAXN];

 void buildsparsetable(int N)
{
      int i, j;

    for (i = 0; i < N; i++){
    for (j = 0; 1 << j < N; j++){
    sparse[i][j] = -1;/// initialize with -1, that means there is no ancestor of i node
    }
    }
    for (i = 0; i < N; i++){
    sparse[i][0] = par[i];
    /// initialize all node i ,for 2^0 (=1) th ancestor of i ,that is obviously ith parent
    }
    ///bottom up dynamic programing
    for (j = 1; 1 << j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            if (sparse[i][j - 1] != -1)
                {
                    sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];

                }
        }

    }

}


    int lca_query(int a, int b)
    {
        int i;
        if(Lev[a]>Lev[b]) {swap(a,b);}
        int dif_between_lev=Lev[b]-Lev[a];
        /// we have to find out the same level of a which is also ancestor of b
        while(dif_between_lev>0) /// if difference between b and a is above zero , we can reduce it by binary lifting
        {
            int max_mum_power_of_i=log2(dif_between_lev);
            b=sparse[b][max_mum_power_of_i];
            dif_between_lev-=(1<<max_mum_power_of_i);
        }
        if(b==a) return b;
        /// if a is itself ancestor of a and b

       ///Now,two are on same level,so trying to reduce the level  just before that ancestor node
        for( i=Maxlog;i>=0;i--)
        {
            if(sparse[a][i]!=-1 && sparse[a][i]!=sparse[b][i])
            {
                a=sparse[a][i];
                b=sparse[b][i];
            }
        }
        return par[a];/// sparse[a][0] , now print the just parent of this node
    }

    ///
void dfs(int v,int parent,int lvl)
{
    Lev[v] = lvl ;
    int i , sz = graph[v].size();
    int  u ;
    ll cost;
    disc[v] = true;
    par[v]=parent;
    for ( i = 0 ; i < sz ; i++ )
    {
        u = graph[v][i].first;
        cost=graph[v][i].second;
        if( disc[u]) continue;
        dist[u]=dist[v]+cost;
        dfs(u,v,lvl+1);
    }
}
void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();dist[i]=0;} }

int main() {
    fast;
    int m,N,x,y;
    ll c;
    cin >> N;
    init_search(N+1);
    for(int i=0;i<N-1;i++)
    {
        cin>>x>>y>>c;
        graph[x].push_back(make_pair(y,c));
        graph[y].push_back(make_pair(x,c));
    }
    par[0]=-1;
    dist[0]=0ll;/// distance from 0 to 0 is zero
    dfs(0, -1, 0); ///tree is rooted at 0
    Maxlog=(int)(ceil)(log2(N));
    buildsparsetable(N);
    int q,a,b;
    cin>>q;
    while(q--)
    {
        cin>>a>>b;
        int lca=lca_query(a,b);
        ll distance=dist[a]+dist[b]-2ll*dist[lca];
        cout<<distance<<endl;
    }
	return 0;
}
