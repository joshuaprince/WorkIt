#include <pebble.h>
#include "win_milestone.h"
#include <string.h>

 

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18;
static GBitmap *s_res_image_hamburger;
static GFont s_res_gothic_18_bold;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *s_textlayer_3;

static pictures pics[NUM_PICS];
int num_food = 0;

pictures* getPictures()
{
  return pics;
}


void initFoods()
{
  strcpy(pics[0].name, "A hamburger!");
  pics[0].calories = 350;
  strcpy(pics[1].name, "An apple!");
  pics[1].calories = 50;
  strcpy(pics[2].name, "Ice Cream!");
  pics[2].calories = 375;
  strcpy(pics[3].name, "A slice of Pizza!");
  pics[3].calories = 620;
  strcpy(pics[4].name, "5 M&Ms!");
  pics[4].calories = 25;
  strcpy(pics[5].name, "A banana!");
  pics[5].calories = 100;
  strcpy(pics[6].name, "A popsicle!");
  pics[6].calories = 75;
}


static void initialise_ui(void) {
  s_window = window_create();  
  
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  
  pics[0].img = gbitmap_create_with_resource(RESOURCE_ID_hamburger);
  pics[1].img = gbitmap_create_with_resource(RESOURCE_ID_apple);
  pics[2].img = gbitmap_create_with_resource(RESOURCE_ID_ice_cream);
  pics[3].img = gbitmap_create_with_resource(RESOURCE_ID_pizza);
  pics[4].img = gbitmap_create_with_resource(RESOURCE_ID_mm);
  pics[5].img = gbitmap_create_with_resource(RESOURCE_ID_banana);
  pics[6].img = gbitmap_create_with_resource(RESOURCE_ID_popsicle);

  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(36, 9, 72, 30));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "Congrats!");
  text_layer_set_font(s_textlayer_1, s_res_gothic_18_bold);
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(36, 31, 72, 44));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_font(s_textlayer_2, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(s_textlayer_2, "You just burned:");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_2, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(54, 75, 34, 35));
  bitmap_layer_set_bitmap(s_bitmaplayer_1, pics[num_food].img);
  bitmap_layer_set_compositing_mode(s_bitmaplayer_1, GCompOpSet);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(5, 117, 134, 20));
  text_layer_set_text(s_textlayer_3, pics[num_food].name);
  text_layer_set_text_alignment(s_textlayer_3, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_3, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(s_textlayer_3);
  gbitmap_destroy(s_res_image_hamburger);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void disappear(void* data)
{
  if (window_stack_get_top_window() == s_window)
    window_stack_pop(true);
}

void show_win_milestone(int foodid) {
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Spawning Milestone %d", foodid);
  
  num_food = foodid;
  
  vibes_long_pulse();
  
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  window_stack_push(s_window, true);
  
  app_timer_register(10000, disappear, NULL);
}

void hide_win_milestone(void) {
  window_stack_remove(s_window, true);
}

