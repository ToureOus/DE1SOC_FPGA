#include "video.h"

video::video(){
  fd = open("/dev/mem",(O_RDWR | O_SYNC));
    if(fd == -1){
        std::cout << "ERROR: could not open /dev/mem..." << std::endl;
        exit(1);
    }
    char *virtual_base = (char *)mmap(NULL, LW_BRIDGE_SPAN,(PROT_READ | PROT_WRITE), MAP_SHARED,     fd, LW_BRIDGE_BASE);
    if(virtual_base == MAP_FAILED){
        std::cout << "ERROR: mmap() failed..." << std::endl;
        close(fd);
        exit(1);
    }
    pBase = virtual_base;
}

video::~video(){
  if(munmap(pBase,LW_BRIDGE_SPAN) != 0){
        std::cout << "ERROR: munmap() failed..." << std::endl;
        exit(1);
    }
    close(fd);
}

void video::initialize(){
  volatile int * video_resolution = (int *)(pBase + PIXEL_BUF_CTRL_BASE - LW_BRIDGE_BASE);
  screen_x = *video_resolution & 0xFFFF;
  screen_y = (*video_resolution >> 16) & 0xFFFF;
  volatile int * rgb_status = (int *)(pBase + RGB_RESAMPLER_BASE - LW_BRIDGE_BASE);
  db = get_data_bits(*rgb_status & 0x3F);
  res_offset = (screen_x == 160) ? 1 : 0;
  col_offset = (db == 8) ? 1 : 0;
}

void video::video_text(int x, int y, char * text_ptr){
  int offset;
  volatile char * character_buffer = (char *)(pBase + FPGA_CHAR_BASE - LW_BRIDGE_BASE); 
  offset = (y << 7) + x;
  while (*(text_ptr)) {
    *(character_buffer + offset) = *(text_ptr);
    ++text_ptr;
    ++offset;
  }
}

void video::video_box(int x1, int y1, int x2, int y2, short pixel_color){
  int pixel_buf_ptr = *(int *)(pBase + PIXEL_BUF_CTRL_BASE  - LW_BRIDGE_BASE);
  int pixel_ptr, row, col;
  int x_factor = 0x1 << (res_offset + col_offset);
  int y_factor = 0x1 << (res_offset);
  x1 = x1 / x_factor;
  x2 = x2 / x_factor;
  y1 = y1 / y_factor;
  y2 = y2 / y_factor;
  for (row = y1; row <= y2; row++){
    for (col = x1; col <= x2; ++col) {
      pixel_ptr = pixel_buf_ptr + (row << (10 - res_offset - col_offset)) + (col << 1);
      *(short *)(pixel_ptr + pBase -LW_BRIDGE_BASE) = pixel_color;
    }
  }
}

void video::resample_rgb(int color){
  if (db == 8) {
    color = (((color >> 16) & 0x000000E0) | ((color >> 11) & 0x0000001C) |
    ((color >> 6) & 0x00000003));
    color = (color << 8) | color;
  } else if (db == 16) {
    color = (((color >> 8) & 0x0000F800) | ((color >> 5) & 0x000007E0) |
    ((color >> 3) & 0x0000001F));
  }
  background_color = color;
}

int video::get_data_bits(int mode){
  switch (mode) {
    case 0x0:
      return 1;
    case 0x7:
      return 8;
    case 0x11:
      return 8;
    case 0x12:
      return 9;
    case 0x14:
      return 16;
    case 0x17:
      return 24;
    case 0x19:
      return 30;
    case 0x31:
      return 8;
    case 0x32:
      return 12;
    case 0x33:
      return 16;
    case 0x37:
      return 32;
    case 0x39:
      return 40;
  }
}