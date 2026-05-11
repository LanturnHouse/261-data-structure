#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    char name[10];
    int number;
};

// 노드 구조체 정의
typedef struct Node {
    Contact data;
    struct Node* next;
} Node;

// 첫 번째 노드 삽입 함수
Node* insertFirst(Node* head, Contact data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    newNode->next = head;
    return newNode;
}

Node* insertLast(Node* head, Contact data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return head;
}

Node* deleteHead(Node* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    Node* temp = head;
    head = head->next;
    free(temp);

    return head;
}

Node* deleteLast(Node* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Node* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;

    return head;
}

Node* deleteNode(Node* head, const char* targetName) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    if (strcmp(head->data.name, targetName) == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next != NULL && strcmp(current->next->data.name, targetName) != 0) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("이름 '%s'를 가진 노드를 찾을 수 없습니다.\n", targetName);
        return head;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);

    return head;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("(%s, %d) -> ", current->data.name, current->data.number);
        current = current->next;
    }
    printf("NULL\n");
}

// 이름으로 위치 검색
int searchValue1(Node* head, const char* targetName) {
    int pos = 2;
    if (head == NULL) {
        printf("리스트가 비어 있습니다.\n");
        return -1;
    }

    if (strcmp(head->data.name, targetName) == 0) {
        return 1;
    }

    Node* current = head;
    while (current->next != NULL && strcmp(current->next->data.name, targetName) != 0) {
        pos = pos + 1;
        current = current->next;
    }

    if (current->next == NULL) {
        printf("이름 '%s'를 가진 노드를 찾을 수 없습니다.\n", targetName);
        return -1;
    }

    return pos;
}

// 이름으로 전화번호 확인
void searchValue2(Node* head, const char* targetName) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->data.name, targetName) == 0) {
            printf("이름: %s | 전화번호: %d\n", current->data.name, current->data.number);
            return;
        }
        current = current->next;
    }

    printf("이름 '%s'를 가진 노드를 찾을 수 없습니다.\n", targetName);
}

void freeList(Node* head) {
    if (head == NULL) {
        printf("\n\n모든 리스트를 메모리에서 제거 완료...");
        return;
    }
    freeList(head->next);
    free(head);
}

int main() {
    Node* head = NULL;

    Contact contacts[9] = {
        {"김민준", 1011111111},
        {"이서연", 1022222222},
        {"박지호", 1033333333},
        {"최수아", 1044444444},
        {"정도윤", 1055555555},
        {"강하은", 1066666666},
        {"조시우", 1077777777},
        {"윤채원", 1088888888},
        {"장예준", 1099999999},
    };

    for (int i = 8; i >= 0; i--) {
        head = insertFirst(head, contacts[i]);
    }

    // 리스트 출력
    printf("\n아래는 리스트 출력입니다.\n");
    printList(head);

    // 연락처 추가
    Contact newContact = { "홍길동", 1000000000 };
    head = insertLast(head, newContact);
    printf("\n'%s' 추가 후:\n", newContact.name);
    printList(head);

    // 이름으로 검색 (위치)
    const char* target = "박지호";
    int pos = searchValue1(head, target);
    printf("\n%s의 위치는 %d번째\n", target, pos);

    // 이름으로 전화번호 확인
    searchValue2(head, target);

    // 이름으로 삭제
    head = deleteNode(head, "최수아");
    printf("\n'최수아' 삭제 후:\n");
    printList(head);

    freeList(head);
    return 0;
}
