#include <stdio.h>

int main() {
    int nota;
    
    printf("grade: ");

    if (scanf("%d", &nota) != 1) {
        perror("invalid format");    
    }

    if (nota < 0 || nota > 100) {
        printf("invalid grade\n");
    } else if (nota >= 90) {
        printf("A\n");
    } else if (nota >= 80) {
        printf("B\n");
    } else if (nota >= 70) {
        printf("C\n");
    } else if (nota >= 60) {
        printf("D\n");
    } else {
        printf("F\n");
    }
    
    return 0;
}
