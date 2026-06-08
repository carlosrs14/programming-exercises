#include <stdio.h>

int main() {
    float c;

    printf("celcius: ");

    if (scanf("%f", &c) != 1) {
        perror("invalid format");
        return 1;
    }
    
    printf("fahrenheit: %.2f\n", c * 1.8f + 32.0f);
    
    return 0;
}
