#include <stdio.h>

int main() {
    int a, b;

    if (scanf("%d %d", &a, &b) == 2) {
        a = a + b;
        b = a - b;
        a = a - b;
        printf("%d %d\n", a, b);
    } else {
        perror("format n1 n2");
    }
    
    return 0;
}
