#include <stdio.h>

int main() {
    int n;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    if (n < 0) {
        perror("invalid number");
        return 1;
    }

    long long fact = 1;

    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    
    printf("%lld\n", fact);

    return 0;
}
