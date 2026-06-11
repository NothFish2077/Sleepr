#include "../include/timer.h"

#include <stdio.h>

void timer_format(
    int seconds,
    char *buffer,
    unsigned long size
)
{
    int hours = seconds / 3600;
    int mins  = (seconds % 3600) / 60;
    int secs  = seconds % 60;

    snprintf(
        buffer,
        size,
        "%02d:%02d:%02d",
        hours,
        mins,
        secs
    );
}

int timer_progress(
    int remaining,
    int total
)
{
    if (total == 0)
        return 0;

    return ((total - remaining) * 100) / total;
}
