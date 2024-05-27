#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct {
    char name[100];
} Names;

typedef Names element;

typedef struct listNode {
    element data;
    struct listNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = h;
    return p;
}

ListNode* insert_last(ListNode* h, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = NULL;

    if (h == NULL) {
        return p;
    }

    ListNode* temp = h;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    temp->link = p;
    return h;
}

ListNode* search_list(ListNode* h, char* x) {
    ListNode* p = h;
    while (p != NULL) {
        if (strcmp(p->data.name, x) == 0) {
            return p;
        }
        p = p->link;
    }
    return NULL;
}

ListNode* delete_first(ListNode* h, ListNode** removed) {
    if (h == NULL) return NULL;
    ListNode* remove = h;
    h = remove->link;
    *removed = remove;
    return h;
}

ListNode* delete_node(ListNode* h, ListNode* pre, ListNode** removed) {
    if (pre->link == NULL) return h;
    ListNode* remove = pre->link;
    pre->link = remove->link;
    *removed = remove;
    return h;
}

void print_list(ListNode* h) {
    while (h != NULL) {
        printf("[%s] ", h->data.name);
        h = h->link;
    }
    printf("\n");
}

int main() {
    ListNode* head = NULL;
    ListNode* removed_head = NULL;
    Names data;

    // 리스트 초기화
    char* fruits[] = { "Mango", "Orange", "Apple", "Grape", "Cherry", "Plum", "Guava", "Raspberry", "Banana", "Peach" };
    for (int i = 0; i < 10; i++) {
        strcpy(data.name, fruits[i]);
        head = insert_first(head, data);
    }

    int choice = 0;
    Names f;
    while (1) {
        printf("\n메뉴 : \n");
        printf("1. 리스트 맨 마지막에 추가\n");
        printf("2. 리스트에서 삭제\n");
        printf("3. 삭제된 리스트 출력\n");
        printf("4. 프로그램 종료\n");
        printf("선택 : ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 과일을 입력해주세요 : ");
            scanf_s("%s", f.name, (unsigned int)sizeof(f.name));
            if (search_list(head, f.name)) {
                printf("리스트에 이미 존재하는 과일입니다. \n");
            }
            else {
                head = insert_last(head, f);
                printf("과일 %s을(를) 추가했습니다.\n", f.name);
            }
            break;
        case 2:
            printf("삭제할 과일을 입력해주세요 : ");
            scanf_s("%s", f.name, (unsigned int)sizeof(f.name));
            ListNode* s = search_list(head, f.name);
            if (s == NULL) {
                printf("리스트에 존재하지 않는 과일입니다. \n");
            }
            else {
                ListNode* removed = NULL;
                if (head == s) {
                    head = delete_first(head, &removed);
                }
                else {
                    ListNode* temp = head;
                    while (temp->link != s) {
                        temp = temp->link;
                    }
                    head = delete_node(head, temp, &removed);
                }
                removed->link = removed_head;
                removed_head = removed;
                printf("과일 %s을(를) 삭제했습니다.\n", f.name);
            }
            break;
        case 3:
            printf("삭제된 리스트: ");
            print_list(removed_head);
            break;
        case 4:
            while (head != NULL) {
                ListNode* temp = head;
                head = head->link;
                free(temp);
            }
            while (removed_head != NULL) {
                ListNode* temp = removed_head;
                removed_head = removed_head->link;
                free(temp);
            }
            exit(0);
        default:
            printf("잘못된 선택입니다.\n");
            break;
        }
    }

    return 0;
}
