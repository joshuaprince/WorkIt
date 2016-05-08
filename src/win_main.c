
#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "win_main.h"
#include "win_milestone.h"

static Window *s_window;
static GFont s_res_gothic_24;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static TextLayer *s_textlayer_3;
static Layer *s_barlayer;
static BitmapLayer *s_bitmaplayer_2;
static BitmapLayer *s_bitmaplayer_3;

// Data
static int lower_bound = 0, upper_bound = 15, calval = 0;
static int drawHeight = 0;
static GRect bar_bds;
static char s_lower_bound[5], s_upper_bound[5]/*, s_bar_count[5]*/;


time_t end;
//const time_t start = time(NULL);
const time_t start;
int steps2 = 0;
int steps_initial;



void bounds_and_bar(int lower, int upper, int value){/*
  int temp_upper = upper - lower;
  int temp_input = bar_percent - lower;
  int percent = ((double)temp_input/temp_upper)*100;
  int bit_count = (int) percent * .9;
  *bar_count = bit_count;
  
  snprintf(lower_bound, 4, "%d", lower);
  snprintf(upper_bound, 4, "%d", upper);*/
  
  if (lower >= 0)
  {
    lower_bound = lower;
    snprintf(s_lower_bound, 4, "%d", lower);
  }
  
  if (upper >= 0)
  {
    upper_bound = upper;
    snprintf(s_upper_bound, 4, "%d", upper);
  }
  
  if (value >= 0)
    calval = value;
  
  drawHeight = ((float)(calval-lower_bound))/(upper_bound-lower_bound) * 97.0;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "updating: drawheight [%d]", drawHeight);
    
  bar_bds.origin.y = (147-drawHeight);
  
  if(lower_bound == 0)
    bar_bds.size.h = drawHeight;
  else
    bar_bds.size.h = drawHeight + 30;
  
  layer_mark_dirty(s_barlayer);
}


static void bar_update_proc(Layer *layer, GContext *ctx) 
{
  // Custom drawing happens here!
  APP_LOG(APP_LOG_LEVEL_WARNING, "drawing window: drawHeight = [%d], bound y=[%d] h=[%d]", drawHeight, bar_bds.origin.y, bar_bds.size.h);
  graphics_context_set_fill_color(ctx, GColorCyan);
  graphics_fill_rect(ctx, bar_bds, false, false);
  //layer_set_bounds((Layer*)s_bitmaplayer_1, GRect(100, (140-drawHeight), 14, drawHeight));
}


static void initialise_ui(void) {
  s_window = window_create();
  steps_initial = (int)health_service_sum_today(HealthMetricActiveKCalories);
 // time_t start = time(NULL);
  
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  
  // s_textlayer_1 - "Calories"
  s_textlayer_1 = text_layer_create(GRect(0, 0, 144, 30));
  text_layer_set_background_color(s_textlayer_1, GColorSpringBud);
  text_layer_set_text(s_textlayer_1, "Calories");
  text_layer_set_font(s_textlayer_1, s_res_gothic_24);
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2 - upper label
  s_textlayer_2 = text_layer_create(GRect(76, 40, 32, 20));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, s_upper_bound);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3 - lower label
  s_textlayer_3 = text_layer_create(GRect(76, 137, 32, 20));
  text_layer_set_background_color(s_textlayer_3, GColorClear);
  text_layer_set_text(s_textlayer_3, s_lower_bound);
  //text_layer_set_font(s_textlayer_3, FONT);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // s_barlayer - the bar
  bar_bds = GRect(105, (147-drawHeight), 14, drawHeight+1);
  s_barlayer = layer_create(layer_get_bounds(window_get_root_layer(s_window)));
  //layer_set_background_color(s_barlayer, GColorBlack);
  
  layer_set_update_proc(s_barlayer, bar_update_proc);
  layer_add_child(window_get_root_layer(s_window), s_barlayer);
  
  
  // s_bitmaplayer_2 - upper line
  s_bitmaplayer_2 = bitmap_layer_create(GRect(95, 50, 35, 1));
  bitmap_layer_set_background_color(s_bitmaplayer_2, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_2);
  
  // s_bitmaplayer_3 - lower line
  s_bitmaplayer_3 = bitmap_layer_create(GRect(95, 147, 35, 1));
  bitmap_layer_set_background_color(s_bitmaplayer_3, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_3);
  
  
  
}

