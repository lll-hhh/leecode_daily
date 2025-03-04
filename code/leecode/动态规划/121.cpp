#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty())return 0;
        int minn=10000000;
        int maxx=0;
        for(int i=0;i<prices.size();i++){
            maxx=max(maxx,prices[i]-minn);
            if(minn>prices[i])minn=prices[i];
        }
        return maxx;
    }
};
int main(){
    vector<int> lh={7,1,5,3,6,4};
    Solution s;
    cout<<s.maxProfit(lh);
}