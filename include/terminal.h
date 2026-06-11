#ifndef TERMINAL_H
#define TERMINAL_H

typedef enum {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_Q,
    KEY_OTHER
} Key;

void terminal_init(void);
void terminal_restore(void);

void terminal_clear(void);

void terminal_hide_cursor(void);
void terminal_show_cursor(void);

void terminal_move_cursor(int row, int col);

void terminal_get_size(int *rows, int *cols);

Key terminal_read_key(void);

#endif
