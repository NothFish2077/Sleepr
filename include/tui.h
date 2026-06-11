#ifndef TUI_H
#define TUI_H

typedef struct {
    int row;
    int col;
    int width;
    int height;
} Rect;

void tui_calculate_layout(void);

Rect tui_logo_rect(void);
Rect tui_menu_rect(void);
Rect tui_status_rect(void);

void tui_clear_rect(Rect rect);

#endif
