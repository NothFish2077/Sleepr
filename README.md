# sleepr

A terminal-based sleep timer that puts your system to sleep after a configurable countdown. Features a TUI with ASCII art logo, glitch animation, and progress bar.

## Features

- **Interactive TUI menu** - Navigate with arrow keys, select with Enter
- **Preset durations** - 5 min, 10 min, 15 min, 30 min, 1 hour
- **Custom duration** - Enter any number of minutes
- **Glitch animation** - ASCII art logo with visual glitch effect on startup
- **Live countdown** - Progress bar, remaining time, current time, and suspension time
- **Cancellation** - Press `q` anytime to cancel

## Build

```bash
make              # Release build (default)
make debug        # Debug build with symbols
make clean        # Clean build artifacts
```

## Install

```bash
make install      # Installs to /usr/local/bin/sleepr
make uninstall    # Removes from /usr/local/bin
```

## Usage

```bash
sleepr
```

### Controls

| Key | Action |
|-----|--------|
| `↑` / `↓` | Navigate menu |
| `Enter` | Confirm selection |
| `q` | Quit / Cancel countdown |

## Project Structure

```
sleeprv2/
├── include/
│   ├── countdown.h   # Countdown timer interface
│   ├── logo.h        # ASCII art logo interface
│   ├── menu.h        # Menu interface
│   ├── terminal.h    # Terminal manipulation
│   ├── timer.h       # Time formatting utilities
│   └── tui.h         # TUI layout system
├── src/
│   ├── countdown.c   # Countdown with progress bar
│   ├── logo.c        # ASCII art + glitch animation
│   ├── main.c        # Entry point
│   ├── menu.c        # Interactive menu
│   ├── terminal.c    # Raw terminal mode, cursor control
│   ├── timer.c       # Time formatting helpers
│   └── tui.c         # Layout calculations
├── build/            # Build output (generated)
└── Makefile
```

## Modules

### terminal
Low-level terminal control: raw mode, cursor visibility, cursor positioning, window size detection, key reading (including arrow keys via escape sequences).

### tui
Layout system using fixed rectangles for logo, menu, and status areas. Centers UI in terminal.

### menu
Interactive menu with 6 options (5 presets + custom). Handles navigation and input.

### logo
ASCII art "SLEEPR" logo (8 lines × 58 cols). Glitch animation: 18 frames with random character corruption and horizontal jitter.

### countdown
Main countdown loop: updates every 0.1s, checks for `q` keypress, displays progress bar with `#` (filled) and `.` (empty), shows current time and scheduled suspension time.

### timer
Utilities: `timer_format()` converts seconds to `HH:MM:SS`, `timer_progress()` computes percentage.

## Requirements

- GCC or Clang (C17)
- POSIX system (Linux, *BSD, macOS)
- `systemctl` for suspend (Linux systemd)

## License

MIT