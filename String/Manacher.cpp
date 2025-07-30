void Manacher(const string &str, int P[]) {
  int sz = str.size() * 2 + 1, prv = -1, ed = -1;

  string T = "#";
  for (auto &ch : str) T += ch, T += '#';

  for (int i = 0; i < sz; i++) {
    P[i] = (i <= ed ? min(P[2 * prv - i], ed - i) : 0);
    while (i + P[i] + 1 < sz && i - P[i] - 1 >= 0 && T[i + P[i] + 1] == T[i - P[i] - 1]) P[i]++;
    if (i + P[i] > ed) ed = i + P[i], prv = i;
  }
}