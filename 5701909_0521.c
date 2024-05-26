#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
    char data[30];
    struct listNode* link;
} ListNode;

ListNode* insert_last(ListNode* h, char* value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    strcpy(p->data, value);
    p->link = NULL;

    if (h == NULL) {
        return p;
    }
    else {
        ListNode* temp = h;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = p;
    }
    return h;
}

ListNode* delete(ListNode* h, char* value, ListNode** deleted) {
    ListNode* p = h;
    ListNode* prev = NULL;

    while (p != NULL && strcmp(p->data, value) != 0) {
        prev = p;
        p = p->link;
    }

    if (p == NULL) {
        printf("해당 과일 %s가 리스트에 없습니다.\n", value);
        return h;
    }

    if (prev == NULL) {
        h = p->link;
    }
    else {
        prev->link = p->link;
    }

    p->link = NULL;
    *deleted = insert_last(*deleted, p->data);
    free(p);
    return h;
}

void print_list(ListNode* h) {
    while (h != NULL) {
        printf("%s ", h->data);
        h = h->link;
    }
    printf("\n");
}

int search_list(ListNode* h, char* value) {
    ListNode* p = h;
    while (p != NULL) {
        if (strcmp(p->data, value) == 0) {
            return 1;
        }
        p = p->link;
    }
    return 0;
}

void display_menu() {
    printf("메뉴:\n");
    printf("1. 리스트의 마지막에 새로운 과일 추가\n");
    printf("2. 리스트에서 과일 삭제\n");
    printf("3. 삭제된 과일 목록 출력\n");
    printf("4. 종료\n");
}

int main() {
    ListNode* head = NULL;
    ListNode* deleted = NULL;
    char* initial_fruits[] = { "Mango", "Orange", "Apple", "Grape", "Cherry", "Plum", "Guava", "Raspberry", "Banana", "Peach" };
    for (int i = 0; i < 10; i++) {
        head = insert_last(head, initial_fruits[i]);
    }

    int choice;
    char fruit[30];
    do {
        display_menu();
        printf("원하는 작업을 선택하세요: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("추가할 과일을 입력하세요: ");
            scanf("%s", fruit);
            if (!search_list(head, fruit)) {
                head = insert_last(head, fruit);
                printf("%s가 리스트에 추가되었습니다.\n", fruit);
            }
            else {
                printf("%s는 이미 리스트에 존재합니다.\n", fruit);
            }
            break;
        case 2:
            printf("삭제할 과일을 입력하세요: ");
            scanf("%s", fruit);
            head = delete(head, fruit, &deleted);
            break;
        case 3:
            printf("삭제된 과일 목록: ");
            print_list(deleted);
            break;
        case 4:
            printf("프로그램을 종료합니다...\n");
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    } while (choice != 4);

    return 0;
}
