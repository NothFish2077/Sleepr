#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../include/terminal.h"
#include "../include/tui.h"
#include "../include/menu.h"
#include "../include/logo.h"
#include "../include/countdown.h"

int main(void)
{
    srand((unsigned)time(NULL));

    terminal_init();

    terminal_clear();

    tui_calculate_layout();

    logo_glitch();

    sleep(1);

    int seconds = menu_run();

    if (seconds > 0) {

        CountdownResult result =
            countdown_run(seconds);

        terminal_restore();

        if (result ==
            COUNTDOWN_FINISHED)
        {
            system(
                "systemctl suspend"
            );
        }

        return EXIT_SUCCESS;
    }

    terminal_restore();

    return EXIT_SUCCESS;
}
