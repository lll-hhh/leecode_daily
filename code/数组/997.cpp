#include<bits/stdc++.h>

class Solution {
public:
    int findJudge(int n, std::vector<std::vector<int>>& trust) {
        std::vector<int> judge(n+1);
        for(int i=0;i<trust.size();i++){
            judge[trust[i][0]]=-1;
            if(judge[trust[i][1]]!=-1)
                judge[trust[i][1]]++;
        }
        for(int i=1;i<n+1;i++){
            if(judge[i]==n-1){
                return i;
            }
        }
        return -1;
    }
};
int main (){
    Solution s;
    int p_num=0;
    std::vector<std::vector<int>> trust;
    std::cin>>p_num;
    for(int i=0;i<p_num;i++){
        std::vector<int> temp1;
        int a,b;
        std::cin>>a>>b;
        temp1.push_back(a);
        temp1.push_back(b);
        trust.push_back(temp1);
    }
    std::cout<<s.findJudge(p_num,trust)<<std::endl;
}