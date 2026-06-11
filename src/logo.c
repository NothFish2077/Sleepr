#define _POSIX_C_SOURCE 200809L

#include "../include/logo.h"

#include "../include/terminal.h"
#include "../include/tui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char *ART[] = {
    " ",
    "███████╗██╗     ███████╗███████╗██████╗ ██████╗",
    "██╔════╝██║     ██╔════╝██╔════╝██╔══██╗██╔══██╗",
    "███████╗██║     █████╗  █████╗  ██████╔╝██████╔╝",
    "╚════██║██║     ██╔══╝  ██╔══╝  ██╔═══╝ ██╔══██╗",
    "███████║███████╗███████╗███████╗██║     ██║  ██║",
    "╚══════╝╚══════╝╚══════╝╚══════╝╚═╝     ╚═╝  ╚═╝",
    " "
};

static const int ART_HEIGHT =
    sizeof(ART) / sizeof(ART[0]);

static void sleep_ms(long ms)
{
    struct timespec ts = {
        .tv_sec = ms / 1000,
        .tv_nsec = (ms % 1000) * 1000000L
    };

    nanosleep(&ts, NULL);
}

int logo_height(void)
{
    return ART_HEIGHT;
}

int logo_width(void)
{
    size_t max = 0;

    for (int i = 0; i < ART_HEIGHT; i++) {

        size_t len = strlen(ART[i]);

        if (len > max)
            max = len;
    }

    return (int)max;
}

static void draw_art(char buffer[][256], int offset)
{
    Rect rect = tui_logo_rect();

    for (int i = 0; i < ART_HEIGHT; i++) {

        terminal_move_cursor(
            rect.row + i,
            rect.col + offset
        );

        printf("%s", buffer[i]);
    }

    fflush(stdout);
}

void logo_draw(void)
{
    Rect rect = tui_logo_rect();

    for (int i = 0; i < ART_HEIGHT; i++) {

        terminal_move_cursor(
            rect.row + i,
            rect.col
        );

        printf("%s", ART[i]);
    }

    fflush(stdout);
}

void logo_glitch(void)
{
    char frame[ART_HEIGHT][256];

    for (int f = 0; f < 18; f++) {

        for (int i = 0; i < ART_HEIGHT; i++) {

            strncpy(
                frame[i],
                ART[i],
                sizeof(frame[i]) - 1
            );

            frame[i][255] = '\0';

            if (rand() % 100 < 25) {

                int len =
                    (int)strlen(frame[i]);

                for (int j = 0; j < len / 8; j++) {

                    int pos = rand() % len;

                    if (frame[i][pos] != ' ')
                        frame[i][pos] =
                            "#@%&*"[
                                rand() % 5
                            ];
                }
            }
        }

        int offset = 0;

        if (rand() % 4 == 0)
            offset = (rand() % 3) - 1;

        if (offset < 0)
            offset = 0;

        draw_art(frame, offset);

        sleep_ms(60);
    }

    logo_draw();
}
