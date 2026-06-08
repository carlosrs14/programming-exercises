#include <stdio.h>

int main() {
    int a, b, c;

    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);
    printf("c: ");
    scanf("%d", &c);

    int mayor = a;
    
    if (b > mayor) mayor = b;
    if (c > mayor) mayor = c;
    
    printf("%d\n", mayor);
    
    return 0;
}
