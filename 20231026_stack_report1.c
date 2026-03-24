// 스택은 동적할당은 사용하지 않은 스택으로 최대 크기를 100으로 사용하였습니다.



int main()
{

    Stack s;
    initStack(&s);

    char str[100];

    printf("반전할 문자열을 입력: ");
    scanf("%s", str);
    for (int i = 0; i < strlen(str); i++) {
        //printf("%d", i);
        push(&s, str[i]);
    }
    

    for (int i = 0; i < strlen(str); i++) {
        char a = pop(&s);
        printf("%c", a);
    }

}
