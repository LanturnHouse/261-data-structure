#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdio.h>
#include <stdbool.h>


#define SIZE 30




//프린터 대기열 구현.
typedef struct {
    char documentName[50];
    int numPage;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;


void initqueue(PrintQueue*q) {
    q->front = 0;
    q->rear = 0;
}

bool isFull(PrintQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}

bool isEmpty(PrintQueue*q) {
    return q->front == q->rear;
}

void printQueue(PrintQueue* q) {
    for (int i = q->front; i < q->rear; i++) {
        printf("작업 이름: %s   작업 수: %d\n", q->queue[i].documentName, q->queue[i].numPage);
    }
}


bool enqueue(PrintQueue *q, char* documentName, int numPage) {
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.");
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
        PrintJob emptyJob = { ", 0" };
        return emptyJob;
    }
    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}



int main()
{

    PrintQueue q;
    initqueue(&q);

    int choice;
    int numPage;
    char documentName[50];



    while (1) {
        printf("\n\n");
        printf("실행할 작업을 입력.\n");
        printf("1: 작업 추가    2: 작업 실행    3: 작업 목록    4: 종료\n");
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

            case 2:
                PrintJob job = dequeue(&q);
                if (strlen(job.documentName) > 0) {
                    printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPage);
                }
                break;

            case 3:
                printQueue(&q);
                break;
            case 4:
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
                break;

        }

    }

}

