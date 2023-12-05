#include <bits/stdc++.h>
using namespace std;
void gen(int test, int n);
int main() {
  srand(20040129);
  gen(2, 1);
  gen(3, 3);
  gen(4, 5);
  gen(5, 8);
  for (int i = 6; i <= 10; i++) gen(i, 10);
}

void gen(int test, int n) {
  freopen(("data" + to_string(test) + ".in").c_str(), "w", stdout);
  vector<array<int, 2>> ch(n + 1);
  for (int x, c, i = 2; i <= n; i++) {
    do {
      x = rand() % (i - 1) + 1;
      c = rand() & 1;
    } while (ch[x][c]);
    ch[x][c] = i;
  }
  vector<int> p(n + 1);
  for (int i = 1; i <= n; i++) p[i] = i;
  random_shuffle(p.begin() + 1, p.end());

  vector<int> inorder, postorder;
  auto dfs_inorder = [&](auto &&self, int u) {
    if (!u) return;
    self(self, ch[u][0]);
    inorder.push_back(p[u]);
    self(self, ch[u][1]);
  };
  dfs_inorder(dfs_inorder, 1);
  auto dfs_postorder = [&](auto &&self, int u) {
    if (!u) return;
    self(self, ch[u][0]);
    self(self, ch[u][1]);
    postorder.push_back(p[u]);
  };
  dfs_postorder(dfs_postorder, 1);
  cout << n << endl;
  for (int i = 0; i < n; i++) cout << inorder[i] << " \n"[i + 1 == n];
  for (int i = 0; i < n; i++) cout << postorder[i] << " \n"[i + 1 == n];

  freopen(("data" + to_string(test) + ".ans").c_str(), "w", stdout);
  cout << "Check:" << endl;
  for (int i = 0; i < n; i++) cout << inorder[i] << " \n"[i + 1 == n];
  for (int i = 0; i < n; i++) cout << postorder[i] << " \n"[i + 1 == n];
}