//static void health_handler(HealthEventType event, void* context)
//{
  ////if (event != HealthEventMovementUpdate) return;
  //switch(event) {
    //case HealthEventSignificantUpdate:
      //APP_LOG(APP_LOG_LEVEL_INFO, 
        //      "New HealthService HealthEventSignificantUpdate event");
      //break;
    //case HealthEventMovementUpdate:
      //APP_LOG(APP_LOG_LEVEL_INFO, 
        //      "New HealthService HealthEventMovementUpdate event");
      //break;
    //case HealthEventSleepUpdate:
      //APP_LOG(APP_LOG_LEVEL_INFO, 
        //      "New HealthService HealthEventSleepUpdate event");
      //break;
  //}
//}

void addCal(int calories);

void loop(void* data)
{
  
  time_t end = time(NULL); 
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(HealthMetricActiveKCalories, start, end);
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Looping: Mask = [%x]", mask);
  ;
  
  //health_handler(HealthEventMovementUpdate);
  if (mask & HealthServiceAccessibilityMaskAvailable)
  //if (health_service_events_subscribe(health_handler, NULL))
  {
    
    steps2 = (int)health_service_sum_today(HealthMetricActiveKCalories);
    if (steps2 > steps_initial)
    {
      APP_LOG(APP_LOG_LEVEL_INFO, "Steps initial %d", steps_initial);
      APP_LOG(APP_LOG_LEVEL_INFO, "steps2 %d", steps2);
      
      for(int i = 0; i < (steps2 - steps_initial); i++){
        addCal(1);
      }
      steps_initial = steps2;
    }
  }
  
 app_timer_register(2500, loop, NULL);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
  // This code will run whenever the select button is pressed on the Splash screen page
  addCal(5);
}

static void click_config_provider(void *context)
{
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}



  // Make a timestamp for now
//time_t start = time(NULL);

// Make a timestamp for the last hour's worth of data
//time_t start = end - SECONDS_PER_MINUTE;

// Check data is available
//HealthServiceAccessibilityMask result = 
  //  health_service_metric_accessible(HealthMetricActiveKCalories, start, end);
//if(result & HealthServiceAccessibilityMaskAvailable) {
  // Data is available! Read it
  //HealthValue cal = health_service_sum(HealthMetricActiveKCalories, start, end);

  //addCal((int) cal);
// else {
  //APP_LOG(APP_LOG_LEVEL_ERROR, "No data available!");
//}
  
  /*
    int steps = 0;
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(HealthMetricStepCount, start, end);
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Looping: Mask = [%x]", mask);
  
  if (mask & HealthServiceAccessibilityMaskAvailable)
  {
    steps = (int)(health_service_sum(HealthMetricStepCount, start, end));
    APP_LOG(APP_LOG_LEVEL_INFO, "Mask available, steps = [%d]", steps);
    addCal(steps);
  }*/
  
//}



static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  layer_destroy(s_barlayer);
  bitmap_layer_destroy(s_bitmaplayer_2);
}
// END AUTO-GENERATED UI CODE


static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_win_main(void) {
  initialise_ui();
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  bounds_and_bar(0, 25, 0);
  
  window_set_click_config_provider(s_window, click_config_provider);
  
  window_stack_push(s_window, true);
  
  //app_timer_register(1, loop, NULL);
  loop(NULL);
  //if(!health_service_events_subscribe(health_handler, NULL)) {
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
}
//}

void hide_win_main(void) {
  window_stack_remove(s_window, true);
}

void addCal(int calories)
{
  if (calval + calories >= upper_bound + 5)
  {
    // time to update the bounds
    for (int i = 0 ; i < NUM_PICS ; i++)
    {
      APP_LOG(APP_LOG_LEVEL_INFO, "cal[%d] upper[%d] lower[%d]", getPictures()[i].calories, upper_bound, lower_bound);
      
      if (getPictures()[i].calories <= upper_bound && getPictures()[i].calories > lower_bound)
      {
        goToWindow(W_MILESTONE, i);
        break;
      }
    }
    bounds_and_bar(lower_bound + 25, upper_bound + 25, calval + calories);
  }
  else
    bounds_and_bar(-1, -1, calval + calories);
}



