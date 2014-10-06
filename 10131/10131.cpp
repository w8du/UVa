#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct weight {
 int index;
 int w;
};

struct intelligence {
 int index;
 int iq;
};

struct elephant {
 int index;
 int w;
 int iq;
};

bool wComp(weight w1, weight w2) {return w1.w < w2.w;}

bool iqComp(intelligence i1, intelligence i2) {return i2.iq < i1.iq;}

int main() {
 int n = 1;
 int w,iq;
 vector<weight> wList;
 vector<intelligence> iqList;
 while (cin >> w >> iq) {
  struct weight ww = {n, w};
  struct intelligence i = {n, iq};
  wList.push_back(ww);
  iqList.push_back(i);
  n += 1;
 }
 sort(wList.begin(),wList.end(), wComp);
 sort(iqList.begin(),iqList.end(),iqComp);
 int** arr = new int*[n+1];
 int** dir = new int*[n+1];
 for (int i=0;i<n;i++) {
  arr[i] = new int[n];
  dir[i] = new int[n];
 }
 arr[0][0] = 0;
 for (int i=0;i<n;i++) {
  for (int j=0;j<n;j++) {
   if (i == 0 || j == 0) arr[i][j] = 0;
   else if (wList.at(i-1).index == iqList.at(j-1).index) {
    arr[i][j] = arr[i-1][j-1] + 1;
    dir[i][j] = 2;
   } else if (arr[i-1][j] > arr[i][j-1]) {
    arr[i][j] = arr[i-1][j];
    dir[i][j] = 3;
   } else {
    arr[i][j] = arr[i][j-1];
    dir[i][j] = 1;
   }
  }
 }
 int res = arr[n-1][n-1];
 vector<elephant> sol;
 int r = n-1,c=n-1;
 while (r > 0 && c > 0) {
  if (dir[r][c] == 2) {
   elephant e = {wList.at(r-1).index,wList.at(r-1).w,iqList.at(c-1).iq};
   if (sol.empty() || (e.w != sol.back().w && e.iq != sol.back().iq)) {
    sol.push_back(e);
   } else res -= 1;
   r -= 1;
   c -= 1;
  } else if (dir[r][c] == 1) c-=1;
  else r-= 1;
 }
 cout << res << endl;
 for (vector<elephant>::reverse_iterator it = sol.rbegin();it!=sol.rend();it++)
  cout << it->index << endl;
}
