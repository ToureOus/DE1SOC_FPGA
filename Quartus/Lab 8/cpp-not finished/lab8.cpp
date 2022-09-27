#include "video.h"
#define YELLOW 0xD6E800

char text_top_row[40] = "EECE 2160 - Summer 1 - 2022\0";
char text_bottom_row[40] = "Ousmane Toure & Jianning Chen\0";

int main(){
  video *new_video = new video;
  new_video -> initialize();
  new_video -> resample_rgb(YELLOW);
  new_video -> video_text(32,29,text_top_row);
  new_video -> video_text(32,30,text_bottom_row);
  new_video -> video_box(0,0,320,240,0);
  new_video -> video_box(31*4,28*4,62*4-1,32*4,new_video->background_color);
  delete new_video;
}
  
