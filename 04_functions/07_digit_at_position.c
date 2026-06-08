#include <stdio.h>
#include <stdlib.h>

int digit_pos(int n, int k) {
    n = abs(n);

    if (k <= 0) return -1;
    
    int pos = 1;
    while (n > 0) {
        if (pos == k) return n % 10;
        n /= 10;
        pos++;
    }
    return -1;
}

int main() {
    int n, k;
    
    printf("n: ");
    scanf("%d", &n);
    printf("position: ");
    scanf("%d", &k);
    
    printf("number at %d: %d\n", k, digit_pos(n, k));
    return 0;
}
