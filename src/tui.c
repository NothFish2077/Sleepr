#include "../include/tui.h"
#include "../include/terminal.h"

#include <stdio.h>

static Rect logo_rect;
static Rect menu_rect;
static Rect status_rect;

void tui_calculate_layout(void)
{
    int rows;
    int cols;

    terminal_get_size(&rows, &cols);

    const int ui_width = 60;
    const int ui_height = 22;

    int top  = (rows - ui_height) / 2;
    int left = (cols - ui_width) / 2;

    if (top < 0)
        top = 0;
    if (left < 0)
        left = 0;

    logo_rect = (Rect) {
        .row = top,
        .col = left,
        .width = ui_width,
        .height = 8
    };

    menu_rect = (Rect) {
        .row = top + 10,
        .col = left,
        .width = ui_width,
        .height = 8
    };

    status_rect = (Rect) {
        .row = top + 19,
        .col = left,
        .width = ui_width,
        .height = 3
    };
}

Rect tui_logo_rect(void)
{
    return logo_rect;
}

Rect tui_menu_rect(void)
{
    return menu_rect;
}

Rect tui_status_rect(void)
{
    return status_rect;
}

void tui_clear_rect(Rect rect)
{
    for (int i = 0; i < rect.height; i++) {
        terminal_move_cursor(
            rect.row + i,
            rect.col
        );

        for (int j = 0; j < rect.width; j++)
            putchar(' ');
    }

    fflush(stdout);
}
