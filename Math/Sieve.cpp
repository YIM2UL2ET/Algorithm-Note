vector<int> primeNums;
vector<bool> isPrime;

void LinearSieve(int n) {
  isPrime.resize(n + 1, true);
  isPrime[0] = isPrime[1] = false;

  for (int i = 2; i <= n; i++) {
    if (isPrime[i]) primeNums.push_back(i);

    for (auto j : primeNums) {
      if (i * j > n) break;
      isPrime[i * j] = false;
      if (i % j == 0) break;
    }
  }
}

void EratosSieve(int n) {
  isPrime.resize(n + 1, true);
  isPrime[0] = isPrime[1] = false;

  for (int i = 2; i * i <= n; i++) {
    if (isPrime[i]) {
      primeNums.push_back(i);
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false;
      }
    }
  }
}