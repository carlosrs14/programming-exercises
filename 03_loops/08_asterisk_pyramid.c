#include <stdio.h>

int main() {
    int n;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }

        for (int j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }
        
        printf("\n");
    }

    return 0;
}
