#include <stdio.h>
#include <stdlib.h>

void min_max(int* arr, int n, int* min, int* max) {
    *min = *arr;
    *max = *arr;

    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = *(arr + i);
        if (arr[i] > *max) *max = *(arr + i);
    }
}

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
    
    int min, max;
    min_max(arr, n, &min, &max);
    printf("min: %d\nmax: %d\n", min, max);
    
    free(arr);
    
    return 0;
}
