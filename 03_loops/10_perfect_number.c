#include <stdio.h>

int main() {
    int n;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    if (n <= 0) {
        printf("not perfect\n");
        return 0;
    }

    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    if (sum == n) {
        printf("perfect\n");
    } else {
        printf("not perfect\n");
    }

    return 0;
}
