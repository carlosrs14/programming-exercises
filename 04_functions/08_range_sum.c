#include <stdio.h>

int suma_rango(int a, int b) {
    int min = (a < b) ? a : b;
    int max = (a < b) ? b : a;
    int suma = 0;
    for (int i = min; i <= max; i++) {
        suma += i;
    }
    return suma;
}

int main() {
    int a, b;

    printf("start-end: ");

    if (scanf("%d-%d", &a, &b) == 2) {
        perror("format start-end");
        return 1;
    }
    
    printf("%d\n", suma_rango(a, b));
    
    return 0;
}
