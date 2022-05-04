#include <iostream>
#include <vector>

using namespace std;

struct twoPairs{
  int end[2];           // finishing point of the interval,but we have two intervals
  int length[2];        // length of the interval
};

int CeilIndex1(int c[], int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if(c[m] == key)
          return m;
        if (c[m] > key)
            r = m;
        else
            l = m;
    }

    return r;
}
int CeilIndex2(int c[], int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (c[m] == key)
          return m;
        if (c[m] > key)
            l = m;
        else
            r = m;
    }

    return r;
}

int compareArrays(struct twoPairs a[], struct twoPairs b[], int N,int K){
  int res = 0;
  for(int i = 0; i < N-1; i++)
  {
    if(a[i].end[0] < b[i+1].end[0] + K)
      res = max(res,a[i].length[0] + b[i+1].length[0]);
   if(a[i].end[1] < b[i+1].end[0] + K)
      res = max(res,a[i].length[1] + b[i+1].length[0]);
   if(a[i].end[0] < b[i+1].end[1] + K)
      res = max(res,a[i].length[0] + b[i+1].length[1]);
   if(a[i].end[1] < b[i+1].end[1] + K)
      res = max(res,a[i].length[1] + b[i+1].length[1]);
  }
  return res;
}


void LIS(int v[], struct twoPairs a[],int N)
{
    int *tail = (int *) malloc(N * sizeof(int));
    for(int i = 0; i < N; i++)
      tail[i] = 0;

    int length = 1; // always points empty slot in tail

    tail[0] = v[0];
    a[0].end[0] = a[0].end[1] = v[0];
    a[0].length[0] = a[0].length[1] = 1;
    for(int i = 1; i < N; i++) {

        // new smallest value
        if(v[i] < tail[0])
        {
            a[i].end[0] = v[i];
            a[i].length[0] = 1;
            a[i].end[1] = tail[length - 1];
            a[i].length[1] = length;
            tail[0] = v[i];
        }
        // v[i] extends largest subsequence
        else if(v[i] > tail[length - 1])
        {
            tail[length++] = v[i];
            a[i].end[0] = v[i];
            a[i].length[0] = length;
            a[i].end[1] = v[i];
            a[i].length[1] = length;
        }

        // v[i] will become end candidate of an existing
        // subsequence or Throw away larger elements in all
        // LIS, to make room for upcoming greater elements
        // than v[i] (and also, v[i] would have already
        // appeared in one of LIS, identify the location
        // and replace it)
        else
        {
            int index = CeilIndex1(tail, -1, length - 1, v[i]);
            tail[index] = v[i];
            a[i].end[0] = v[i];
            a[i].length[0] = index + 1;
            a[i].end[1] = tail[length - 1];
            a[i].length[1] = length;
        }
    }
}

void LDS(int v[], struct twoPairs a[],int N)
{
    int *tail = (int *) malloc(N * sizeof(int));
    for(int i = 0; i < N; i++)
      tail[i] = 0;

    int length = 1; // always points empty slot in tail

    tail[0] = v[N-1];
    a[N-1].end[0] = a[N-1].end[1] = v[N-1];
    a[N-1].length[0] = a[N-1].length[1] = 1;
    for(int i = N-2; i > -1; i--) {

        // new smallest value
        if(v[i] > tail[0])
        {
            a[i].end[0] = v[i];
            a[i].length[0] = 1;
            a[i].end[1] = tail[length - 1];
            a[i].length[1] = length;
            tail[0] = v[i];
        }
        // v[i] extends largest subsequence
        else if(v[i] < tail[length - 1])
        {
            tail[length++] = v[i];
            a[i].end[0] = v[i];
            a[i].length[0] = length;
            a[i].end[1] = v[i];
            a[i].length[1] = length;
        }

        // v[i] will become end candidate of an existing
        // subsequence or Throw away larger elements in all
        // LIS, to make room for upcoming greater elements
        // than v[i] (and also, v[i] would have already
        // appeared in one of LIS, identify the location
        // and replace it)
        else
        {
            int index = CeilIndex2(tail, -1, length - 1, v[i]);
            tail[index] = v[i];
            a[i].end[0] = v[i];
            a[i].length[0] = index + 1;
            a[i].end[1] = tail[length - 1];
            a[i].length[1] = length;
        }
    }
}



int main(){
  int N,K;
  int *c;
  scanf("%d %d",&N,&K);
  c = (int *) malloc(N * sizeof(int));
  for(int i =0; i<N; i++)  // read the permutation of universes
  {
    scanf("%d",&c[i]);
  }
  struct twoPairs *a = (struct twoPairs *) malloc(N*sizeof(struct twoPairs));
  struct twoPairs *b = (struct twoPairs *) malloc(N*sizeof(struct twoPairs));

  LIS(c,a,N);
  LDS(c,b,N);

  printf("%d\n",compareArrays(a,b,N,K));

}
