#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> answer(temperatures.size(),0);
        if(temperatures.empty())return answer;
        lh.reserve(temperatures.size()); // 预留足够的空间
        length = 0;
        for(int i=0;i<temperatures.size();i++){
            if(empty()||temperatures[getop()]>=temperatures[i])push(i);
            else if(temperatures[getop()]<temperatures[i]){
                int temp=pop();
                answer[temp]=i-temp;

                while(1){
                    if(empty()||temperatures[getop()]>=temperatures[i]){
                        push(i);
                        break;
                    }
                    else {
                        int temp1=pop();
                        answer[temp1]=i-temp1;
                    }
                }
            }
        }
        return answer;
    }
private:
    vector<int> lh;
    int length;
    int pop(){
        return lh[--length];
    }
    void push(int a){
        lh[length++]=a;
    }
    int getop(){
        return lh[length-1];
    }
    bool empty(){
        return length==0;
    }
};
int main(){
    Solution solu;
    vector<int> a{73,74,75,71,69,72,76,73};
    vector b=solu.dailyTemperatures(a);
    for(auto& c:b)cout<<c<<' ';
}