#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int findContentChildren(vector<int>& g, vector<int>& s) {
            sort(g.begin(),g.end());
            sort(s.begin(),s.end());
            int i=0,j=0,k=0;
            while(i<g.size()&&j<s.size()){
                if(g[i]<=s[j]){
                    i++;
                    j++;
                    k++;
                }
                else{
                    j++;
                }
                
            }
            return k;
        }
};