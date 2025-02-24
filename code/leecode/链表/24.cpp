#include<bits/stdc++.h>
using namespace std;
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// class Solution {
//     public:
//         ListNode* swapPairs(ListNode* head) {
//             if(head==nullptr||head->next==nullptr){
//                 return head;
//             }
//             if(head->next->next==nullptr){
//                 ListNode*temp=head->next;
//                 temp->next=head;
//                 head->next=nullptr;
//                 return temp;
//             }
//             ListNode* re=head->next;

//             ListNode* temp=head->next;
//             head->next=temp->next;
//             temp->next=head;

//             if(head->next->next==nullptr)return re;
//             ListNode* temp1=head;
//             ListNode* temp2=head->next;
//             ListNode* temp3=head->next->next;
            
//             while(1){
//                 temp1->next=temp3;
//                 temp1=temp3;

//                 if(temp3==nullptr)break;
//                 temp2->next=temp3->next;
//                 if(temp3->next==nullptr){
//                     temp3->next=temp2;
//                     break;
//                 }
//                 ListNode* t=temp2;
//                 temp2=temp3->next;

//                 temp3->next=t;
//                 if(temp3->next->next==nullptr)break;
//                 temp3=temp2->next->next;
//             }
//             return re;
//         }
// };

class Solution {
    public:
        ListNode* swapPairs(ListNode* head) {
            if(head==nullptr||head->next==nullptr){return head;}
            ListNode* temp=head->next;
            head->next=swapPairs(temp->next);
            temp->next=head;
            return temp;
        }
    };


    class Solution {
        public:
            ListNode* swapPairs(ListNode* head) {
                ListNode* dummyHead = new ListNode(0);
                dummyHead->next = head;
                ListNode* temp = dummyHead;
                while (temp->next != nullptr && temp->next->next != nullptr) {
                    ListNode* node1 = temp->next;
                    ListNode* node2 = temp->next->next;
                    temp->next = node2;
                    node1->next = node2->next;
                    node2->next = node1;
                    temp = node1;
                }
                ListNode* ans = dummyHead->next;
                delete dummyHead;
                return ans;
            }
        };