#include <stdio.h>

int is_bisiest(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int main() {
    int a, b;
    
    printf("year1-year2: ");

    if (scanf("%d-%d", &a, &b) != 2) {
        perror("format year1-year2");
        return 1;
    }

    int min = (a < b) ? a : b;
    int max = (a < b) ? b : a;
    int count = 0;

    for (int i = min; i <= max; i++) {
        if (is_bisiest(i)) count++;
    }

    printf("%d\n", count);
    
    return 0;
}
