// ax + by = gcd , return [gcd, x, y]
tuple<ll, ll, ll> ExGcd(ll a, ll b) {
  if (a == 0) return {b, 0, 1};
  auto [g, x, y] = ExGcd(b % a, a);
  return {g, y - (b / a) * x, x};
}