#ifdef oldcode /////////////////////////////////////////////////////////////////////////////

#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "win_main.h"
#include "win_milestone.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_24;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static TextLayer *s_textlayer_3;
static Layer *s_barlayer;
static BitmapLayer *s_bitmaplayer_2;
static BitmapLayer *s_bitmaplayer_3;

// Data
static int lower_bound = 0, upper_bound = 15, calval = 0;
static int drawHeight = 0;
static GRect bar_bds;
static char s_lower_bound[5], s_upper_bound[5]/*, s_bar_count[5]*/;


time_t end;
//const time_t start = time(NULL);
const time_t start;



void bounds_and_bar(int lower, int upper, int value){/*
  int temp_upper = upper - lower;
  int temp_input = bar_percent - lower;
  int percent = ((double)temp_input/temp_upper)*100;
  int bit_count = (int) percent * .9;
  *bar_count = bit_count;
  
  snprintf(lower_bound, 4, "%d", lower);
  snprintf(upper_bound, 4, "%d", upper);*/
  
  if (lower >= 0)
  {
    lower_bound = lower;
    snprintf(s_lower_bound, 4, "%d", lower);
  }
  
  if (upper >= 0)
  {
    upper_bound = upper;
    snprintf(s_upper_bound, 4, "%d", upper);
  }
  
  if (value >= 0)
    calval = value;
  
  drawHeight = ((float)(calval-lower_bound))/(upper_bound-lower_bound) * 97.0;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "updating: drawheight [%d]", drawHeight);
    
  bar_bds.origin.y = (147-drawHeight);
  
  if(lower_bound == 0)
    bar_bds.size.h = drawHeight;
  else
    bar_bds.size.h = drawHeight + 30;
  
  layer_mark_dirty(s_barlayer);
}


static void bar_update_proc(Layer *layer, GContext *ctx) 
{
  // Custom drawing happens here!
  APP_LOG(APP_LOG_LEVEL_WARNING, "drawing window: drawHeight = [%d], bound y=[%d] h=[%d]", drawHeight, bar_bds.origin.y, bar_bds.size.h);
  graphics_context_set_fill_color(ctx, GColorCyan);
  graphics_fill_rect(ctx, bar_bds, false, false);
  //layer_set_bounds((Layer*)s_bitmaplayer_1, GRect(100, (140-drawHeight), 14, drawHeight));
}


static void initialise_ui(void) {
  s_window = window_create();
  //time_t start = time(NULL);
  
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  
  // s_textlayer_1 - "Calories"
  s_textlayer_1 = text_layer_create(GRect(0, 0, 144, 30));
  text_layer_set_background_color(s_textlayer_1, GColorSpringBud);
  text_layer_set_text(s_textlayer_1, "Calories");
  text_layer_set_font(s_textlayer_1, s_res_gothic_24);
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2 - upper label
  s_textlayer_2 = text_layer_create(GRect(76, 40, 32, 20));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, s_upper_bound);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3 - lower label
  s_textlayer_3 = text_layer_create(GRect(76, 137, 32, 20));
  text_layer_set_background_color(s_textlayer_3, GColorClear);
  text_layer_set_text(s_textlayer_3, s_lower_bound);
  //text_layer_set_font(s_textlayer_3, FONT);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // s_barlayer - the bar
  bar_bds = GRect(105, (147-drawHeight), 14, drawHeight+1);
  s_barlayer = layer_create(layer_get_bounds(window_get_root_layer(s_window)));
  //layer_set_background_color(s_barlayer, GColorBlack);
  
  layer_set_update_proc(s_barlayer, bar_update_proc);
  layer_add_child(window_get_root_layer(s_window), s_barlayer);
  
  
  // s_bitmaplayer_2 - upper line
  s_bitmaplayer_2 = bitmap_layer_create(GRect(95, 50, 35, 1));
  bitmap_layer_set_background_color(s_bitmaplayer_2, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_2);
  
  // s_bitmaplayer_3 - lower line
  s_bitmaplayer_3 = bitmap_layer_create(GRect(95, 147, 35, 1));
  bitmap_layer_set_background_color(s_bitmaplayer_3, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_3);
  
  
  
}

