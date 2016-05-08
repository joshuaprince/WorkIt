#include <pebble.h>

#define null (0)

#define WINDOW_COUNT (5)


#define W_SPLASH (0)
#define W_MAIN (1)
#define W_MILESTONE (2)
#define W_END (3)
#define W_REPORT (4)

void goToWindow(int window, int arg);