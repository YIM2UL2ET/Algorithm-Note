// include
tuple<ll, ll, ll> exGcd(ll a, ll b) {
  if (a == 0) return {b, 0, 1};
  auto [g, x, y] = exGcd(b % a, a);
  return {g, y - (b / a) * x, x};
}

// case1: gcd(m_i, m_j) = 1 (i != j && 1 <= i,j <= n)
// x = sum_{i=0}^{n} M_i * (M_i^{-1} mod m_i) * a_i
ll crt(const vector<pair<ll, ll>> &vec) {
  ll M = 1;
  for (auto &i : vec) {
    M *= i.second;
  }

  ll x = 0;
  for (auto &i : vec) {
    auto [g, k, _] = exGcd(M / i.second, i.second);
    if (g != 1) return -1;
    x += (M / i.second) * k * i.first;
    x %= M;
  }
  return x;
}

// case2: gcd(m_i, m_j) != 1 (i = 1, j = 2)
// x = m_1 * k_0 + a_1 (mod lcm(m1, m2))
ll crt(ll a1, ll m1, ll a2, ll m2) {
  auto [g, k0, _] = exGcd(m1, m2);
  if ((a2 - a1) % g != 0) return -1;
  k0 *= (a2 - a1) / g;

  ll x = m1 * k0 + a1;
  while (x < 0) x += m1 * (m2 / g);
  return x;
}