static void health_handler(HealthEventType event, void* context)
{
  //if (event != HealthEventMovementUpdate) return;
  switch(event) {
    case HealthEventSignificantUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSignificantUpdate event");
      break;
    case HealthEventMovementUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventMovementUpdate event");
      break;
    case HealthEventSleepUpdate:
      APP_LOG(APP_LOG_LEVEL_INFO, 
              "New HealthService HealthEventSleepUpdate event");
      break;
  }
}

void addCal(int calories);

void loop(void* data)
{
  
  //time_t end = time(NULL);
  int steps = 0;
  //HealthServiceAccessibilityMask mask = health_service_metric_accessible(HealthMetricStepCount, start, end);
  
  //APP_LOG(APP_LOG_LEVEL_INFO, "Looping: Mask = [%x]", mask);
  
  //health_handler(HealthEventMovementUpdate);
  //if (mask & HealthServiceAccessibilityMaskAvailable)
  if (health_service_events_subscribe(health_handler, NULL))
  {
    //steps = (int)(health_service_sum(HealthMetricStepCount, start, end));
    steps = 1;
    APP_LOG(APP_LOG_LEVEL_INFO, "Mask available, steps = [%d]", steps);
    addCal(steps);
  }
  
 app_timer_register(5000, loop, NULL);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
  // This code will run whenever the select button is pressed on the Splash screen page
  addCal(1);
}

static void click_config_provider(void *context)
{
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}



  // Make a timestamp for now
//time_t start = time(NULL);

// Make a timestamp for the last hour's worth of data
//time_t start = end - SECONDS_PER_MINUTE;

// Check data is available
//HealthServiceAccessibilityMask result = 
  //  health_service_metric_accessible(HealthMetricActiveKCalories, start, end);
//if(result & HealthServiceAccessibilityMaskAvailable) {
  // Data is available! Read it
  //HealthValue cal = health_service_sum(HealthMetricActiveKCalories, start, end);

  //addCal((int) cal);
// else {
  //APP_LOG(APP_LOG_LEVEL_ERROR, "No data available!");
//}
  
  /*
    int steps = 0;
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(HealthMetricStepCount, start, end);
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Looping: Mask = [%x]", mask);
  
  if (mask & HealthServiceAccessibilityMaskAvailable)
  {
    steps = (int)(health_service_sum(HealthMetricStepCount, start, end));
    APP_LOG(APP_LOG_LEVEL_INFO, "Mask available, steps = [%d]", steps);
    addCal(steps);
  }*/
  
//}



static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  layer_destroy(s_barlayer);
  bitmap_layer_destroy(s_bitmaplayer_2);
}
// END AUTO-GENERATED UI CODE


static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_win_main(void) {
  initialise_ui();
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  bounds_and_bar(0, 25, 0);
  
  window_set_click_config_provider(s_window, click_config_provider);
  
  window_stack_push(s_window, true);
  
  app_timer_register(1, loop, NULL);
  //if(!health_service_events_subscribe(health_handler, NULL)) {
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
}
//}

void hide_win_main(void) {
  window_stack_remove(s_window, true);
}

void addCal(int calories)
{
  if (calval + calories >= upper_bound + 5)
  {
    // time to update the bounds
    for (int i = 0 ; i < NUM_PICS ; i++)
    {
      APP_LOG(APP_LOG_LEVEL_INFO, "cal[%d] upper[%d] lower[%d]", getPictures()[i].calories, upper_bound, lower_bound);
      
      if (getPictures()[i].calories <= upper_bound && getPictures()[i].calories > lower_bound)
      {
        goToWindow(W_MILESTONE, i);
        break;
      }
    }
      
    bounds_and_bar(lower_bound + 25, upper_bound + 25, calval + calories);
  }
  else
    bounds_and_bar(-1, -1, calval + calories);
  
 
}

#endif