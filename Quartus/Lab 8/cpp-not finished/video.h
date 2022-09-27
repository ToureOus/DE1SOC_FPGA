#ifndef VIDEO_H
#define VIDEO_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include "address_map_arm.h"

const unsigned int LW_BRIDGE_BASE = 0xFF200000;
const unsigned int FINAL_PHYSICAL_ADDRESS = 0xFF203020;
const unsigned int LW_BRIDGE_SPAN = FINAL_PHYSICAL_ADDRESS - LW_BRIDGE_BASE;

class video{
public:
    video();
    ~video();
    void initialize();
    void video_text(int x, int y, char * text_ptr);
    void video_box(int x1, int y1, int x2, int y2, short pixel_color);
    void resample_rgb(int color);
    short background_color;

private:
    char *pBase;
    int fd;
    int screen_x;
    int screen_y;
    int db;
    int res_offset;
    int col_offset;
    int get_data_bits(int mode);
};
    
#endif //VIDEO_H