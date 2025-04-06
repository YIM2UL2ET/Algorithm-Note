#include <bits/stdc++.h>

using namespace std;

int N, S, T;  // N: vertex ea, S: sink, T = source
vector<vector<int>> flow;   // flow[u][v]: residual flow on u to v
vector<vector<int>> graph;  // graph of linked list

// get layerd graph consisting of level array with bfs
bool getLydNtw(vector<int> &lv) {
  fill(lv.begin(), lv.end(), -1);
  lv[S] = 0;

  queue<int> que;
  que.push(S);

  for (int cnt = 1; !que.empty(); cnt++) {
    int sz = que.size();
    while (sz--) {
      int cur = que.front();
      que.pop();

      for (auto &nxt : graph[cur]) {
        if (lv[nxt] != -1 || flow[cur][nxt] <= 0) continue;
        lv[nxt] = cnt;
        que.push(nxt);
      }
    }
  }
  return lv[T] != -1;
}

// update layerd network and return flow from argument path with traceback
int update(vector<int> &path) {
  int ret = 1e9;
  for (int i = T; i != S; i = path[i]) {
    ret = min(ret, flow[path[i]][i]);
  }

  for (int i = T; i != S; i = path[i]) {
    flow[i][path[i]] += ret;
    flow[path[i]][i] -= ret;
  }

  return ret;
}

// if find argument path on layerd network with bfs,
// update layerd network and return flow
int getFlow(vector<int> &lv) {
  queue<int> que;
  que.push(S);

  vector<int> path(N, -1);
  path[S] = S;

  for (int cnt = 1; !que.empty(); cnt++) {
    int sz = que.size();
    while (sz--) {
      int cur = que.front();
      que.pop();

      for (auto &nxt : graph[cur]) {
        if (path[nxt] != -1 || flow[cur][nxt] <= 0 || lv[nxt] != cnt) continue;
        path[nxt] = cur;

        if (nxt == T) return update(path);
        que.push(nxt);
      }
    }
  }
  return -1;
}

int main() {
  // fastIO
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  /* init residual network and graph */

  // dinitz algorithm
  int ans = 0;
  vector<int> lv(N);
  while (getLydNtw(lv)) {
    int ret = 0;
    while (ret != -1) {
      ans += ret;
      ret = getFlow(lv);
    }
  }

  cout << ans;
  return 0;
}
