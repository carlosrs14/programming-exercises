#include <stdio.h>

struct Point {
    float x;
    float y;
};

struct Rectangle {
    struct Point top_left;
    struct Point bottom_right;
};

int main() {
    struct Rectangle r;
    struct Point p;

    printf("enter rectangle top-left x,y: ");
    if (scanf("%f,%f", &r.top_left.x, &r.top_left.y) != 2) {
        perror("invalid format x,y");
        return 1;
    }

    printf("enter rectangle bottom-right x,y: ");
    if (scanf("%f,%f", &r.bottom_right.x, &r.bottom_right.y) != 2) {
        perror("invalid format x,y");
        return 1;
    }

    printf("enter test point x,y: ");
    if (scanf("%f,%f", &p.x, &p.y) != 2) {
        perror("invalid format x,y");
        return 1;
    }

    float width = r.bottom_right.x - r.top_left.x;
    float height = r.top_left.y - r.bottom_right.y;
    float area = width * height;

    if (area < 0) {
        area = -area;
    }

    printf("area: %.2f\n", area);

    printf("point is ");
    if (p.x >= r.top_left.x && p.x <= r.bottom_right.x && p.y >= r.bottom_right.y && p.y <= r.top_left.y) {
        printf("inside\n");
    } else {
        printf("outside\n");
    }

    return 0;
}
