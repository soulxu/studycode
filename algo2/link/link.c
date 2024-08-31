
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct LinkNode {
    int data_;
    struct LinkNode* next_;
} LinkNode;

typedef struct LinkNode* LinkHead;

LinkNode* newList(int data) {
    LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
    new_node->data_ = data;
    new_node->next_ = NULL;
}

void destoryList(LinkHead head) {
    LinkNode* next = head;
    while (next != NULL) {
        LinkNode* to_destory = next;
        next = next->next_;
        free(to_destory);
    }
}

LinkHead insertList(LinkHead head, int data, int index) {
    if (head == NULL || index < 0) {
        return NULL;
    }
    LinkNode* previous = NULL;
    LinkNode* pos = head;
    int i = 0;
    for (i = 0; i < index && pos != NULL; i++) {
        previous = pos;
        pos = pos->next_;
    }

    if (i < index) {
        return NULL;
    }

    LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
    new_node->data_ = data;
    new_node->next_ = NULL;

    if (previous != NULL) {
        previous->next_ = new_node;
        new_node->next_ = pos;
    } else {
        new_node->next_ = head;
        return new_node;
    }

    return head;
}

LinkHead removeList(LinkHead head, int index) {
    if (head == NULL || index < 0) {
        return NULL;
    }

    LinkNode* previous = NULL;
    LinkNode* pos = head;

    int i = 0;
    for (i = 0; i < index && pos != NULL; i++){
        previous = pos;
        pos = pos->next_;
    }

    if (pos == NULL) {
        return head;
    }

    if (previous == NULL) {
        LinkNode* new_head = pos->next_;
        free(pos);
        return new_head;
    }

    LinkNode* to_delete = pos;
    previous->next_ = pos->next_;
    free(pos);
    return head;
}

void printList(LinkHead head) {
    LinkNode* pos = head;

    while (pos != NULL) {
        printf("%d ", pos->data_);
        pos = pos->next_;
    }
    printf("\n");
}

int main(int, char**) {
    LinkHead list = newList(0);
    printList(list);
    list = insertList(list, 1, 1);
    printList(list);
    list = insertList(list, 2, 0);
    printList(list);
    list = insertList(list, 3, 2);
    printList(list);
    list = removeList(list, 2);
    printList(list);
    list = removeList(list, 0);
    printList(list);
    destoryList(list);
}