#include <stdio.h>

int main() {
    int hours;

    printf("hours: ");

    if (scanf("%d", &hours) != 1) {
        perror("invalid format");
    }

    float total = 0.0f;

    if (hours <= 0) {
        total = 0.0f;
    } else if (hours <= 1) {
        total = 3.0f;
    } else if (hours <= 3) {
        total = 3.0f + (hours - 1) * 2.0f;
    } else {
        total = 3.0f + 2.0f * 2.0f + (hours - 3) * 1.5f;
    }

    printf("%.2f\n", total);
    
    return 0;
}
