#include <stdio.h>

int main() {
    int segs;

    printf("Seconds: ");

    if (scanf("%d", &segs) != 1) {
        perror("invalid format");
        return 1;
    }

    int h = segs / 3600;
    int m = (segs % 3600) / 60;
    int s = segs % 60;
    printf("%02d:%02d:%02d\n", h, m, s);

    return 0;
}
