#include <stdio.h>

int main() {
    float usd;

    printf("USD: ");

    if (scanf("%f", &usd) != 1) {
        perror("invalid format");
        return 1;
    }

    printf("EUR: %.2f\n", usd * 0.92f);
    printf("COP: %.2f\n", usd * 3606);
    
    return 0;
}
