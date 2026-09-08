#include <stdio.h>

typedef enum {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} DayOfWeek;

const char* get_day_name(DayOfWeek day) {
    switch (day) {
        case MONDAY: return "Monday";
        case TUESDAY: return "Tuesday";
        case WEDNESDAY: return "Wednesday";
        case THURSDAY: return "Thursday";
        case FRIDAY: return "Friday";
        case SATURDAY: return "Saturday";
        case SUNDAY: return "Sunday";
        default: return "Unknown";
    }
}

int is_weekend(DayOfWeek day) {
    return (day == SATURDAY || day == SUNDAY);
}

int main() {
    int day_input;

    printf("enter day number (1-7): ");
    if (scanf("%d", &day_input) != 1) {
        perror("invalid input");
        return 1;
    }

    if (day_input < 1 || day_input > 7) {
        printf("error: day must be between 1 and 7\n");
        return 1;
    }

    DayOfWeek day = (DayOfWeek)day_input;
    printf("Day: %s (%s)\n", get_day_name(day), is_weekend(day) ? "weekend" : "weekday");

    return 0;
}
