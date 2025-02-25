#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
        int trap(vector<int>& height) {
        if(height.size()<2){
            return 0;
        }

        lh=vector<int>(height.size(),0);
        lenth=0;
        int max=-1;
        int index;
        for(int i=0;i<height.size();i++){
            if(max<height[i]){
                max=height[i];
                index=i;
            }
        }

        // int begin=0;
        // while(height[begin]==height[begin+1]){
        //     begin++;
        // }
        // if(height[begin]<height[begin+1]){
        //     begin++;
        // }
        // int end=height.size()-1;
        // while(height[end]==height[end-1]){
        //     end--;
        // }
        // if(height[end]<height[end-1]){
        //     end--;
        // }



        int sum=0;
        max=-1;
        for(int i=0;i<=index;i++){
            if(lenth==0){
                push(i);
                max=height[i];
            }
            else if(lenth>0&&height[i]>=max){
                while(lenth>0){
                    sum+=(max-height[pop()]);
                }
                push(i);
                max=height[i];

            }
            else if(!empty()&&height[i]<max){
                push(i);
            }
        }

        pop();
        max=-1;
        int n=height.size()-1;
        for(int i=n;i>=index;--i){
            if(lenth==0){
                push(i);
                max=height[i];
            }
            else if(lenth>0&&height[i]>=max){
                while(lenth>0){
                    sum+=(max-height[pop()]);
                }
                push(i);
                max=height[i];

            }
            else if(!empty()&&height[i]<max){
                push(i);
            }
        }
        return sum;
    }
private:
    int lenth;
    vector<int> lh;
    int pop(){
        return lh[--lenth];
    }
    void push(int x){
        lh[lenth++]=x;
    }
    int getop(){
        return lh[lenth-1];
    }
    bool empty(){
        return lenth==0;
    }
};
int main(){
    Solution solu;
    vector<int> lh{0,1,0,2,1,0,1,3,2,1,2,1};
    cout<<solu.trap(lh);
}