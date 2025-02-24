#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        bool isAnagram(string s, string t) {
            sort(s.begin(),s.end());
            sort(t.begin(),t.end());
            return s==t;
        }
};
class Solution {
    public:
        bool isAnagram(string s, string t) {
            if(s.length()!=t.length())return false;
            vector<int> table(26,0);
            for(auto& x: s){
                table[x-'a']++;
            }
            for(auto& x:t){
                table[x-'a']--;
                if(table[x-'a']<0){
                    return false;
                }
            }
            return true;
        }
};