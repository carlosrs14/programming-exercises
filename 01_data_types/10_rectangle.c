#include <stdio.h>

int main() {
    float b, h;
    
    printf("base: ");
    scanf("%f", &b);
    printf("heigth: ");
    scanf("%f", &h);

    printf("area: %.2f\n", b * h);
    printf("perimeter: %.2f\n", 2.0f * (b + h));

    return 0;
}
