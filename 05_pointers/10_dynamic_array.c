#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;

    printf("n: ");
    scanf("%d", &n);
    printf("m: ");
    scanf("%d", &m);

    if (n < 0) {
        perror("invalid number n");
        return 1;
    }

    int* arr = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        *(arr + i) = (i + 1) * m;
    }
    
    for (int i = 0; i < n; i++) {
        printf("[%d]", *(arr + i));
    }
    printf("\n");
    
    free(arr);
    
    return 0;
}
