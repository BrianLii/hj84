#define MAXN 500010
#define MAX_LOG 19  // 2^MAX_LOG >= MAXN
int pa[MAX_LOG + 1][MAXN];
int dep[MAXN];
vector<int> G[MAXN];
void dfs(int x, int fa) {
  pa[0][x] = fa;
  for (int i = 0; i + 1 <= MAX_LOG; i++) {
    pa[i + 1][x] = pa[i][pa[i][x]];
  }
  for (auto i : G[x]) {
    if (i == fa) continue;
    dep[i] = dep[x] + 1;
    dfs(i, x);
  }
}
int find_lca(int a, int b) {
  if (dep[a] > dep[b]) swap(a, b);
  for (int i = dep[b] - dep[a], k = 0; i; i >>= 1) {
    if (i & 1) b = pa[k][b];
    ++k;
  }
  if (a == b) return a;
  for (int i = MAX_LOG; i >= 0; i--) {
    if (pa[i][a] != pa[i][b]) {
      a = pa[i][a];
      b = pa[i][b];
    }
  }
  return pa[0][a];
}