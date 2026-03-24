// 배열은 동적할당을 사용하지 않은 크기 100의 배열을 사용하였습니다.




int isOpenBracket(char c) {
    if (c == '(') {
        return 1;
    }
    else if (c == '{') {
        return 1;
    }
    else if (c == '[') {
        return 1;
    }
    else {
        return 0;
    }
}
int isCloseBracket(char c) {
    if (c == ')') {
        return 1;
    }
    else if (c == '}') {
        return 1;
    }
    else if (c == ']') {
        return 1;
    }
    else {
        return 0;
    }
}
char getPairBracket(char c) {
    if (c == '(') {
        return ')';
    }
    else if (c == '{') {
        return '}';
    }
    else if (c == '[') {
        return ']';
    }
    else if (c == ')') {
        return '(';
    }
    else if (c == '}') {
        return '{';
    }
    else if (c == ']') {
        return '[';
    }
}


int main() {
    Stack s;
    initStack(&s);

    char str[100];

    printf("검사할 괄호 문자를 입력: ");
    //공백을 포함한 입력을 받기
    scanf(" %[^\n]", str);
    for (int i = 0; i < strlen(str); i++) {
        if (isOpenBracket(str[i])) {
            push(&s, str[i]);
        }
        else if (isCloseBracket(str[i])) {
            if (isEmpty(&s)) {  // 추가
                printf("올바르지 않은 괄호입니다.");
                return 0;
            }
            if (str[i] == getPairBracket(peek(&s))) {
                pop(&s);
            }
            else {
                printf("올바르지 않은 괄호입니다.");
                return 0;
            }
        }
    }

    if (!isEmpty(&s)) {
        printf("올바르지 않은 괄호입니다.");
    }
    else {
        printf("괄호가 올바르게 사용되었습니다.");
    }
}
