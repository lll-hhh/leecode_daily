#include<bits/stdc++.h>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode():val(0),next(nullptr){}
    ListNode(int x):val(x),next(nullptr){}
    ListNode(int x,ListNode* next):val(x),next(next){}
};
class Solution {
    public:
        ListNode* removeElements(ListNode* head, int val) {
            if(!head)return nullptr;
            while(head!=nullptr&&head->val==val){
                ListNode *temp=head;
                head=head->next;
                delete temp;
            }
            ListNode* ptr=head;
            while(ptr&&ptr->next){
                if(ptr->next->val==val){
                    ListNode *temp=ptr->next;
                    if(ptr->next->next!=nullptr)
                        ptr->next=ptr->next->next;
                    else ptr->next=nullptr;
                    delete temp;
                }
                else ptr=ptr->next;
            }
            return head;
    }
};