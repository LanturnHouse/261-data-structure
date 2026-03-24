#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculateAverage(int scores[], int size);
void printScore(int scores[], int size, double average, int option);

int main() {
    int scores[30];
    int printOption;
    double average;

    srand(time(0));

    for (int i = 0; i < 30; i++) {
        scores[i] = rand() % 101;
    }

    average = calculateAverage(scores, 30);
    printf("학급 평균 점수: %.2f\n", average);

    printf("출력 옵션을 선택하세요.\n0: 모두\n1: 평균 이상\n2: 평균 미만\n>>> ");
    scanf("%d", &printOption);

    printScore(scores, 30, average, printOption);
    return 0;
}

double calculateAverage(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / (double)size;
}


void printScore(int scores[], int size, double average, int option) {
    for (int i = 0; i < size; i++) {
        int s = scores[i];
        if (option == 0 ||
            (option == 1 && s >= average) ||
            (option == 2 && s < average)) {
            printf("%2d번 학생: %d점\n", i + 1, s);
        }
    }
}
