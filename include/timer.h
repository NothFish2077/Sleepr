#ifndef TIMER_H
#define TIMER_H

#include <stddef.h>

void timer_format(
    int seconds,
    char *buffer,
    size_t size
);

int timer_progress(
    int remaining,
    int total
);

#endif
