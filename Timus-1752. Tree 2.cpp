
/// Time-0.281s
/// Here ,we first find two farthest nodes of the tree 
/// Nice problem 
/*
Let's find two farthest nodes in tree. Let's call it f1 and f2. It can be done by two bfs/dfs'. 
Now let's answer for queries. Let the y farthest node from x(it's f1 or f2). 
If such node exists that dist(x, z) = d, then it would lie on path from x to y. 
If dist(x, y) < d, answer would be 0. Let l be lca(x, y). 
If dist(l, x) <= d, answer would be dist(l, x)'th parent of x. 
If x is ancestor of y, answer would be (dist(x, y) - d)'th parent of y.
Otherwise answer would be dist(l, y) - (d - dist(l, x)).
*/
/// I used a normal kthnode_from_a_to_b path algorithm to find kth node in the path 

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

typedef long long ll;

const int MAXN=20002;
int sparse[MAXN][20];
int sparse1[MAXN][20];
int  Lev[MAXN]={0};
int Lev2[MAXN]={0};
int par[MAXN]={-1};
int par1[MAXN]={-1};
bool disc[MAXN];
bool vis[MAXN];
int Maxlog;
int  num_of_child_of_this_node[MAXN];
ll nmber_of_times_visited_this_node[MAXN];
pair<int,int>two_furthest_nodes;
int first;
int flev;
int second;
int seclev;

vector< int > graph[MAXN];
vector< pair<int,int> >edge;

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

void buildsparsetable1(int N)
{
      int i, j;
     memset(sparse1,-1,sizeof(sparse1));
    for (i = 0; i < N; i++){
    sparse1[i][0] = par1[i];
    /// initialize all node i ,for 2^0 (=1) th ancestor of i ,that is obviously ith parent
    }
    ///bottom up dynamic programing
    for (j = 1; 1 << j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            if (sparse1[i][j - 1] != -1)
                {
                    sparse1[i][j] = sparse1[sparse1[i][j - 1]][j - 1];
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

    int lca2(int a, int b)
    {

        if(Lev2[a]>Lev2[b]) {swap(a,b);}

        int dif_between_lev=Lev2[b]-Lev2[a];
        /// we have to find out the same level of a which is also ancestor of b
        while(dif_between_lev>0) /// if difference between b and a is above zero , we can reduce it by binary lifting
        {
            int max_mum_power_of_i=log2(dif_between_lev);
            b=sparse1[b][max_mum_power_of_i];
            dif_between_lev-=(1<<max_mum_power_of_i);
        }
        if(b==a) return b;/// if a is itself ancestor of a and b

 ///Now,two are on same level,so trying to reduce the level  just before that ancestor node
        for(int i=Maxlog;i>=0;i--)
        {
            if(sparse1[a][i]!=-1 && sparse1[a][i]!=sparse1[b][i])
            {
                a=sparse1[a][i];
                b=sparse1[b][i];
            }
        }
        return par1[a];/// sparse[a][0] , now print the just parent of this node
    }

void dfs(int v,int parent,int lvl)
{
    ///num_of_child_of_this_node[v]=1;
    Lev[v] = lvl ;
    if(lvl>flev) {flev=lvl;first=v;}
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
        ///num_of_child_of_this_node[v]+=num_of_child_of_this_node[u];
    }
}

void DFS(int v,int lvl,int parent)
{
    Lev2[v]=lvl;
    if(lvl>seclev)
    {
        seclev=lvl;
        second=v;
    }
    vis[v]=true;
    par1[v]=parent;
    int u,i,sz=graph[v].size();
    for(i=0;i<sz;i++)
    {
        u=graph[v][i];
        if(vis[u]) continue;
        DFS(u,lvl+1,v);
    }
}

int kthnode_from_a(int a,int b,int k,int lca)
    {
        int total_nodes_between_a_and_b;
        if(lca==a)
        {
            total_nodes_between_a_and_b=Lev[b]-Lev[a]+1;
            swap(a,b);
            k=total_nodes_between_a_and_b-k+1;
        }
        else if(lca==b);

        else
        {
             if(Lev[a] - Lev[lca] + 1 < k)
            {
              total_nodes_between_a_and_b = Lev[a] + Lev[b] - 2 * Lev[lca] + 1;
              k = total_nodes_between_a_and_b - k + 1;
              swap(a,b);
            }
        }
        k--;
         int desire_jump=k;
        while(desire_jump>0)
        {
            int max_mum_power_of_i=log2(desire_jump);
            a=sparse[a][max_mum_power_of_i];
            desire_jump-=(1<<max_mum_power_of_i);
        }
        return a;
    }

    int kthnode_from_a1(int a,int b,int k,int lca)
    {
        int total_nodes_between_a_and_b;
        if(lca==a)
        {
            total_nodes_between_a_and_b=Lev2[b]-Lev2[a]+1;
            swap(a,b);
            k=total_nodes_between_a_and_b-k+1;
        }
        else if(lca==b);

        else
        {
             if(Lev2[a] - Lev2[lca] + 1 < k)
            {
              total_nodes_between_a_and_b = Lev2[a] + Lev2[b] - 2 * Lev2[lca] + 1;
              k = total_nodes_between_a_and_b - k + 1;
              swap(a,b);
            }
        }
        k--;
         int desire_jump=k;
        while(desire_jump>0)
        {
            int max_mum_power_of_i=log2(desire_jump);
            a=sparse1[a][max_mum_power_of_i];
            desire_jump-=(1<<max_mum_power_of_i);
        }
        return a;
    }

void init_search(int N) {for(int i=0;i<=N;i++) { disc[i]=false;graph[i].clear();vis[i]=false;} }

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
    Lev[0]=-1;
    par[1]=-1;
    dfs(1, -1, 1);
    Maxlog=(int)(ceil)(log2(N+1));
    buildsparsetable(N+1);
    int u;
    par1[first]=-1;
    DFS(first,1,-1);
    buildsparsetable1(N+1);
    int a,b,v,k;
    while(q--)
    {
          scanf("%d%d",&v,&k);
         int dist_from_first=Lev[v]+Lev[first]-2*Lev[lca(v,first)];
         int dist_from_second=Lev2[v]+Lev2[second]-2*Lev2[lca2(v,second)];
         if(dist_from_first>dist_from_second)
         {
             if(dist_from_first<k) printf("0\n");
             else
             {
                 printf("%d\n",kthnode_from_a(v,first,k+1,lca(v,first)));
             }
         }
         else
         {
             if(dist_from_second<k) printf("0\n");
             else
             {
                  printf("%d\n",kthnode_from_a1(v,second,k+1,lca2(v,second)));
             }
         }
    }
	return 0;
}
