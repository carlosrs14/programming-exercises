#include <stdio.h>

int main() {
    float a, b, c;
    
    if (scanf("%f %f %f", &a, &b, &c) != 3) {
        perror("invalid format: n1 n2 n3");
        return 1;
    }

    if (!(a + b > c && a + c > b && b + c > a)) {
        perror("invalid triangle\n");
        return 1;
    }

    if (a == b && b == c) {
        printf("equilateral\n");
    } else if (a == b || a == c || b == c) {
        printf("isosceles\n");
    } else {
        printf("scalene\n");
    }
    
    return 0;
}
