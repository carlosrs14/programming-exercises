#include <stdio.h>

int main() {
    int n;

    printf("n: ");

    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }
    
    if (n == 0) {
        printf("1\n");
    } else {

        if (n < 0) n = -n;
        int cont = 0;
    
        while (n > 0) {
            cont++;
            n /= 10;
        }
        printf("%d\n", cont);
    }

    return 0;
}
