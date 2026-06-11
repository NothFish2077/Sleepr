#define _POSIX_C_SOURCE 200809L

#include "../include/countdown.h"

#include "../include/terminal.h"
#include "../include/tui.h"
#include "../include/timer.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>

static void draw_bar(
    int remaining,
    int total,
    int width
)
{
    int filled =
        ((total - remaining) * width) / total;

    putchar('[');

    for (int i = 0; i < width; i++) {

        if (i < filled)
            putchar('#');
        else
            putchar('.');
    }

    putchar(']');
}

static void draw_status(
    int remaining,
    int total,
    time_t suspend_at
)
{
    Rect rect = tui_status_rect();

    tui_clear_rect(rect);

    char time_buffer[16];

    timer_format(
        remaining,
        time_buffer,
        sizeof(time_buffer)
    );

    time_t now = time(NULL);

    struct tm *tm_now =
        localtime(&now);

    struct tm *tm_suspend =
        localtime(&suspend_at);

    int center =
        rect.col + (rect.width / 2);

    terminal_move_cursor(
        rect.row,
        center - 10
    );

    printf(
        "Tempo restante: %s",
        time_buffer
    );

    terminal_move_cursor(
        rect.row + 1,
        center - 12
    );

    printf(
        "Agora: %02d:%02d:%02d",
        tm_now->tm_hour,
        tm_now->tm_min,
        tm_now->tm_sec
    );

    terminal_move_cursor(
        rect.row + 2,
        center - 13
    );

    printf(
        "Suspensão: %02d:%02d:%02d",
        tm_suspend->tm_hour,
        tm_suspend->tm_min,
        tm_suspend->tm_sec
    );

    terminal_move_cursor(
        rect.row + 4,
        center - 15
    );

    draw_bar(
        remaining,
        total,
        30
    );

    terminal_move_cursor(
        rect.row + 6,
        center - 10
    );

    printf(
        "Pressione q para cancelar"
    );

    fflush(stdout);
}

static int key_pressed(void)
{
    fd_set set;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    struct timeval timeout = {
        .tv_sec = 0,
        .tv_usec = 0
    };

    return select(
        STDIN_FILENO + 1,
        &set,
        NULL,
        NULL,
        &timeout
    ) > 0;
}

CountdownResult countdown_run(int seconds)
{
    const int total = seconds;

    time_t suspend_at =
        time(NULL) + seconds;

    while (seconds > 0) {

        draw_status(
            seconds,
            total,
            suspend_at
        );

        for (int i = 0; i < 10; i++) {

            struct timespec ts = { .tv_sec = 0, .tv_nsec = 100000000 };
            nanosleep(&ts, NULL);

            if (key_pressed()) {

                Key key =
                    terminal_read_key();

                if (key == KEY_Q)
                    return COUNTDOWN_CANCELLED;
            }
        }

        seconds--;
    }

    return COUNTDOWN_FINISHED;
}
