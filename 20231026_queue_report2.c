#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define SIZE 30
#define MAX_PAGE 50  // 인쇄 가능한 최대 페이지 수


typedef struct {
    char documentName[50];
    int numPage;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;


void initQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
}

bool isFull(PrintQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}

bool isEmpty(PrintQueue* q) {
    return q->front == q->rear;
}

void printQueue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어있습니다.\n");
        return;
    }
    printf("현재 대기 중인 작업:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("  - %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPage);
        i = (i + 1) % SIZE;
    }
}

// 50페이지 초과 시 거부 메시지 출력 후 삽입 안 함
bool enqueue(PrintQueue* q, char* documentName, int numPage) {
    if (numPage > MAX_PAGE) {
        printf("'%s'은(는) %d 페이지로 최대 허용 페이지(%d)를 초과하여 거부되었습니다.\n",
            documentName, numPage, MAX_PAGE);
        return false;
    }
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }
    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPage = numPage;
    q->rear = (q->rear + 1) % SIZE;
    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPage);
    return true;
}

PrintJob dequeue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어있습니다. 작업이 없습니다.\n");
        PrintJob emptyJob = { "", 0 };
        return emptyJob;
    }
    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

// 특정 문서 이름을 가진 작업을 대기열에서 제거 후 나머지 앞으로 이동
void cancelJob(PrintQueue* q, char* targetName) {
    if (isEmpty(q)) {
        printf("대기열이 비어있습니다.\n");
        return;
    }

    // 대상 문서 탐색
    int i = q->front;
    int found = -1;
    while (i != q->rear) {
        if (strcmp(q->queue[i].documentName, targetName) == 0) {
            found = i;
            break;
        }
        i = (i + 1) % SIZE;
    }

    if (found == -1) {
        printf("해당 문서가 없습니다.\n");
        return;
    }

    // 찾은 위치 이후 작업들을 한 칸씩 앞으로 이동
    int cur = found;
    int next = (found + 1) % SIZE;
    while (next != q->rear) {
        q->queue[cur] = q->queue[next];
        cur = next;
        next = (next + 1) % SIZE;
    }
    q->rear = cur;

    printf("작업 '%s'가 대기열에서 취소되었습니다.\n", targetName);
}

// 대기열 전체 초기화
void clearQueue(PrintQueue* q) {
    initQueue(q);
    printf("대기열 초기화 완료.\n");
}


int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    int numPage;
    char documentName[50];

    while (1) {
        printf("\n\n");
        printf("실행할 작업을 입력.\n");
        printf("1: 작업 추가    2: 작업 실행    3: 작업 목록\n");
        printf("4: 작업 취소    5: 대기열 초기화    6: 종료\n");
        printf(">>> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("문서이름: ");
                scanf("%s", documentName);
                printf("페이지 수: ");
                scanf("%d", &numPage);
                enqueue(&q, documentName, numPage);
                break;

            case 2: {
                PrintJob job = dequeue(&q);
                if (strlen(job.documentName) > 0) {
                    printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPage);
                }
                break;
            }

            case 3:
                printQueue(&q);
                break;

            case 4:
                printf("취소할 문서 이름: ");
                scanf("%s", documentName);
                cancelJob(&q, documentName);
                break;

            case 5:
                clearQueue(&q);
                break;

            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;

            default:
                printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
                break;
        }
    }
}
