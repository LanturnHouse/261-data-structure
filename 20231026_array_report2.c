#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int size = 30;

    // 동적할당으로 배열 생성
    int* scores = (int*)malloc(size * sizeof(int));

    srand(time(0));
    for (int i = 0; i < size; i++) {
        scores[i] = rand() % 101;
    }

    printf("초기 학생 수: %d\n", size);
    for (int i = 0; i < size; i++) {
        printf("%2d번 학생: %d점\n", i + 1, scores[i]);
    }

    printf("\n\n================\n\n");

    int option;
    while (true) {
        printf("\n\n");
        printf("0: 학생 추가\n");
        printf("1: 학생 삭제\n");
        printf("2: 학생 출력\n");
        printf("3: 종료\n");
        printf(">>>");
        scanf("%d", &option);

        if (option == 0) {
            size++;
            scores = (int*)realloc(scores, size * sizeof(int));
            scores[size - 1] = rand() % 101;
            printf("\n%d번 학생(신규) 추가: %d점\n", size, scores[size - 1]);
        }
        else if (option == 1) {
            int deleteIndex;
            printf("삭제할 학생의 번호를 입력\n");
            printf(">>>");
            scanf("%d", &deleteIndex);
            deleteIndex--;
            //뒤 데이터들을 압으로 이동.
            for (int i = deleteIndex; i < size - 1; i++) {
                scores[i] = scores[i + 1];
            }
            size--;
            scores = (int*)realloc(scores, size * sizeof(int));
            printf("%2d 번 학생이 삭제되었습니다.\n", deleteIndex + 1);
        }
        else if (option == 2) {
            for (int i = 0; i < size; i++) {
                printf("%2d번 학생: %d점\n", i + 1, scores[i]);
            }
        }
        else if (option == 3) {
            printf("종료합니다...");
            break;
        }
        //숫자가 아닌 문자를 입력 시, break로 종료되지 않는 문제
        //원인: option의 입력값이 문자 입력 시 변환에 실패하면 입력값을 계속 버퍼에 남겨둠.
        //해결 방법: option에 3을 넣고, 다음 루프에서 자동으로 종료되도록 유도함.
        else {
            printf("올바르지 않은 입력입니다.\n 다음 루프에서 자동으로 종료합니다.");
            option = 3;
        }
    }



    // 메모리 해제
    free(scores);

}
