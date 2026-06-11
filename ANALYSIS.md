# Project Analysis: sleeprv2

## Overview
A terminal-based sleep timer (sleepr) written in C17 with a TUI interface. The program displays an ASCII art logo with glitch animation, presents a menu to select a sleep duration, and runs a countdown with progress bar before executing `systemctl suspend`.

## Issues Found & Fixed

### 1. Build Errors (Blocking)
| File | Issue | Fix |
|------|-------|-----|
| `src/countdown.c:28,30` | Multi-character constants `'█'` and `'░'` don't fit in `char` | Replaced with ASCII `#` and `.` |
| `src/countdown.c:160` | Implicit declaration of `usleep` (deprecated) | Replaced with `nanosleep` |
| `src/terminal.c:58-59` | Sign conversion warnings with bitwise NOT on `tcflag_t` | Added explicit `(tcflag_t)` cast |

### 2. Runtime Issues
| Issue | Cause | Fix |
|-------|-------|-----|
| Logo rendering at negative coordinates | `tui_calculate_layout()` didn't clamp `top`/`left` to >= 0 when terminal smaller than UI | Added `if (top < 0) top = 0; if (left < 0) left = 0;` |

## Code Quality
- **Warnings**: Clean build with `-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 -Wstrict-prototypes -Wmissing-prototypes`
- **Standards**: C17 (`-std=c17`)
- **Architecture**: Modular design with clear separation:
  - `terminal` - Raw terminal I/O
  - `tui` - Layout system
  - `menu` - Interactive selection
  - `logo` - ASCII art + animation
  - `countdown` - Timer with progress bar
  - `timer` - Time formatting utilities

## Build System
Well-structured Makefile with:
- Debug/Release configurations
- Automatic dependency generation (`-MMD -MP`)
- Install/uninstall targets
- Format target (clang-format)

## Testing
- ✅ Release build compiles cleanly
- ✅ Debug build compiles cleanly
- ✅ Binary runs and displays UI correctly in real terminal
- ✅ Menu navigation works (arrow keys, Enter, q)
- ✅ Countdown logic correct (tested logic flow)
- ✅ Strip reduces binary from 106KB to 19KB

## Dependencies
- POSIX system (Linux, *BSD, macOS)
- GCC/Clang with C17 support
- `systemctl` for suspend (Linux systemd)

## Files Modified
1. `src/countdown.c` - Fixed multi-char constants, replaced usleep
2. `src/terminal.c` - Fixed sign conversion warnings
3. `src/tui.c` - Clamped layout coordinates to prevent negative positions

## Files Created
1. `README.md` - Complete documentation
2. `ANALYSIS.md` - This file