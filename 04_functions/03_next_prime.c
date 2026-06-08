#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n < 2) return false;
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }

    return true;
}

int main() {
    int n;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    int sig = n + 1;

    while (!is_prime(sig)) {
        sig++;
    }

    printf("next prime: %d\n", sig);
    
    return 0;
}
