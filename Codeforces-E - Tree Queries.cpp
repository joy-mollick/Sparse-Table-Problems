
/// Time-0.436s
/// Code is neat and clean and understandable
/// No need to make explanation
/// A must do problem
/// Tricky Nice Problem 

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

typedef long long ll;

const int MAXN=200002;
int sparse[MAXN][20];
int  Lev[MAXN]={0};
int par[MAXN]={-1};
bool disc[MAXN];
int Maxlog;
///int  val[MAXN];
///ll cost[MAXN];

vector< int > graph[MAXN];

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

    int kthfrom_p_node(int p, int k)
    {
       int dif_between_lev=k;
        while(dif_between_lev>0)
        {
            int max_mum_power_of_i=log2(dif_between_lev);
            p=sparse[p][max_mum_power_of_i];
            dif_between_lev-=(1<<max_mum_power_of_i);
        }
        return p;
    }

    ///
void dfs(int v,int parent,int lvl)
{
    Lev[v] = lvl ;
    int i , sz = graph[v].size();
    int  u ;
    disc[v] = true;
    par[v]=parent;
    for ( i = 0 ; i < sz ; i++ )
    {
        u = graph[v][i];
        if( disc[u]) continue;
        dfs(u,v,lvl+1);
    }
}

int dist(int a,int b)
{
    return (Lev[a]+Lev[b]-2*Lev[lca(a,b)]);
}

void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();} }

int main()
{
    ///fast;
    int m,N,x,y,q;
    scanf("%d%d",&N,&q);
     init_search(N+1);
    for(int i=1;i<=N-1;i++)
    {
        scanf("%d%d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    par[1]=-1;
    dfs(1, -1, 1);
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    while(q--)
    {
        int mxlev=-1;
        int mLevnode;
        int m;
        scanf("%d",&m);
        int arr[m];
        for(int i=0;i<m;i++)
        {
            scanf("%d",&arr[i]);
            if(Lev[arr[i]]>mxlev)/// keep track of max levelth node ,which can be used as our reference node with whom we can compare our other node
            {
                mxlev=Lev[arr[i]];
                mLevnode=arr[i];
            }
        }
        bool flag=true;
        for(int i=0;i<m;i++)
        {
            if(arr[i]==mLevnode) continue;
            int distance_between_this_node_and_reference=dist(arr[i],mLevnode);
            int distance_between_reference_and_lca=dist(mLevnode,lca(arr[i],mLevnode));
            if((distance_between_this_node_and_reference-distance_between_reference_and_lca)>1)
                {
                flag=false;
                }
        }
        if(flag)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
	return 0;
}
