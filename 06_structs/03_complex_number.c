#include <stdio.h>

struct Complex {
    float real;
    float imag;
};

int main() {
    struct Complex c1, c2;

    printf("enter c1 real,imag: ");

    if (scanf("%f,%f", &c1.real, &c1.imag) != 2) {
        perror("invalid format");
        return 1;
    }

    printf("enter c2 real,imag: ");
    if (scanf("%f,%f", &c2.real, &c2.imag) != 2) {
        perror("invalid format");
        return 1;
    }

    struct Complex sum = {c1.real + c2.real, c1.imag + c2.imag};

    printf("%.2f + %.2fi\n", sum.real, sum.imag);

    return 0;
}
