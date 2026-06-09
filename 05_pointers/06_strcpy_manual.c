#include <stdio.h>

void copy(char* dest, char* src) {
    while ((*dest++ = *src++));
}

int main() {
    char src[101];
    char dest[101];
    
    printf("src: ");
    scanf("%100s", src);

    copy(dest, src);
    printf("dest: %s\n", dest);

    return 0;
}
