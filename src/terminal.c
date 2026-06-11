#define _POSIX_C_SOURCE 200809L

#include "../include/terminal.h"

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

static struct termios original_termios;

void terminal_hide_cursor(void)
{
    printf("\033[?25l");
    fflush(stdout);
}

void terminal_show_cursor(void)
{
    printf("\033[?25h");
    fflush(stdout);
}

void terminal_clear(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

void terminal_move_cursor(int row, int col)
{
    printf("\033[%d;%dH", row, col);
}

void terminal_get_size(int *rows, int *cols)
{
    struct winsize ws;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    *rows = ws.ws_row;
    *cols = ws.ws_col;
}

void terminal_restore(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);

    terminal_show_cursor();
}

void terminal_init(void)
{
    tcgetattr(STDIN_FILENO, &original_termios);

    struct termios raw = original_termios;

    raw.c_lflag &= (tcflag_t)~(ECHO | ICANON);
    raw.c_iflag &= (tcflag_t)~(IXON | ICRNL);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    terminal_hide_cursor();
}

Key terminal_read_key(void)
{
    char c;

    if (read(STDIN_FILENO, &c, 1) != 1)
        return KEY_NONE;

    if (c == 'q' || c == 'Q')
        return KEY_Q;

    if (c == '\n' || c == '\r')
        return KEY_ENTER;

    if (c != '\033')
        return KEY_OTHER;

    char seq[2];

    if (read(STDIN_FILENO, &seq[0], 1) != 1)
        return KEY_ESCAPE;

    if (read(STDIN_FILENO, &seq[1], 1) != 1)
        return KEY_ESCAPE;

    if (seq[0] != '[')
        return KEY_ESCAPE;

    switch (seq[1]) {
        case 'A': return KEY_UP;
        case 'B': return KEY_DOWN;
        case 'C': return KEY_RIGHT;
        case 'D': return KEY_LEFT;
        default:  return KEY_OTHER;
    }
}
