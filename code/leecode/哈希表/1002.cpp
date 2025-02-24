#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        vector<string> commonChars(vector<string>& words) {
            vector<vector<int>> table(26,vector<int>(words.size(),0));
            vector<string> answer;
            for(int i=0;i<words.size();i++){
                for(auto& b:words[i]){
                    table[b-'a'][i]++;
                }
            }
            for(int i=0;i<table.size();i++){
                int min = table[i][0];
                for(auto& b:table[i]){
                    if(b==0) break;
                    else{
                        if(min>b){
                            min=b;
                        }
                    }
                }
                while(min--){
                    ;
                    answer.push_back(string('a'+i,1));
                }
            }
            return answer;
        }
};