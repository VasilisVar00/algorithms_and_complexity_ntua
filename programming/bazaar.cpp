#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int minimum(long a, long b){
  if(a == -1) return b;
  if(b == -1) return a;
  return (a < b) ? a : b;
}

long* addPrices(long* arr1, int size1,long * arr2, int size2, long *arr3, int size3){
  int size = min(size1,min(size2,size3));
  long *acc = new long[size + 1];
  for(int i = 1; i <= size; i++)
  {
    acc[i] = arr1[i] + arr2[i] + arr3[i];
  }
  return acc;
}


long* knapsack(vector< pair<int,int> > &S){ // return only the last line of V[][]
  int size = S.size();
  int W = 0;
  long** V; // min price for first k offers and for w quantity
  int withoutk,withk;
  V = new long* [size + 1];
  for(int i = 0; i < size; i++)
  {
    W += S[i].first; // the sum of all quantities is the size of the knapsack
  }
  for(int i = 0; i <= size; i++)
  {
    V[i] = new long[W+1];
  }
  for(int j = 0; j<= W; j++)
  {
    V[0][j] = 0;
  }
  for(int k = 1; k <= size; k++)
  {
    for(int w = 0; w <= W; w++)
    {
      withoutk = V[k-1][w];
      if(w <= S[k-1].first) // as eksetasoyme to paradeigma 4 800 3 100 1 50
      {
        if(withoutk == 0) // quantity = 4 we want V[1][1] (first offer is that with quantity = 4 and price = 800 in this example)
          V[k][w] = S[k-1].second; // so the cost for quantity = 1 is equal with that of quantity = 4, remember that so far the only offer
        else                       // available is that of quantity = 4.
          V[k][w] = minimum(S[k-1].second, withoutk); // quantity = 3 we want V[2][1] = min(V[1][1],100) where 100 is the price of quantity = 3
      }
      else
      {
        if(withoutk == 0) // edw den ginetai na paroume prosfora megethous w exontas mono tis prwtes k prosfores
          V[k][w] = -1; // px. to V[1][5] = -1 giati den ginetai na paroyme 5 set exontas mono thn prwth prosfora pou exei quantity = 4
        else if(V[k-1][w-S[k-1].first] != -1) // h klasikh periptwsh tou knapsack
        {
          withk = V[k-1][w-S[k-1].first] + S[k-1].second;
          V[k][w] = minimum(withk,withoutk);
        }
        else
        // an exoume px: 4 800, 3 100, 1 50
        // to V[2][8] = -1 dioti den mporoyme na paroyme w = 8 me tis dyo prwtes kata seira prosfores
        // parathrhste oti V[2-1][8-3] = V[1][5] = -1
        // edw omws to withoutk = -1, opote einai ksexwristh periptwsh.
          V[k][w] = -1;
      }
    }
  }
  return V[size];
}

int main(){
  int N,M;
  int merchant,quantity,price;
  char typeOfArmor;
  vector< pair<int,int> > v[9];
  scanf("%d %d",&N,&M);

  for(int i = 0; i < M; i++)
  {
    scanf("%d %c %d %d",&merchant,&typeOfArmor,&quantity,&price);
    if(merchant == 1)
    {
      if(typeOfArmor == 'A')
      {
        v[0].push_back(make_pair(quantity,price));
      }
      else if (typeOfArmor == 'B')
      {
        v[1].push_back(make_pair(quantity,price));
      }
      else
      {
        v[2].push_back(make_pair(quantity,price));
      }
    }
    else if(merchant == 2)
    {
      if(typeOfArmor == 'A')
      {
        v[3].push_back(make_pair(quantity,price));
      }
      else if (typeOfArmor == 'B')
      {
        v[4].push_back(make_pair(quantity,price));
      }
      else
      {
        v[5].push_back(make_pair(quantity,price));
      }
    }
    else
    {
      if(typeOfArmor == 'A')
      {
        v[6].push_back(make_pair(quantity,price));
      }
      else if (typeOfArmor == 'B')
      {
        v[7].push_back(make_pair(quantity,price));
      }
      else
      {
        v[8].push_back(make_pair(quantity,price));
      }
    }
  }
  int sizes[9];
  for (int i = 0; i < 9; i++)
  {
    sizes[i] = 0;
  }

  for (int i = 0; i < 9; i++)
  {
    for (auto it = v[i].begin(); it != v[i].end(); it++)
    {
      sizes[i] += (*it).first;
    }
  }
  long* results[9];
  for(int i = 0; i < 9; i++)
  {
    results[i] = knapsack(v[i]);
  }

   long* prices[3];
  for(int i = 0; i < 9; i += 3){
    int k = i/3;
    prices[k] = addPrices(results[i],sizes[i],results[i+1],sizes[i+1],results[i+2],sizes[i+2]);
  }
  prices[0][0] = 0;
  prices[1][0] = 0;
  prices[2][0] = 0;

  int maxfrom1 = min(sizes[0],min(sizes[1],sizes[2]));
  int maxfrom2 = min(sizes[3],min(sizes[4],sizes[5]));
  int maxfrom3 = min(sizes[6],min(sizes[7],sizes[8]));
  long my_ans = 0;
  long res = 0;
  if(maxfrom1 + maxfrom2 + maxfrom3 < N){
     my_ans = -1;
  }
  else{
    res = prices[0][maxfrom1] + prices[1][maxfrom2] + prices[2][maxfrom3];
      for(int i = 0; i <= maxfrom1; i++)
      {
        for(int j = 0; j <= maxfrom2; j++)
        {
          if(N-i-j <= maxfrom3 && N-i-j >= 0)
          {
            long temp = prices[0][i] + prices[1][j] + prices[2][N-i-j];
            if(res > temp)
              res = temp;
          }
        }
      }
  }
  if(my_ans != -1)
    my_ans = res;
  printf("%ld\n",my_ans);

}
