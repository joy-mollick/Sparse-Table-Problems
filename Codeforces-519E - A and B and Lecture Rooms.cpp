
/// Time-0.186s
/// Excellent problem 
/// A must do problem which only need LCA 
/// Neat and Clean Understandable Code 

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
int  num_of_child_of_this_node[MAXN];
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

   int pthnodefromb(int b,int p) {
       int dif_between_lev=p;
        while(dif_between_lev>0)
        {
            int max_mum_power_of_i=log2(dif_between_lev);
            b=sparse[b][max_mum_power_of_i];
            dif_between_lev-=(1<<max_mum_power_of_i);
        }
        return b;
    }

void dfs(int v,int parent,int lvl)
{
    num_of_child_of_this_node[v]=1;
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
        num_of_child_of_this_node[v]+=num_of_child_of_this_node[u];
    }
}

void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();length[i]=0ll;} }

int main()
{
    ///fast;
    int m,N,x,q,y;
    ll l;
    scanf("%d",&N);
     init_search(N+1);
    for(int i=1;i<=N-1;i++)
    {
        scanf("%d%d",&y,&x);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    Lev[0]=-1;
    par[1]=-1;
    dfs(1, -1, 1);
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    int a,b,c;
    scanf("%d",&q);
    for(int j=0;j<q;j++)
    {
        scanf("%d%d",&a,&b);
        int ans;
        int lev_distance=abs(Lev[a]-Lev[b]);
        /// when both a and b are equal then all nodes are equal distance from a and b
        if(a==b)
        {
            printf("%d\n",N);
        }
        /// when there is no mid point of point a and b,there is no such node

        else if(lev_distance%2==1)
        {
            printf("0\n");
        }

        /// There can be lca in the exactly middle point of two nodes a and b ,then all nodes in two subtree one lca(a,b)+1->a and lca(a,b)+1->b will be minus because other all nodes from the upper subtree of lca will be equidistance from a and b
        else if(Lev[a]==Lev[b])/// when the level's of a and b are equal but not same node ,then these have obviously have lca which is situated from equidistance from these
        {
             ans=N;
            int Lca=lca(a,b);
            int distance_from_a_lca=Lev[a]-Lev[Lca];
            int node_just_before_a_lca=pthnodefromb(a,distance_from_a_lca-1);
            ans=ans-num_of_child_of_this_node[node_just_before_a_lca];
            int distance_from_b_lca=Lev[b]-Lev[Lca];
            int node_just_before_b_lca=pthnodefromb(b,distance_from_b_lca-1);
            ans=ans-num_of_child_of_this_node[node_just_before_b_lca];
            printf("%d\n",ans);
        }

        else/// when ancestor of two nodes are a itself assuming a is lower level ,then find its mid point and count its children without the children in which path b is situated
        {
            int mid_distance_between_a_and_b=(Lev[a]+Lev[b])-2*Lev[lca(a,b)];
            mid_distance_between_a_and_b=mid_distance_between_a_and_b/2;
            if(Lev[a]>Lev[b]) swap(a,b);
            int dist_between_a_lca=(Lev[a]-Lev[lca(a,b)]);
             mid_distance_between_a_and_b=mid_distance_between_a_and_b-dist_between_a_lca;///now the distance only in the lca to b path
            /// assuming b is in higher level
            int dist_between_lca_b=Lev[b]-Lev[lca(a,b)];
            int mid_node=pthnodefromb(b,dist_between_lca_b-mid_distance_between_a_and_b);
            ans=num_of_child_of_this_node[mid_node];
            int just_before_node_mid_point_of_a_b=pthnodefromb(b,dist_between_lca_b-mid_distance_between_a_and_b-1);
            ans=ans-num_of_child_of_this_node[just_before_node_mid_point_of_a_b];
            printf("%d\n",ans);
        }
    }

	return 0;
}
