#include <iostream>

// // 定义链表节点类
// class MyLinkedListNode {
// public:
//     int val;
//     MyLinkedListNode* next;
//     MyLinkedListNode() : val(0), next(nullptr) {}
//     MyLinkedListNode(int x) : val(x), next(nullptr) {}
//     MyLinkedListNode(int x, MyLinkedListNode* next) : val(x), next(next) {}
// };

// // 定义链表管理jkl类
// class MyLinkedList {
// private:
//     static MyLinkedListNode* head;

// public:
//     MyLinkedList() {}

//     // 获取索引处的值
//     int get(int index) {
//         MyLinkedListNode* temp = head;
//         for (int i = 0; i < index && temp != nullptr; ++i) {
//             temp = temp->next;
//         }
//         if (temp == nullptr) return -1; // 索引超出范围
//         return temp->val;
//     }

//     // 在头部添加节点
//     void addAtHead(int val) {
//         MyLinkedListNode* newNode = new MyLinkedListNode(val);
//         newNode->next = head;
//         head = newNode;
//     }

//     // 在尾部添加节点
//     void addAtTail(int val) {
//         MyLinkedListNode* newNode = new MyLinkedListNode(val);
//         if (head == nullptr) {
//             head = newNode;
//             return;
//         }
//         MyLinkedListNode* temp = head;
//         while (temp->next != nullptr) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//     }

//     // 在指定索引处添加节点
//     void addAtIndex(int index, int val) {
//         if (index == 0) {
//             addAtHead(val);
//             return;
//         }
//         MyLinkedListNode* temp = head;
//         for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
//             temp = temp->next;
//         }
//         if (temp == nullptr) return; // 索引超出范围
//         MyLinkedListNode* newNode = new MyLinkedListNode(val);
//         newNode->next = temp->next;
//         temp->next = newNode;
//     }

//     // 删除指定索引处的节点
//     void deleteAtIndex(int index) {
//         if (index == 0) {
//             MyLinkedListNode* temp = head;
//             head = head->next;
//             delete temp;
//             return;
//         }
//         MyLinkedListNode* temp = head;
//         for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
//             temp = temp->next;
//         }
//         if (temp == nullptr || temp->next == nullptr) return; // 索引超出范围
//         MyLinkedListNode* toDelete = temp->next;
//         temp->next = temp->next->next;
//         delete toDelete;
//     }
// };

// // 初始化静态成员变量
// MyLinkedListNode* MyLinkedList::head = nullptr;

// int main() {
//     MyLinkedList linkedList;
//     linkedList.addAtHead(1);
//     linkedList.addAtTail(3);
//     linkedList.addAtIndex(1, 2); // 链表变为 1->2->3
//     std::cout << linkedList.get(1) << std::endl; // 返回 2
//     linkedList.deleteAtIndex(1); // 现在链表为 1->3
//     std::cout << linkedList.get(1) << std::endl; // 返回 3
//     return 0;
// }
struct ListNode{
public:
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next){}
};
class MyLinkedList{
public:
    MyLinkedList():size(0),head(nullptr){}
    int get(int index){
        if (index < 0 || index >= size || head == nullptr) return -1;
        else {
            if(index==0)return head->val;
            else{
                ListNode *temp=head;
                while(index--){
                    temp=temp->next;
                }
                return temp->val;
            }
        }
    }

    void addAtHead(int val){
        addAtIndex(0,val);
    }
    void addAtTail(int val){
        addAtIndex(size,val);
    }
    void addAtIndex(int index, int val){
        if(index>size){
            return ;
        }
        else {
            if(index==0){
                ListNode* temp=new ListNode();
                temp->val=val;
                temp->next=head;
                head=temp;
            }
            else {
                ListNode* temp=head;
                while(--index)temp=temp->next;
                ListNode* temp2=new ListNode();
                temp2->val=val;
                if(temp){
                    temp2->next=temp->next;
                    temp->next=temp2;
                }
                else temp2->next=nullptr;
            }
        }
        size++;
    }
    void deleteAtIndex(int index){
        if(index<0||index>=size){
            return ;
        }
        else if(index==0){
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        else{
            ListNode* temp=head;
            while(--index)temp=temp->next;
            if(temp->next){
            ListNode* temp2=temp->next;
            temp->next=temp->next->next;
            delete temp2;
            }
        }
        size--;
    }
private:
    int size;
    ListNode* head;
};