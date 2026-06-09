#include <stdio.h>

int length(char* str) {
    char *p = str;
    while (*p != '\0') {
        p++;
    }
    return (int)(p - str);
}

int main() {
    char str[101];

    printf("str: ");
    scanf("%100s", str);

    printf("%d\n", length(str));
    
    return 0;
}
