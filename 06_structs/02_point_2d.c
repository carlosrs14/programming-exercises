#include <stdio.h>
#include <math.h>

struct Point {
    float x;
    float y;
};

int main() {
    struct Point p1, p2;

    printf("enter p1 x,y: ");
    if (scanf("%f,%f", &p1.x, &p1.y) != 2) {
        perror("invalid format x,y");
        return 1;
    }

    printf("enter p2 x,y: ");
    if (scanf("%f,%f", &p2.x, &p2.y) != 2) {
        perror("invalid format x,y");
        return 1;
    }

    float d = sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

    printf("distance: %.2f\n", d);

    return 0;
}
