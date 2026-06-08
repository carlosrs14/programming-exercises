#include <stdio.h>

int main() {
    int n;

    printf("number: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }
    
    if (n == 0) {
        printf("Zero\n");
    } else if (n % 2 == 0) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}
