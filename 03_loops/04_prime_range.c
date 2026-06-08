#include <stdio.h>

int main() {
    int n, prime;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    for (int i = 2; i <= n; i++) {
        prime = 1;

        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                prime = 0;
                break;
            }
        }
        
        if (prime) {
            printf("[%d]", i);
        }
    }

    printf("\n");
    
    return 0;
}
