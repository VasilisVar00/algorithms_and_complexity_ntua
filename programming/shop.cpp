#include <iostream>
#include <unordered_map>
using namespace std;
#define START_FILE 1
#define END_FILE  26


int main(int argc, char * argv[])
{
  int N,K,my_ans = -1;
  scanf("%d %d",&N,&K);
  int *p = (int *) malloc((N+1) * sizeof(int));
  p[0] = 0;
  for(int i = 1; i <= N; i++)
  {
    scanf("%d",&p[i]);
  }
  int *a = (int*) malloc((K+1) * sizeof(int));
  a[0] = 0;
  for(int i = 1; i<=K; i++)
  {
    a[i] = N+1;
  }
  long sum;
  long the_sum;
  for(int i = N ; i > 0; i--)
  {
    sum = 0;
    the_sum = 0;
    for(int k = i+1; k<=N; k++)
    {
      the_sum += p[k];
      if(the_sum > K)
        break;
      if(the_sum <= K)
      {
        a[the_sum] = min(k-i,a[the_sum]);
        if(the_sum == K)
          break;
      }
    }
    for(int j =0; j < i; j++)
    {
      sum += p[i-j];
      if(sum <= K)
      {
        if(j+1 + a[K-sum] <= N)
        {
          if(my_ans == -1)
            my_ans = j+1 + a[K-sum];
          else
            my_ans = min(my_ans,j+1 + a[K-sum]);
        }
      }
    }
  }
  printf("%d\n",my_ans);
}
