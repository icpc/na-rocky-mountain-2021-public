#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500;
const int MAX_S = 1000;

int N, S;
int s[MAX_N], t[MAX_N];
vector<int> G[MAX_N];

// ans[node][skip][size]
int ans[MAX_N][2][MAX_S+1];
bool init[MAX_N][2];

void f(int root, bool skip, int parent = -1)
{
  if (init[root][skip]) return;

  // try selecting root
  int ans2[MAX_S+1] = {0};
  if (!skip && s[root] <= S) {
    ans2[s[root]] = t[root];
    for (auto c : G[root]) {
      int temp[MAX_S+1];
      if (c == parent) continue;

      copy(ans2, ans2+S+1, temp);
      f(c, true, root);

      for (int ss = 0; ss <= S; ss++) {
	for (int s1 = 0; s1 <= ss; s1++) {
	  int s2 = ss - s1;
	  if (s1 && !temp[s1]) continue;
	  if (s2 && !ans[c][true][s2]) continue;
	  ans2[ss] = max(ans2[ss], temp[s1] + ans[c][true][s2]);
	}
      }
    }
  }
  copy(ans2, ans2+S+1, ans[root][skip]);

  // try not selecting root
  fill(ans2, ans2+S+1, 0);
  for (auto c : G[root]) {
    int temp[MAX_S+1];
    if (c == parent) continue;

    copy(ans2, ans2+S+1, temp);
    f(c, false, root);

    for (int ss = 0; ss <= S; ss++) {
      for (int s1 = 0; s1 <= ss; s1++) {
	int s2 = ss - s1;
	if (!temp[s1] && s1) continue;
	if (!ans[c][false][s2] && s2) continue;
	ans2[ss] = max(ans2[ss], temp[s1] + ans[c][false][s2]);
      }
    }
  }
  for (int s = 0; s <= S; s++) {
    ans[root][skip][s] = max(ans[root][skip][s], ans2[s]);
  }

  init[root][skip] = true;
}

int main()
{
  cin >> N >> S;
  for (int i = 0; i < N; i++) {
    cin >> s[i] >> t[i];
  }

  for (int i = 0; i < N-1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  f(0, false);
  cout << *max_element(ans[0][0], ans[0][0] + S+1) << endl;
  
  return 0;
}
