vector<int> SuffixArray(string T) {
  int n = T.size();
  vector <int> SA, RA, tmp(n);
  
  for (int i = 0; i < n; i++) SA[i] = i, RA[i] = T[i];
  
  for (int l = 1; l < n; l <<= 1) {
    auto cmp = [&](int a, int b) -> bool {
      if (RA[a] != RA[b]) return RA[a] < RA[b];
      int na = (a + l >= n ? -1 : RA[a + l]);
      int nb = (b + l >= n ? -1 : RA[b + l]);
      return na < nb;
    };

    sort(SA.begin(), SA.end(), cmp);

    tmp[SA[0]] = 0;
    for (int i = 1; i < n; i++) {
      if (!cmp(SA[i], SA[i - 1]) && !cmp(SA[i - 1], SA[i])) {
        tmp[SA[i]] = tmp[SA[i - 1]];
      } else {
        tmp[SA[i]] = tmp[SA[i - 1]] + 1;
      }
    }

    for (int i = 0; i < n; i++) RA[i] = tmp[i];
  }

  return SA;
}

vector <int> LCP_Array(string T) {
  int n = T.size();
  vector <int> SA = SuffixArray(T), RA(n), LCP(n);

  for (int i = 0; i < n; i++) RA[SA[i]] = i;
  
  for (int i = 0, k = 0; i < n; i++, k = max(0, k - 1)) {
    if (RA[i] == n - 1) continue;
    for (int j = SA[RA[i] + 1]; T[i + k] == T[j + k]; k++);
    LCP[RA[i]] = k;
  }

  return LCP;
}