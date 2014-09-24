#include <iostream>
using namespace std;

struct bint {
 int len;
 int arr[12];

 bint(int n): len(1) {
  for (int i=1;i<12;i++) arr[i]=0;
  arr[0] = n;
 }
 
 bint(): len(1) {
  for (int i=1;i<12;i++) arr[i]=0;
  arr[0] = 0;
 }

 bint& operator+=(const bint& a) {
  len = len > a.len ? len : a.len;
  bool incr = false;
  for (int i=0;i<len;i++) {
   int sum = this->arr[i] + a.arr[i];
   if (incr) this->arr[i] = 1;
   else this->arr[i] = 0;
   if (sum > 9) incr = true;
   else incr = false;
   this->arr[i] += sum % 10;
  }
  if (incr) {
   arr[len] = 1;
   len += 1;
  }
  return *this;
 }
 
};

ostream& operator<<(ostream&out, bint& b) {
  for (int i=b.len-1;i>=0;i--) out << b.arr[i];
  return out;
}

bint a[30001];
bint b[30001];
bint c[30001];
bint d[30001];

bint f(int n) {
 if (a[n].len > 1 || a[n].arr[0] != 0) return a[n];
 a[n] += a[n-1];
 if (n >= 5) {
  a[n] += b[n-5];
  b[n] += b[n-5];
 }
 if (n >= 10) {
  a[n] += c[n-10];
  c[n] += c[n-10];
  b[n] += c[n-10];
 }
 if (n >= 25) {
  a[n] += d[n-25];
  d[n] += d[n-25];
  c[n] += d[n-25];
  b[n] += d[n-25];
 }
 if (n % 50 == 0) {
  a[n] += bint(1);
  d[n] += bint(1);
  c[n] += bint(1);
  b[n] += bint(1);
 }
 return a[n];
}

int main() {
 a[0]=b[0]=c[0]=d[0]=bint(1);
 int n;
 while (cin >> n) {
  for (int i=1;i<=n;i++) f(i);
  cout << "There are ";
  cout << a[n];
  cout << " ways to produce ";
  cout << n;
  cout << " cents change." << endl;
 }
}
