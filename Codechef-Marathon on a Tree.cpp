
/// Time-0.190s
/// A good problem for noobs 

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

typedef long long ll;

const int MAXN=100002;
int sparse[MAXN][20];
int  Lev[MAXN]={0};
int par[MAXN]={-1};
bool disc[MAXN];
int Maxlog;
///int  val[MAXN];
ll length[MAXN];

vector< int > graph[MAXN];

 void buildsparsetable(int N)
{
      int i, j;
     memset(sparse,-1,sizeof(sparse));
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

    int lca(int a, int b)
    {

        if(Lev[a]>Lev[b]) {swap(a,b);}

        int dif_between_lev=Lev[b]-Lev[a];
        /// we have to find out the same level of a which is also ancestor of b
        while(dif_between_lev>0) /// if difference between b and a is above zero , we can reduce it by binary lifting
        {
            int max_mum_power_of_i=log2(dif_between_lev);
            b=sparse[b][max_mum_power_of_i];
            dif_between_lev-=(1<<max_mum_power_of_i);
        }
        if(b==a) return b;/// if a is itself ancestor of a and b

 ///Now,two are on same level,so trying to reduce the level  just before that ancestor node
        for(int i=Maxlog;i>=0;i--)
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
    disc[v] = true;
    par[v]=parent;
    ll len;
    for ( i = 0 ; i < sz ; i++ )
    {
        u = graph[v][i];
        if( disc[u]) continue;
        dfs(u,v,lvl+1);
    }
}

void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();length[i]=0ll;} }

int main()
{
    ///fast;
    int m,N,x,q,y;
    ll l;
    scanf("%d%d",&N,&q);
     init_search(N+1);
    for(int i=1;i<=N-1;i++)
    {
        scanf("%d%d",&y,&x);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    Lev[0]=0;
    par[1]=-1;
    dfs(1, -1, 1);
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    int a,b,c;
    for(int j=0;j<q;j++)
    {
        scanf("%d%d%d",&a,&b,&c);
        if(((lca(a,c)==c)&&lca(a,b)==lca(c,b))||(lca(b,c)==c&&lca(a,b)==lca(a,c))) printf("YES\n");
        else printf("NO\n");
    }

	return 0;
}
