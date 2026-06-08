#include <stdio.h>
#include <math.h>

int main() {
    float x1, y1, x2, y2;

    printf("a: x,y: ");
    scanf("%f,%f", &x1, &y1);
    printf("b: x,y: ");
    scanf("%f,%f", &x2, &y2);

    
    float h = sqrtf(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    printf("distance: %.4f\n", h);
    
    return 0;
}
