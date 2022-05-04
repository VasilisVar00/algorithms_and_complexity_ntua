#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <math.h>

using namespace std ;


struct node {
  int parent;  // store the parent of the node
  int rank;   // store the depth of tree
};
struct portal {
  int first;    // first universe of the portal bridge
  int second;  // second universe
  int width;
};

int timer, l,N;
vector<vector<int>> ancest;
vector< vector<int> > w_max;
vector< vector<int> > weights;
vector < vector<int> > aList;
vector<int> level;

// Function to perform DFS starting from node u
void dfs_lca(int v, int p, int lev)
{

    ancest[v][0] = p;
    level[v] = lev;     // to varos ths v-p akmhs

    for(int u : aList[v])
    {
        if (u == p)
          continue;
            w_max[u][0] = weights[u][v];
            dfs_lca(u,v,lev+1);
    }
}

void find_ancestor()
{
  cout<<"l ="<<l<<"\n"<<"N="<<N<<"\n";
    for (int i = 1; i <= l; i++) {
      cout<<"mesa sto prwto for\n";
        for (int j = 1; j <=N; j++) {
          cout<<"mphka sto for gia"<< j << i <<"-osth"<<"fora\n";
            ancest[j][i] = ancest[ancest[j][i-1]][i-1];
            cout<<ancest[j][i]<<"\n";
            w_max[j][i]= max(w_max[j][i-1],w_max[ancest[j][i-1]][i-1]);
            cout<<w_max[j][i]<<"\n";
        }
    }
}

void compute_lca()
{
    dfs_lca(1, 1, 0);
    cout<<"meta thn dfs\n";
    find_ancestor();
    cout<<"meta to find_ancestor";
}
bool compare(struct portal p1, struct portal p2)
{
  return p1.width < p2.width;
}


// union-find functions
int find(struct node nodes[],int i)
{
  if(nodes[i].parent != i)
    nodes[i].parent = find(nodes,nodes[i].parent);

    return nodes[i].parent;
}

void Union(struct node nodes[],int xclass,int yclass)
{
  // attach small depth tree to large depth tree and don't change the depth
  if(nodes[xclass].rank < nodes[yclass].rank)
    nodes[xclass].parent = yclass;

  else if(nodes[xclass].rank > nodes[xclass].rank)
    nodes[yclass].parent = xclass;

  else // if depths are equal link one to another and increment the depth
  {
    nodes[yclass].parent = xclass;
    nodes[xclass].rank++;
  }
}

vector< portal > Kruskal(struct node nodes[], struct portal portals[], int M)
{
  sort(portals,portals+M,compare);
  vector< portal > res;
  for(int i = 0; i < M; i++)
  {

    int xclass = find(nodes,portals[i].first);
    int yclass = find(nodes,portals[i].second);
    if(xclass != yclass)
    {
       res.push_back(portals[i]);
       Union(nodes,xclass,yclass);
    }
  }
  return res;
}

int query(int a, int b)
{
  cout<<"klithike h query";
  if (level[b] < level[a])
        swap(a, b);

    int ans = 0;

    // Difference between the depth of
    // the two given nodes
    int diff = level[b] - level[a];
    while (diff > 0) {
        int log = log2(diff);
        ans = max(ans, w_max[b][log]);

        // Changing Node B to its
        // parent at 2 ^ i distance
        b = ancest[b][log];

        // Subtracting distance by 2^i
        diff -= (1 << log);
    }

    // Take both a, b to its
    // lca and find maximum
    while (a != b) {
        int i = log2(level[a]);

        // Loop to find the 2^ith
        // parent that is different
        // for both a and b i.e below the lca
        while (i > 0
               && ancest[a][i] == ancest[b][i])
            i--;

        // Updating ans
        ans = max(ans, w_max[a][i]);
        ans = max(ans, w_max[b][i]);

        // Changing value to its parent
        a = ancest[a][i];
        b = ancest[b][i];
    }
    return ans;
}



int main(int argc, char *argv[])
{
  int M,Q,u,v,a_j,b_j,w_j;
  struct node *nodes;
  struct portal *p;
  scanf("%d %d",&N,&M); // read the N vertices and the M edges
  nodes = (struct node *) malloc((N+1) * sizeof(struct node));
  p = (struct portal *) malloc((M+1)*sizeof(struct portal));

  for(int i = 1; i<= N; i++) // initialize the union-find structure for detecting  cycle
  {
    nodes[i].parent = i;
    nodes[i].rank = 0;
  }

  for(int i = 0; i<M; i++) //  initialize the adjacency list
  {
    scanf("%d %d %d",&a_j,&b_j,&w_j);
    p[i].first = a_j;
    p[i].second = b_j;
    p[i].width = w_j;
  }

  scanf("%d", &Q);
  vector< pair<int,int> > Queries;
  for(int i = 0; i < Q; i++)
  {
    scanf("%d %d", &u, &v);
    Queries.push_back(make_pair(u,v));
  }


  vector< portal > vec;
  vec = Kruskal(nodes,p,M);

  weights.assign(N+1, vector<int>(N+1));
  aList.assign(N+1, vector<int>(N+1));

for (vector<portal>::iterator it = vec.begin() ; it != vec.end(); ++it)
  {
    weights[it->first][it->second] = it->width;
    weights[it->second][it->first] = it->width;
    aList[it->first].push_back(it->second);
  }

  cout<<"meta th for\n";

  level.resize(N+1);
  l = ceil(log2(N));
  ancest.assign(N+1, vector<int>(l + 1));
  w_max.assign(N+1, vector<int>(l+1));
  cout<<"meta ta assignements\n";
  compute_lca();


  for(int i = 0; i < Q; i++){
    int q = query(Queries[i].first, Queries[i].second);
    printf("%d\n",q);
  }
}
