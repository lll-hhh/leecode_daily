#include <bits/stdc++.h>
using namespace std;
class MyQueue {
public:
    MyQueue() {
        in=vector<int>(10,0);
        out=vector<int>(10,0); 
        linl=0;
        linr=0;
        lout=0;   
    }
        
    void push(int x) {
        in[linl++]=x;
    }
        
    int pop() {
        lout=0;
        int x=linl;
        for(;linr<x;){
            out[lout++]=in[--x];
        }
        linr++;
        return out[lout-1];
    }
        
    int peek() {
        lout=0;
        int x=linl;
        for(;linr<x;){
            out[lout++]=in[--x];
        }
        return out[lout-1];
    }
        
    bool empty() {
        return linl==linr;
    }
private:
    vector<int> in;
    vector<int> out;
    int linl;
    int linr;
    int lout;
};
int main(){
    MyQueue* obj = new MyQueue();
    obj->push(1);
    int param_2 = obj->pop();
    int param_3 = obj->peek();
    bool param_4 = obj->empty();
    cout<<param_2<<' '<<param_3<<' '<<param_4<<endl;
}