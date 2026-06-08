#include <stdio.h>

int main() {
    int a, b;

    printf("A: ");
    scanf("%d", &a);
    printf("B: ");
    scanf("%d", &b);
        
    printf("(A + B): %d\n", a + b);
    printf("(A - B): %d\n", a - b);
    printf("(A * B): %d\n", a * b);

    if (b == 0) {
        perror("Zero divisor");
        return 0;
    }

    printf("(A / B): %d\n", a / b);
    printf("(A %% B): %d\n", a % b);

    return 0;
}
