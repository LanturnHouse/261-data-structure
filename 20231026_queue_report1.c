// 261-datastruct-6.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdio.h>
#include <stdbool.h>


#define SIZE 5

typedef struct {
	int data[SIZE];
	int front;
	int rear;
} LinearQueue;

void initQueue(LinearQueue* q) {
	q->front = 0;
	q->rear = -1;
}

bool isEmpty(LinearQueue* q) {
	return q->rear < q->front;
}

bool isFull(LinearQueue* q) {
	return q->rear == SIZE - 1;
}

bool enqueue(LinearQueue* q, int value) {
	if (isFull(q)) {
		printf("큐가 가득 찼습니다.\n");
		return true;
	}
	q->rear++;
	q->data[q->rear] = value;
	return true;
}


void shiftQueueLeft(LinearQueue* q) {
	if (isEmpty(q)) {
		printf("큐가 비어있습니다.\n");
		return;
	}
	printf("큐 공간 최적화중...\n");
	for (int i = 0; i < q->rear - q->front + 1; i++) {
		q->data[i] = q->data[q->front + i];
	}
	q->rear = q->rear - q->front;
	q->front = 0;
	printf("큐 공간 최적화 완료.\n");
}

int dequeue(LinearQueue* q) {
	if (isEmpty(q)) {
		printf("큐가 비어있습니다.\n");
		return -1;
	}
	int value = q->data[q->front];
	q->front++;
	shiftQueueLeft(q);
	return value;
}


void printQueue(LinearQueue* q) {
	for (int i = q->front; i < q->rear + 1; i++) {
		printf("%d\n", q->data[i]);
	}
}

int main() {
	LinearQueue q;
	initQueue(&q);

	int menuInput;
	int input;

	while (1) {
		menuInput = 0;
		input = 0;

		printf("==== 큐 메뉴 ====\n");
		printf("1: 큐 삽입\n");
		printf("2: 큐 삭제\n");
		printf("3: 큐 출력\n");
		printf("4: 종료\n");
		printf(">>> ");


		scanf("%d", &menuInput);
		switch (menuInput) {
		case 1:
			printf("삽입할 데이터를 입력하세요.\n>>> ");
			scanf("%d",&input);
			enqueue(&q, input);
			printf("데이터 [%d]가 삽입되었습니다.\n", input);
			break;
		case 2:
			printf("데이터 [%d]가 삭제되었습니다.\n", dequeue(&q));
			break;
		case 3:
			printQueue(&q);
			break;
		case 4:
			printf("프로그램을 종료합니다...\n");
			return 0;
		}

		printf("\n\n");

	}
}
