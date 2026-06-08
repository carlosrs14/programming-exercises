#include <stdio.h>

long long factorial(int n) {
    long long f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

long long combination(int n, int k) {
    if (k < 0 || k > n || n < 0) return -1;
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int n, k;

    printf("combination n,k: ");
    
    if (scanf("%d,%d", &n, &k) != 2) {
        perror("invalid format n,k");
        return 1;
    }
    
    printf("%lld\n", combination(n, k));

    return 0;
}
