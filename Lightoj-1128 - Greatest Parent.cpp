/// Time-0.440s
/// Nice problem , for LCA 
/// Easy 

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

typedef long long ll;

const int MAXN=100005;
int sparse[MAXN][20];
///int lg[MAXN];
///int  Lev[MAXN]={0},;
int par[MAXN]={-1};
///bool disc[MAXN];
int Maxlog;
///int mxlength,mnlength;
int  val[MAXN];

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


    int greatest_parent(int a, int b)
    {
        for(int i=Maxlog;i>=0;i--)
        {
            if(sparse[a][i]!=-1 && val[sparse[a][i]]>=b)
            {
                 a=sparse[a][i];
                 ///return a;
            }
        }
        return a;/// sparse[a][0] , now print the just parent of this node
    }

    ///
    /*
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
*/
///void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();dist[i]=0;} }

int main() {
    ///fast;
    int tc;
    scanf("%d",&tc);
    int caso=1;
    while(tc--)
    {
    int m,N,x,y,q;
    scanf("%d%d",&N,&q);
    ///cin >> N>>q;
    ///init_search(N+1);
    for(int i=1;i<=N-1;i++)
    {
        scanf("%d%d",&par[i],&val[i]);
        ///cin>>par[i]>>val[i];
    }
    par[0]=-1;
    val[0]=1;/// distance from 1 to 1 is zero
    ///dfs(0, -1, 0); ///tree is rooted at 1
    Maxlog=(int)(ceil)(log2(N));
    buildsparsetable(N);
    int a,b;
    printf("Case %d:\n",caso);
    ///cout<<"Case "<<caso<<":"<<endl;
    while(q--)
    {
        scanf("%d%d",&a,&b);
        ///cin>>a>>b;
        int lca=greatest_parent(a,b);
        printf("%d\n",lca);
        ///cout<<lca<<endl;
    }
    caso++;
    }
	return 0;
}
