#include <stdio.h>

int main() {
    int n;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    int sign = (n < 0) ? -1 : 1;
    
    if (n < 0) n = -n;

    int rev = 0;

    while (n > 0) {
        rev = rev * 10 + (n % 10);
        n /= 10;
    }
    
    printf("%d\n", sign * rev);
    
    return 0;
}
