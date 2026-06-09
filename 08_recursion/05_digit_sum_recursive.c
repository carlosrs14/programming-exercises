#include <stdio.h>
#include <stdlib.h>

int digit_sum_rec(int n) {
    if (n == 0) {
        return 0;
    }
    return (n % 10) + digit_sum_rec(n / 10);
}

int main() {
    int n;

    printf("n: ");
    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    printf("%d\n", digit_sum_rec(abs(n)));

    return 0;
}
