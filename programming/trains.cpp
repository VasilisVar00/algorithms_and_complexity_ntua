#include <stdio.h>
#include <vector>
#include <set>
#include <stdlib.h>

#define limit 10001
#define s_j 1000000001
#define my_pair std::pair <unsigned long, int>

std::vector <unsigned long> dist, query(limit,-1);
std::set< my_pair > queue;
int my_limit = limit;

void Dijkstra(){
  while(!queue.empty()){
      my_pair head = *queue.begin();
      unsigned long mpla = head.second;
      int sum = head.first;
      queue.erase(head);

      for(auto dj: dist){
        int new_state = (mpla + dj) % my_limit;
        int new_dist = sum + dj;

        if(new_dist < query[new_state] || query[new_state] == -1){
          queue.erase ( std::make_pair(new_dist,new_state) );
          query[new_state] = new_dist;
          queue.insert( std::make_pair(new_dist,new_state) );
        }
      }
    }
}

int main(){
  int N;
  unsigned long Q;
  scanf("%d %lu", &N, &Q);
  for(int i = 0; i < N; i++){
    unsigned long d;
    scanf("%lu",&d);
    dist.push_back(d);
    my_limit = (d < my_limit) ? d : my_limit;
  }
  query[0] = 0;
  queue.insert(std::make_pair(0,0));
  Dijkstra();

  unsigned long *q = (unsigned long *) malloc(Q * sizeof(unsigned long));
  for(int i = 0; i < Q; i++){

    scanf("%lu", &q[i]);
  }

  for(int i = 0; i < Q; i++){
    if(query[q[i] % my_limit] > q[i])
      printf("NO\n");
    else
      printf("YES\n");
  }
}
