#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("n: ");
    scanf("%d", &n);
    
    if (n < 0) {
        perror("invalid number");
        return 1;
    }

    int* arr = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("idx%d: ", i);
        scanf("%d", arr + i);
    }

    int sum = 0;
    int *p = arr;
    
    for (int i = 0; i < n; i++) {
        sum += *p;
        p++;
    }
    
    printf("sum: %d\n", sum);
    
    free(arr);
    
    return 0;
}
