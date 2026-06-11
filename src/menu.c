#include "../include/menu.h"

#include "../include/terminal.h"
#include "../include/tui.h"

#include <stdio.h>

typedef struct {
    const char *label;
    int seconds;
} MenuItem;

static const MenuItem ITEMS[] = {
    { "5 minutos", 5 * 60 },
    { "10 minutos", 10 * 60 },
    { "15 minutos", 15 * 60 },
    { "30 minutos", 30 * 60 },
    { "1 hora", 60 * 60 },
    { "Personalizado", -1 }
};

static const int ITEM_COUNT =
    sizeof(ITEMS) / sizeof(ITEMS[0]);

static void draw_menu(int selected)
{
    Rect rect = tui_menu_rect();

    tui_clear_rect(rect);

    int title_col =
        rect.col + (rect.width - 18) / 2;

    terminal_move_cursor(rect.row, title_col);

    printf("Escolha o tempo");

    for (int i = 0; i < ITEM_COUNT; i++) {

        int row = rect.row + 2 + i;

        int col =
            rect.col +
            (rect.width - 24) / 2;

        terminal_move_cursor(row, col);

        if (i == selected)
            printf("> %-20s", ITEMS[i].label);
        else
            printf("  %-20s", ITEMS[i].label);
    }

    terminal_move_cursor(
        rect.row + rect.height - 1,
        rect.col + (rect.width - 40) / 2
    );

    printf("↑↓ Navegar  Enter Confirmar  q Sair");

    fflush(stdout);
}

static int custom_time(void)
{
    terminal_restore();

    int minutes;

    printf("\n\nMinutos: ");

    if (scanf("%d", &minutes) != 1) {
        terminal_init();
        return -1;
    }

    terminal_init();

    if (minutes <= 0)
        return -1;

    return minutes * 60;
}

int menu_run(void)
{
    int selected = 0;

    draw_menu(selected);

    while (1) {

        Key key = terminal_read_key();

        switch (key) {

            case KEY_UP:

                selected--;

                if (selected < 0)
                    selected = ITEM_COUNT - 1;

                draw_menu(selected);

                break;

            case KEY_DOWN:

                selected++;

                if (selected >= ITEM_COUNT)
                    selected = 0;

                draw_menu(selected);

                break;

            case KEY_ENTER:

                if (ITEMS[selected].seconds > 0)
                    return ITEMS[selected].seconds;

                return custom_time();

            case KEY_Q:

                return -1;

            default:
                break;
        }
    }
}
