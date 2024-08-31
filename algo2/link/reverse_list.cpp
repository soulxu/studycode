#include <cstdio>

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr) {
            return head;
        }
        ListNode* smaller_head = nullptr;
        ListNode* larger_head = nullptr;
        ListNode* smaller = nullptr;
        ListNode* larger = nullptr;
        ListNode* pos = head;
        while (pos != nullptr) {
            if (pos->val <= x) {
                if (smaller == nullptr) {
                    smaller = pos;
                    smaller_head = pos;
                } else {
                    smaller->next = pos;
                    smaller = smaller->next;
                }
            } else {
                if (larger == nullptr) {
                    larger = pos;
                    larger_head = pos;
                } else {
                    larger->next = pos;
                    larger = larger->next;
                }
            }
            pos = pos->next;
        }
        if (smaller == nullptr) {
            if (larger != nullptr) {
                larger->next = nullptr;
            }
            return larger_head;
        }
        if (larger == nullptr) {
            if (smaller != nullptr) {
                smaller->next = nullptr;
            }
            return smaller_head;
        }
        smaller->next = nullptr;
        pos = smaller_head;
        while (pos != nullptr) {
            printf("smaller: %d\n", pos->val);
            pos = pos->next;
        }
        smaller->next = larger_head;
        larger->next = nullptr;
        return smaller_head;
    }
};

int main(int, char**) {
    ListNode* head  = new ListNode(1);
    ListNode* pos = head;
    pos->next = new ListNode(4);
    pos = pos->next;
    pos->next = new ListNode(3);
    pos = pos->next;
    pos->next = new ListNode(2);
    pos = pos->next;
    pos->next = new ListNode(5);
    pos = pos->next;
    pos->next = new ListNode(2);

    Solution s;
    head = s.partition(head, 3);
    pos = head;
    while (pos != nullptr) {
        printf("%d\n", pos->val);
        pos = pos->next;
    }


    return 0;
}