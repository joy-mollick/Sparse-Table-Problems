
/// Time - 0.26s
/// Sparse Table and LCA with binary lifting technique 


#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

const int MAXN=100001;
int sparse[MAXN][20];
int lg[MAXN];
int  Lev[2*MAXN]={0},par[MAXN+1]={-1}, K=0;
bool disc[MAXN];
int Maxlog;

vector<int> graph[MAXN];

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
            if (sparse[i][j - 1] != -1)/// if 2^(j-1) th ancestor of ith node is available then proceed
                    sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];///for first one,sparse[i][j-1] for 2^j-1 ,so for 2^j-1 *2^j-1=2^j , sparse[i][j] means 2^j the ancestor found
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
void dfs(int v , int parent , int lvl)
{
    Lev[v] = lvl ;
    int i , sz = graph[v].size();
    int  u ;
    disc[v] = true;
    for ( i = 0 ; i < sz ; i++ )
    {
        u = graph[v][i];
        if( disc[u]) continue;
        par[u]=v;
        ///cout<<v<<" "<<parent<<endl;
        ///dist[u]=dist[v]+
        dfs(u,v,lvl+1);
    }
}
void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();} }

int main() {
    fast;
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
    par[1]=-1;
    dfs(1, -1, 0); //tree is rooted at 1
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    cout<<"Case "<<caso<<":"<<endl;
    int q;
    cin>>q;
    while(q--)
    {
    int l, r;
    cin>>l>>r;
    int Lca = lca(l,r);
    cout<<Lca<<endl;
    }
    caso++;
    }
	return 0;
}
