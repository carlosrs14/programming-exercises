#include <stdio.h>

int main() {
    int n;
    
    printf("n: ");
    
    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    long long a = 0, b = 1;

    for (int i = 0; i < n; i++) {
        printf("[%lld]", a);
    
        long long temp = a + b;
        a = b;
        b = temp;
    }

    printf("\n");
    
    return 0;
}
