#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        bool canConstruct(string ransomNote, string magazine) {
            vector<int> lh(26,0);
            for(int i=0;i<magazine.size();i++){
                lh[magazine[i]-'a']++;
            }
            for(int j=0;j<ransomNote.size();j++){
                lh[ransomNote[j]-'a']--;
                if(lh[ransomNote[j]-'a']<0)return false;
            }
            return true;
        }
};
int main(){
    string a="aa";
    string b="aab";
    Solution solu;
    cout<<solu.canConstruct(a,b);
}