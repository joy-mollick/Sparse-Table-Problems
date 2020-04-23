
/// Time-Complexity O(nlogn) [building of sparse table] + per query -> O(logn) [binary-lifting based finding] 
/// Space Complexity O(nlogn) 

/* 

https://www.youtube.com/watch?v=w56Qe5wEr2I, a good tutorial here 
You can also see the code in TopCoder Tutorial ,https://www.topcoder.com/community/competitive-programming/tutorials/range-minimum-query-and-lowest-common-ancestor/#Another%20easy%20solution%20in%20O(N%20logN,%20O(logN)

*/
/// This is the normal building of sparse-table like as in finding rmq 
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

/// This is for finding the level of all node and parent of all nodes ,normal dfs 

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
        dfs(u,v,lvl+1);
    }
}

/// This is for finding lca between two nodes ,this part is little bit tricky ,we used binary lifting technique 
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
