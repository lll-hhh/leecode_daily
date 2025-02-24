#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int lengthOfLastWord(string s) {
            int n=s.length();
            int num=0;
            int j=n-1;
            for(;j>=0;j--){
                if(s[j]==' ')continue;
                else break;
            }
            for(;j>=0;j--){
                if(s[j]!=' ')num++;
                else break;
            }
            return num;
        }
    };