#include <stdio.h>
#include <stdlib.h>

struct Fraction {
    int num;
    int den;
};

int get_gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    struct Fraction f1, f2;

    printf("enter fraction 1 num/den: ");
    if (scanf("%d/%d", &f1.num, &f1.den) != 2) {
        perror("invalid format");
        return 1;
    }

    printf("enter fraction 2 num/den: ");
    if (scanf("%d/%d", &f2.num, &f2.den) != 2) {
        perror("invalid format");
        return 1;
    }

    if (f1.den == 0 || f2.den == 0) {
        perror("invalid denominator\n");
        return 1;
    }

    struct Fraction res = {f1.num * f2.num, f1.den * f2.den};
    int div = get_gcd(res.num, res.den);
    res.num /= div;
    res.den /= div;
    
    if (res.den < 0) {
        res.num = -res.num;
        res.den = -res.den;
    }
    
    printf("%d/%d\n", res.num, res.den);

    return 0;
}
