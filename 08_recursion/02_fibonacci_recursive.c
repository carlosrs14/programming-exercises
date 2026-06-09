#include <stdio.h>

long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

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

    printf("%lld\n", fibonacci(n));

    return 0;
}
