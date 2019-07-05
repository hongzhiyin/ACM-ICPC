memset(mu, 0, sizeof(mu));
mu[1] = 1;
rep(i, 1, m+1) for (int j = i+i; j <= m; j += i) mu[j] -= mu[i];
