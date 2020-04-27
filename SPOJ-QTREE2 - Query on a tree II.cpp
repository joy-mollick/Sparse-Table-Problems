
/// Time-0.190s 
/// A must do problem for lca practice 

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

typedef long long ll;

const int MAXN=10005;
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

    /// This will return kth node from a to b , not from b to a be careful about this. kth node from a to b
    int kthnode_from_a(int a,int b,int k,int lca)
    {   /// One thing-> by binary lifting we can come up to lower level from higher level
        /// So , when a is upper level then we will find how much cover will we have to do  from b to a to find kth node from a
        /// when a is in higher level then task is half done ,we have to come up from higher level of a to (lower level) kth node
        /// But when node structure will be like a-------(lca)------b ,then by binary lifting we will not be able to pass lca to go to (lca -> b) path
        /// So, then with some calculation  we will go from b to lca , to find desire node which is kth from a
        /// Let's start
        int total_nodes_between_a_and_b;
        if(lca==a) /// a node itself is lca of a and b node ,so a is upper level we have to swap it as we will go all time from higher level to lower level
        {
            total_nodes_between_a_and_b=Lev[b]-Lev[a]+1;
            swap(a,b);
            k=total_nodes_between_a_and_b-k+1;///  this is now new k ,as we swap a and b
        }
        else if(lca==b);/// then a is on higher level and lca is q ,so only by binary lifting we can come up to kth node ,no need extra calculation

        else ///  when node structure will be like a-------(lca)------b , lca is neither a nor b but a middle node of path from a to b
        {
             if(Lev[a] - Lev[lca] + 1 < k) ///when kth node is on the path (lca->b), then we need some calculations as we have to go to desire node from b node ,not from a node
            {
              total_nodes_between_a_and_b = Lev[a] + Lev[b] - 2 * Lev[lca] + 1;
              k = total_nodes_between_a_and_b - k + 1;
              swap(a,b);/// as we will start our binary lifting journey from b to a ,so swap (a,b)
            }
        }
        /// because k is numbered from a ,where a itself is 1st node from a ,so decrease k one
        k--;
        /// three cases has been checked and new k has been calculated  ,now to use binary lifting finally to find kth node from a
         int desire_jump=k;
        /// we have to find out the same level of a which is also ancestor of b
        while(desire_jump>0) /// if difference between b and a is above zero , we can reduce it by binary lifting
        {
            int max_mum_power_of_i=log2(desire_jump);
            a=sparse[a][max_mum_power_of_i];
            desire_jump-=(1<<max_mum_power_of_i);
        }
        return a;
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
    int tc;
    cin>>tc;
    while(tc--)
    {
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
    par[1]=-1;
    dist[1]=0ll;/// distance from 1 to 1 is zero
    dfs(1, -1, 0); ///tree is rooted at 1
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    string command;
    int k,a,b,lca;
    while(cin>>command)
    {
        if(command=="DONE") break;
        else if(command=="DIST")
        {
            cin>>a>>b;
        ll distance;
        lca=lca_query(a,b);
        distance=dist[a]+dist[b]-2ll*dist[lca];
        cout<<distance<<endl;
        }
        else
        {
            cin>>a>>b>>k;
            lca=lca_query(a,b);
            cout<<kthnode_from_a(a,b,k,lca)<<endl;
        }
    }
    ///cout<<endl;/// blank line between every testcase
    }
	return 0;
}
