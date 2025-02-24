#include<bits/stdc++.h>
using namespace std;
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
    public:
        ListNode* reverseList(ListNode* head) {
            if(head==nullptr||head->next==nullptr){
                return head;
            }
            if(head->next->next==nullptr){
                ListNode*temp=head->next;
                temp->next=head;
                head->next=nullptr;
                return temp;
            }
            ListNode* temp1=head;
            ListNode* temp2=head->next;
            ListNode* temp3=head->next->next;
            temp1->next=nullptr;
            for(;temp3!=nullptr;){
                temp2->next=temp1;
                temp1=temp2;
                temp2=temp3;
                temp3=temp3->next;
            }
            temp2->next=temp1;
            return temp2;
        }
};