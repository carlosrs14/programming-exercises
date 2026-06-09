#include <stdio.h>

int count = 0;

void hanoi(int n, char origen, char destino, char auxiliar) {
    if (n == 1) {
        count++;
        printf("Move disk 1 from %c to %c\n", origen, destino);
        return;
    }
    hanoi(n - 1, origen, auxiliar, destino);
    count++;
    printf("Move disk %d from %c to %c\n", n, origen, destino);
    hanoi(n - 1, auxiliar, destino, origen);
}

int main() {
    int n;

    printf("n: ");
    if (scanf("%d", &n) != 1) {
        perror("invalid format");
        return 1;
    }

    if (n <= 0) {
        perror("invalid number");
        return 1;
    }

    hanoi(n, 'A', 'C', 'B');
    printf("%d\n", count);

    return 0;
}
