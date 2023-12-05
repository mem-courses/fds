#include <bits/stdc++.h>
using namespace std;
void gen(int test, int n);
int main() {
  srand(20040129);
  gen(2, 1);
  gen(3, 3);
  gen(4, 5);
  gen(5, 8);
  gen(6, 10);
  for (int i = 7; i <= 10; i++) gen(i, 20 + i);
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
  vector<tuple<int, int, int>> node;
  auto dfs = [&](auto &&self, int u, int dep) {
    if (!u) return;
    node.emplace_back(dep, (int)node.size(), p[u]);
    self(self, ch[u][0], dep + 1);
    self(self, ch[u][1], dep + 1);
  };
  dfs(dfs, 1, 1);
  sort(node.begin(), node.end());
  for (int l = 0, r; l < node.size(); l = r + 1) {
    r = l;
    while (r + 1 < node.size() && get<1>(node[r + 1]) == get<1>(node[r])) ++r;
    if (get<1>(node[l]) & 1) {
      for (int i = r; i >= l; i--) cout << get<2>(node[i]) << " \n"[i + 1 == node.size()];
    } else {
      for (int i = l; i <= r; i++) cout << get<2>(node[i]) << " \n"[i + 1 == node.size()];
    }
  }
}