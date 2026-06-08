#include <stdio.h>

#define PI 3.14159

int main() {
    float r;

    printf("r: ");
    
    if (scanf("%f", &r) == 1) {
        printf("area: %.2f\n", PI * r * r);
    } else {
        perror("scan error");
        return 1;
    }
    
    return 0;
}
