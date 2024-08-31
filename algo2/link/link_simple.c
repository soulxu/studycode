
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct LinkNode {
    int data_;
    struct LinkNode* next_;
} LinkNode;

LinkNode* newNode(int data) {
    LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
    new_node->data_ = data;
    new_node->next_ = NULL;
}

LinkNode* insertAfter(LinkNode* pos, LinkNode* new_node) {
    if (pos == NULL || new_node == NULL) {
        return NULL;
    }
    new_node->next_ = pos->next_;
    pos->next_ = new_node;
    return new_node;
}

LinkNode* removeAfter(LinkNode* pos) {
    if (pos == NULL) {
        return NULL;
    }
    LinkNode* ret = pos->next_;
    pos->next_ = ret->next_;
    ret->next_ = NULL;
    return ret;
}
void printList(LinkNode* head) {
    LinkNode* pos = head;

    while (pos != NULL) {
        printf("%d ", pos->data_);
        pos = pos->next_;
    }
    printf("\n");
}

void destoryList(LinkNode* head) {
    LinkNode* next = head;
    while (next != NULL) {
        LinkNode* to_destory = next;
        next = next->next_;
        free(to_destory);
    }
}
int main(int, char**) {
    LinkNode* head = newNode(0);
    LinkNode* pos = head;
    for (int i = 1; i < 10; i++) {
        LinkNode* new_node = newNode(i);
        pos = insertAfter(pos, new_node);
    }
    printList(head);
    destoryList(head);
}