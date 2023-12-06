#include "assert.h"
#include "stdio.h"

#define N 39
int n, tot, a[N], ch[N][2], in[N], post[N];

int build(int *in, int *post, int n) {
  if (n == 0) {
    return 0;
  }
  int u = ++tot;
  a[u] = post[n];
  int m;
  for (m = 1; m <= n; m++)
    if (in[m] == a[u]) {
      break;
    }
  ch[u][0] = build(in, post, m - 1);
  ch[u][1] = build(in + m, post + m - 1, n - m);
  return u;
}

struct atom {
  int val, dep, ts;
} q[N];
int cmp(struct atom a, struct atom b) {
  if (a.dep != b.dep) return a.dep < b.dep;
  if (a.dep & 1) {
    return a.ts > b.ts;
  } else {
    return a.ts < b.ts;
  }
}

void dfs(int u, int dep) {
  if (u == 0) {
    return;
  }
  ++tot;
  q[tot].val = a[u];
  q[tot].dep = dep;
  q[tot].ts = tot;
  dfs(ch[u][0], dep + 1);
  dfs(ch[u][1], dep + 1);
}

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", in + i);
  for (int i = 1; i <= n; i++) scanf("%d", post + i);
  build(in, post, n);
  tot = 0;
  dfs(1, 1);
  for (int i = 1; i < n; i++)
    for (int j = 1; j < n; j++)
      if (!cmp(q[j], q[j + 1])) {
        struct atom tmp = q[j];
        q[j] = q[j + 1];
        q[j + 1] = tmp;
      }
  for (int i = 1; i <= n; i++) printf("%d%c", q[i].val, " \n"[i == n]);
}