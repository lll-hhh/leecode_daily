#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> ans;
    string path;

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return ans;

        vector<string> mp = {
            "",     // 0
            "",     // 1
            "abc",  // 2
            "def",  // 3
            "ghi",  // 4
            "jkl",  // 5
            "mno",  // 6
            "pqrs", // 7
            "tuv",  // 8
            "wxyz"  // 9
        };

        backtrack(digits, mp, 0);

        return ans;
    }

    void backtrack(string digits,vector<string> mp,int n){
        if(path.size()==digits.size()){
            ans.push_back(path);
            return;
        }
        int digit =digits[n]-'0';
        string liuhao=mp[digit];
        for(auto c:liuhao){
            path.push_back(c);

            backtrack(digits,mp,n+1);

            path.pop_back();
        }
    }

};