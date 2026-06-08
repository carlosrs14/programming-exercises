#include <stdio.h>

void print_binary(unsigned int n) {
    if (n > 1) {
        print_binary(n >> 1);
    }
    printf("%d", n & 1);
}

int main() {
    int n;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }


    if (n < 0) {
        printf("-");
        print_binary((unsigned int)(-n));
    } else if (n == 0) {
        printf("0");
    } else {
        print_binary((unsigned int)n);
    }
    
    printf("\n");

    return 0;
}
