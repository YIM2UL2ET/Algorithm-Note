struct Dinic {  // 0-index
  struct Edge { int vtx, dst, cap, rvs; };
  const int INF = 1e9; int n, *dist, *cnt; bool *inQ, *vst; vector<Edge> *adj;

  Dinic(int n) : n(n), inQ(new bool[n]{}), vst(new bool[n]{}),
    cnt(new int[n]{}), dist(new int[n]{}), adj(new vector<Edge>[n] {}) {}
  ~Dinic() { delete[] cnt, delete[] dist, delete[] inQ, delete[] vst, delete[] adj; }

  void add_edge(int u, int v, int d, int c) {
    adj[u].emplace_back(v, d, c, (int)adj[v].size());
    adj[v].emplace_back(u, -d, 0, (int)adj[u].size() - 1);
  }

  pair<int, int> MCMF(int S, int T) {
    int min_cost = 0, max_flow = 0;
    while (SPFA(S, T)) {
      int res = 0;
      for (int i = 0; i < n; i++) cnt[i] = vst[i] = 0;
      while (res = dfs(S, INF, T)) {
        min_cost += dist[T] * res, max_flow += res;
        for (int i = 0; i < n; i++) vst[i] = 0;
      }
    }
    return make_pair(min_cost, max_flow);
  }

  bool SPFA(int S, int T) {
    queue<int> Q;
    for (int i = 0; i < n; i++) dist[i] = INF, inQ[i] = false;
    Q.push(S), inQ[S] = true, dist[S] = 0;
    while (!Q.empty()) {
      int cur = Q.front();
      Q.pop(), inQ[cur] = false;
      for (auto &[nxt, dst, cap, rvs] : adj[cur]) {
        if (dist[nxt] > dist[cur] + dst && cap > 0) {
          dist[nxt] = dist[cur] + dst;
          if (!inQ[nxt]) Q.push(nxt), inQ[nxt] = true;
        }
      }
    }
    return dist[T] < INF;
  }

  int dfs(int cur, int flow, int T) {
    vst[cur] = true;
    if (cur == T) return flow;
    while (cnt[cur] < adj[cur].size()) {
      auto &[nxt, dst, cap, rvs] = adj[cur][cnt[cur]];
      if (!vst[nxt] && dist[nxt] == dist[cur] + dst && cap > 0) {
        int res = dfs(nxt, min(flow, cap), T);
        if (res > 0) {
          cap -= res, adj[nxt][rvs].cap += res;
          return res;
        }
      }
      cnt[cur]++;
    }
    return 0;
  }
};