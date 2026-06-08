#include <stdio.h>

int main() {
    float a, b;
    char op;

    printf("enter an operation (ex: a+b): ");

    if (scanf("%f%c%f", &a, &op, &b) != 3) {
        perror("format: a+b");
        return 1;    
    }

    switch(op) {
        case '+': printf("%.2f\n", a + b); break;
        case '-': printf("%.2f\n", a - b); break;
        case '*': printf("%.2f\n", a * b); break;
        case '/':
            if (b != 0.0f) {
                printf("%.2f\n", a / b);
            } else {
                perror("zero divisior\n");
            }
            break;
        default: perror("invalid operation\n"); break;
    }
    
    return 0;
}
