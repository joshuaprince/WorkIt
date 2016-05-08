
#include <pebble.h>

#define NUM_PICS 7

typedef struct pictures_struct{
    int calories;
    char name[20];
    GBitmap* img;
    
  }pictures;

pictures* getPictures();

void initFoods();

void show_win_milestone(int foodid);
void hide_win_milestone(void);
