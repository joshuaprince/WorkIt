#include <pebble.h>
#include "win_splash.h"
#include "main.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 0);
  #endif
  window_set_background_color(s_window, GColorCyan);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(10, 7, 126, 124));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "ARE YOU READY TO WORK IT?");
  text_layer_set_font(s_textlayer_1, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE

static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
  // This code will run whenever the select button is pressed on the Splash screen page
  goToWindow(W_MAIN, -1);
}

static void click_config_provider(void *context)
{
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_win_splash(void) {
  initialise_ui();
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  text_layer_set_text_color(s_textlayer_1, GColorWhite);
  window_stack_push(s_window, true);
  
  window_set_click_config_provider(s_window, click_config_provider);
}

void hide_win_splash(void) {
  window_stack_remove(s_window, true);
}
