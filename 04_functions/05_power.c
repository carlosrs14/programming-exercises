#include <stdio.h>

double potencia(double base, int exp) {
    double res = 1.0;
    int e = exp < 0 ? -exp : exp;
    for (int i = 0; i < e; i++) {
        res *= base;
    }
    return exp < 0 ? 1.0 / res : res;
}

int main() {
    double base;
    int exp;

    printf("pow b**ex: ");
 
    if (scanf("%lf**%d", &base, &exp) != 2) {
        perror("invalid format");
        return 1;
    }

    printf("%.6f\n", potencia(base, exp));
    
    return 0;
}
