#include <stdio.h>

void concat(char *dest, char *src) {
    while (*dest != '\0') {
        dest++;
    }
    while ((*dest++ = *src++));
}

int main() {
    char s1[201];
    char s2[101];

    printf("str1: ");
    scanf("%100s", s1);
    printf("str2: ");
    scanf("%100s", s2);

    concat(s1, s2);

    printf("%s\n", s1);

    return 0;
}
