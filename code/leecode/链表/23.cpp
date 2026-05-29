/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists,0,lists.size()-1);
    }
    ListNode* merge(vector<ListNode*>& lists,int fisrt,int end){
        if(fisrt==end)return lists[fisrt];
        else if(fisrt>end)return nullptr;
        int mid=(fisrt+end)/2;
        return mergetwo(merge(lists,fisrt,mid),merge(lists,mid+1,end));
    }
    ListNode* mergetwo(ListNode* lists1,ListNode* lists2){
        if(lists1==nullptr)return lists2;
        if(lists2==nullptr)return lists1;
        ListNode* temp1=lists1;
        ListNode* temp2=lists2;
        ListNode* ans;
        if(temp1->val>=temp2->val){
            ans=temp2;
            temp2=temp2->next;
        }else{
            ans=temp1;
            temp1=temp1->next;
        }
        ListNode* temp3=ans;
        while(temp1!=nullptr&&temp2!=nullptr){
            if(temp1->val>=temp2->val){
                temp3->next=temp2;
                temp2=temp2->next;
            }
            else {
                temp3->next=temp1;
                temp1=temp1->next;
            }
            temp3=temp3->next;
        }
        temp3->next = temp1 ? temp1 : temp2;
        return ans;
    }
};