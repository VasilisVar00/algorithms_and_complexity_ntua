#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>
#include <utility>
#include <algorithm>
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

// function that finds the answer
int find_width(struct node nodes[], struct portal portals[] ,vector< pair<int,int> > &vec, int M)
{
  int ans = 0;
  int aux = 0;
  int i = M-1;
  int size = vec.size();
  int limit;
  while(aux < size && i > -1)
  {
    int xclass = find(nodes,portals[i].first);
    int yclass = find(nodes,portals[i].second);
    if(xclass != yclass)
    {
      Union(nodes,xclass,yclass);
      limit = aux;
      for(int j = limit; j < size; j++)
      {
        if(find(nodes,vec[j].first) != find(nodes,vec[j].second))
        {

          break;
        }
        else
        {
          ans = portals[i].width;
          ++aux;
        }
      }

    }

    --i;
  }
  return ans;
}

int main(int argc, char *argv[])
{
  char filename[30];
    int N,M,num_files,ans,my_ans,a_j,b_j,w_j;
    vector< pair<int,int> > vec;
    int *c;
    struct node *nodes;
    struct portal *p;
    scanf("%d %d",&N,&M);
    c = (int *) malloc(N * sizeof(int));
    for(int i =0; i<N; i++)  // read the permutation of universes
    {
      scanf("%d",&c[i]);
    }
    p = (struct portal *) malloc(M*sizeof(struct portal));
    for(int i = 0; i<M; i++) // read the universes that connect with a portal and the width
    {
      scanf("%d %d %d",&a_j,&b_j,&w_j);
      p[i].first = a_j;
      p[i].second = b_j;
      p[i].width = w_j;
    }
    if(N <= 100000)
      sort(p,p+M,compare);

    nodes = (struct node *) malloc(N * sizeof(struct node));
    for(int i = 0; i<N; i++)
    {
      nodes[i].parent = i;
      nodes[i].rank = 0;
    }

    for(int i = 0; i < N; i++)
    {
      int idx;
      if(c[i] != i + 1)
      {
        idx = c[i];
        vec.push_back( make_pair(idx,c[idx-1]));
      }
    }

    my_ans = find_width(nodes,p,vec,M);
    printf("%d\n",my_ans);
}
