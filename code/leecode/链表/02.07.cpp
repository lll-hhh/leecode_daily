# include<bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            if(headA==nullptr||headB==nullptr){
                return nullptr;
            }
            int i=0;
            int j=0;
            ListNode* temp_a=headA;
            ListNode* temp_b=headB;
            for(;temp_a->next!=nullptr;i++){
                temp_a=temp_a->next;
            }
            for(;temp_b->next!=nullptr;j++){
                temp_b=temp_b->next;
            }
            if(temp_a!=temp_b)return nullptr;
            else {
                int k=i>j?(i-j):(j-i);
                ListNode* temp_1=i>j?headA:headB;
                ListNode* temp_2=i>j?headB:headA;
                while(k--){
                    temp_1=temp_1->next;
                }
                while(temp_1!=temp_2){
                    temp_1=temp_1->next;
                    temp_2=temp_2->next;
                }
                return temp_1;
            }
        }
    };