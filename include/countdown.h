#ifndef COUNTDOWN_H
#define COUNTDOWN_H

typedef enum {
    COUNTDOWN_FINISHED,
    COUNTDOWN_CANCELLED
} CountdownResult;

CountdownResult countdown_run(int seconds);

#endif
