#include <iostream>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int H[N], W[N];
int main() {
 int n, k;
 cin >> n >> k;
 int max_side = 0;
 for (int i = 0; i < n; ++i) {
 cin >> H[i] >> W[i];
 max_side = max(max_side, min(H[i], W[i]));
 }
 int l = 1, r = max_side, ans = 0;
 while (l <= r) {
 int mid = (l + r) / 2;
 ll cnt = 0;
 for (int i = 0; i < n; ++i) {
 cnt += (ll)(H[i] / mid) * (W[i] / mid);
 if (cnt >= k) break; // 剪枝：提前结束
 }
 if (cnt >= k) {
 ans = mid;
 l = mid + 1;
 } else {
 r = mid - 1;
 }
 }
 cout << ans << endl;
 return 0;
}