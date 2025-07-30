struct LCA {  // 1-index
  int N, lg; vector<int> dep; vector<vector<int>> adj, par;

  LCA(int N) : N(N), lg(log2(N)), adj(N), par(N, vector<int>(lg)), dep(N) {}

  int log2(int n) {
    int res = 0;
    while (n > 1 << res) res++;
    return res;
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init(int node, int parent, int depth) {
    par[node][0] = parent, dep[node] = depth;
    for (int i = 1; i < lg; i++) par[node][i] = par[par[node][i - 1]][i - 1];
    for (auto &child : adj[node])
      if (child != parent) init(child, node, depth + 1);
  }

  int getLCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = lg - 1; i >= 0; i--)
      if (dep[u] - dep[v] >= (1 << i)) u = par[u][i];
    if (u == v) return u;
    for (int i = lg - 1; i >= 0; i--)
      if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    return par[u][0];
  }
  
  void init(int root) { init(root, 0, 1); }
};