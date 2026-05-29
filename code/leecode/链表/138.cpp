class Solution {
public:
    unordered_map<Node*, Node*> cachedNode;

    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        while(!cachedNode.count(head)){
            Node* nextt=new Node(head->val);
            cachedNode[head]=nextt;
            nextt->next=copyRandomList(head->next);
            nextt->random=copyRandomList(head->random);
        }
        return cachedNode[head];
    }
};
