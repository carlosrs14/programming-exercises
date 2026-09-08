#include <stdio.h>

typedef enum {
    LIGHT_RED,
    LIGHT_GREEN,
    LIGHT_YELLOW
} TrafficLight;

TrafficLight next_light(TrafficLight current) {
    switch (current) {
        case LIGHT_RED: return LIGHT_GREEN;
        case LIGHT_GREEN: return LIGHT_YELLOW;
        case LIGHT_YELLOW: return LIGHT_RED;
        default: return LIGHT_RED;
    }
}

const char* light_name(TrafficLight light) {
    switch (light) {
        case LIGHT_RED: return "RED";
        case LIGHT_GREEN: return "GREEN";
        case LIGHT_YELLOW: return "YELLOW";
        default: return "UNKNOWN";
    }
}

int main() {
    int choice;

    printf("enter initial light (0: RED, 1: GREEN, 2: YELLOW): ");
    if (scanf("%d", &choice) != 1) {
        perror("invalid input");
        return 1;
    }

    if (choice < 0 || choice > 2) {
        printf("error: invalid light state\n");
        return 1;
    }

    TrafficLight light = (TrafficLight)choice;
    printf("initial: %s\n", light_name(light));

    for (int i = 1; i <= 3; i++) {
        light = next_light(light);
        printf("step %d: %s\n", i, light_name(light));
    }

    return 0;
}
