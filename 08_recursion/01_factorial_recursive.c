#include <stdio.h>

long long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
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

    printf("%lld\n", factorial(n));

    return 0;
}
