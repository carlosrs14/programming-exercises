#include <stdio.h>

int main() {
    float n1, n2, n3;

    if (scanf("%f %f %f", &n1, &n2, &n3) != 3) {
        perror("format: n1 n2 n3");
        return 1;
    }
    
    printf("media: %.1f\n", (n1 + n2 + n3) / 3.0f);
    
    return 0;
}
