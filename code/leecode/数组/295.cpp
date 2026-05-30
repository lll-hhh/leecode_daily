#include <bits/stdc++.h>
using namespace std;
class MedianFinder {
public:
    priority_queue<int,vector<int>,less<int>> queMin;
    priority_queue<int,vector<int>,greater<int>> queMax;
    MedianFinder() {}

    void addNum(int num) {
        if(queMin.size()==queMax.size()){
            queMax.push(num);
            queMin.push(queMax.top());
            queMax.pop();
        }
        else{
            queMin.push(num);
            queMax.push(queMin.top());
            queMin.pop();
        }
    }

    double findMedian() {
        if (queMin.size() > queMax.size()) {
            return queMin.top();
        }
        return (queMin.top() + queMax.top()) / 2.0;
    }
};
