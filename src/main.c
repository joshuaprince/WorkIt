#include <pebble.h>
#include "main.h"
#include "win_splash.h"
#include "win_main.h"
#include "win_milestone.h"



static Window *windows[5];

void goToWindow(int window, int arg)
{
  if (window >= WINDOW_COUNT)
  {
    APP_LOG(APP_LOG_LEVEL_ERROR, "%d is not a valid window", window);
    return;
  }

  switch (window){
    case W_SPLASH: show_win_splash(); break;
    case W_MAIN: show_win_main(); break;
    case W_MILESTONE: show_win_milestone(arg); break;
    }
}

void handle_init(void)
{
 // goToWindow(W_SPLASH);
  
  initFoods();
  show_win_splash();
  
  
  //goToWindow(W_MAIN);
  
  //window_stack_push(windows[0], true);
}

void handle_deinit(void)
{
  for (int i = 0 ; i < WINDOW_COUNT ; i++)
    window_destroy(windows[i]);
}

int main(void)
{
  for (int i = 0 ; i < WINDOW_COUNT ; i++)
    windows[i] = null;
  
  handle_init();
  app_event_loop();
  handle_deinit();
}
