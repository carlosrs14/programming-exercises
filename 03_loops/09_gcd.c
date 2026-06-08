#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, temp;
    
    printf("n1 n2: ");

    if (scanf("%d %d", &a, &b) != 2) {
        perror("format: n1 n2");
        return 1;
    }

    a = abs(a);
    b = abs(b);
    
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    printf("%d\n", a);
    
    return 0;
}
