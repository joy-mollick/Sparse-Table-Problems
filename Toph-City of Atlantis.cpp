/// Time-0.40s
/// Very Nice Concept 
/// As all edges can receive same type of coins 
/// So, it is obvious that the all cost of those edges cna be made of given value of coin .think about it (same type of coin)
/// So, we will keep the gcd of a path by sparse_table so that gcd can be made of given value of coin ,if gcd of costs of some edges are divisible by given value ,so all edges can be paid by this coin value ,so continue binary lifting 


#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

typedef long long ll;

const int MAXN=100005;
int sparse[MAXN][20];
ll sparse_gcd_of_cost[MAXN][20];
///int lg[MAXN];
///int  Lev[MAXN]={0},;
int par[MAXN]={-1};
bool disc[MAXN];
int Maxlog;
int  val[MAXN];
ll cost[MAXN];

vector< pair<int,ll> > graph[MAXN];

 void buildsparsetable(int N)
{
      int i, j;
     memset(sparse,-1,sizeof(sparse));
     /*
    for (i = 0; i < N; i++){
    for (j = 0; 1 << j < N; j++){
    sparse[i][j] = -1;/// initialize with -1, that means there is no ancestor of i node
    }
    }
    */
    for (i = 1; i < N; i++){
    sparse[i][0] = par[i];
    sparse_gcd_of_cost[i][0]=cost[i];
    /// initialize all node i ,for 2^0 (=1) th ancestor of i ,that is obviously ith parent
    }
    ///bottom up dynamic programing
    for (j = 1; 1 << j < N; j++)
    {
        for (i = 1; i < N; i++)
        {
            if (sparse[i][j - 1] != -1)
                {
                    sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];
                    sparse_gcd_of_cost[i][j]=__gcd(sparse_gcd_of_cost[i][j-1],sparse_gcd_of_cost[sparse[i][j-1]][j-1]);
                }
        }

    }

}


    int desire_node(int a, ll b)
    {
        for(int i=Maxlog;i>=0;i--)
        {
            if(sparse[a][i]!=-1 && __gcd(sparse_gcd_of_cost[a][i],b)==b)
            {
                 a=sparse[a][i];
            }
        }
        return a;/// sparse[a][0] , now print the just parent of this node
    }

    ///
void dfs(int v,int parent,int lvl)
{
    ///Lev[v] = lvl ;
    int i , sz = graph[v].size();
    int  u ;
    ll cst;
    disc[v] = true;
    par[v]=parent;
    for ( i = 0 ; i < sz ; i++ )
    {
        u = graph[v][i].first;
        cst=graph[v][i].second;
        if( disc[u]) continue;
        cost[u]=cst;
        dfs(u,v,lvl+1);
    }
}

void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();cost[i]=0;} }

int main()
{
    ///fast;
    int tc;
    scanf("%d",&tc);
    int caso=1;
    while(tc--)
    {
    int m,N,x,y,q;
    ll cst;
    scanf("%d",&N);
     init_search(N+1);
    for(int i=1;i<=N-1;i++)
    {
        scanf("%d%d%lld",&x,&y,&cst);
        graph[x].push_back(make_pair(y,cst));
        graph[y].push_back(make_pair(x,cst));
    }
    par[1]=-1;
    cost[1]=0ll;
    dfs(1, -1, 0); ///tree is rooted at 1
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    int a;
    ll b;
    scanf("%d",&q);
    printf("Case %d:\n",caso);
    while(q--)
    {
        scanf("%d%lld",&a,&b);
        int lca=desire_node(a,b);
        printf("%d\n",lca);
    }
    caso++;
    }
	return 0;
}
