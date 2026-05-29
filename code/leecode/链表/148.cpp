class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return sortList(head, nullptr);
    }

    ListNode* sortList(ListNode* head, ListNode* tail) {
        if(head==nullptr)return head;
        if(head->next==tail){
            head->next=nullptr;
            return head;
        }
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast!=tail){
            slow=slow->next;
            fast=fast->next;
            if(fast!=tail)fast=fast->next;
        }
        ListNode* mid=slow;
        return merge(sortList(head,mid),sortList(mid,tail));
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        if(head1==nullptr)return head2;
        if(head2==nullptr)return head1;
        ListNode* ptr1=head1;
        ListNode* ptr2=head2;
        ListNode* ans;
        if(ptr1->val>=ptr2->val){
            ans=ptr2;
            ptr2=ptr2->next;
        }
        else {
            ans=ptr1;
            ptr1=ptr1->next;
        }
        ListNode* now=ans;
        while(ptr1!=nullptr||ptr2!=nullptr){
            if(ptr1==nullptr){
                now->next=ptr2;
                break;
            }
            if(ptr2==nullptr){
                now->next=ptr1;
                break;
            }
            if(ptr1->val>=ptr2->val){
                now->next=ptr2;
                ptr2=ptr2->next;
            }
            else {
                now->next=ptr1;
                ptr1=ptr1->next;
            }
            now=now->next;

        }   
        return ans;
    }
};
