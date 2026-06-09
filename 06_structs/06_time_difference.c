#include <stdio.h>

struct Time {
    int h;
    int m;
    int s;
};

int to_seconds(struct Time t) {
    return t.h * 3600 + t.m * 60 + t.s;
}

int main() {
    struct Time t1, t2;

    printf("enter time 1 h:m:s: ");
    if (scanf("%d:%d:%d", &t1.h, &t1.m, &t1.s) != 3) {
        perror("invalid format h:m:s");
        return 1;
    }

    printf("enter time 2 h:m:s: ");
    if (scanf("%d:%d:%d", &t2.h, &t2.m, &t2.s) != 3) {
        perror("invalid format h:m:s");
        return 1;
    }

    int diff = to_seconds(t2) - to_seconds(t1);

    if (diff < 0) {
        diff += 24 * 3600;
    }

    int rh = diff / 3600;
    int rm = (diff % 3600) / 60;
    int rs = diff % 60;

    printf("%02d:%02d:%02d\n", rh, rm, rs);

    return 0;
}
