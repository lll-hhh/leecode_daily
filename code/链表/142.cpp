#include<bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            if(head==nullptr||head->next==nullptr){
                return nullptr;
            }
            ListNode* temp1=head;
            ListNode* temp2=head;
            do{
                temp1=temp1->next;
                if(temp2->next==nullptr||temp2->next->next==nullptr)return nullptr;
                temp2=temp2->next->next;
            } while(temp1!=temp2);
            ListNode* temp3=head;
            while(temp1!=temp3){
                temp1=temp1->next;
                temp3=temp3->next;
            }
            return temp3;
        }
};

class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            ListNode *slow = head, *fast = head;
            while (fast != nullptr) {
                slow = slow->next;
                if (fast->next == nullptr) {
                    return nullptr;
                }
                fast = fast->next->next;
                if (fast == slow) {
                    ListNode *ptr = head;
                    while (ptr != slow) {
                        ptr = ptr->next;
                        slow = slow->next;
                    }
                    return ptr;
                }
            }
            return nullptr;
        }
    };