#include "address_map_arm.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <cmath>
using namespace std;

void video_text(int, int, char *, char *);
void rainbow_box(int, int, int, int,char *,short);
int nextColor(int, int);
void video_box(int, int, int, int, short,char *);
int resample_rgb(int, int);
int get_data_bits(int);
#define STANDARD_X 320
#define STANDARD_Y 240
#define INTEL_BLUE 0x0071C5
#define YELLOW 0xD1D100

int screen_x;
int screen_y;
int res_offset;
int col_offset;
// Physical base/starting address of FPGA Devices 
const unsigned int LW_BRIDGE_BASE = 0xC8000000;  // Base offset 

// Physical final address of FPGA Devices 
const unsigned int FINAL_PHYSICAL_ADDRESS = 0xFF203020;  // Final offset 

// Length of memory-mapped IO window 
const unsigned int LW_BRIDGE_SPAN = FINAL_PHYSICAL_ADDRESS - LW_BRIDGE_BASE; //; // Address map size

// Code from lab 6
char *Initialize(int *fd) 
{
	// Open /dev/mem to give access to physical addresses
	*fd = open( "/dev/mem", (O_RDWR | O_SYNC));
	if (*fd == -1)			//  check for errors in openning /dev/mem
	{
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
	}
   // Get a mapping from physical addresses to virtual addresses
   char *virtual_base = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, *fd, LW_BRIDGE_BASE);
   if (virtual_base == MAP_FAILED)		// check for errors
   {
      cout << "ERROR: mmap() failed..." << endl;
      close (*fd);		// close memory before exiting
      exit(1);        // Returns 1 to the operating system;
   }
   return virtual_base;
}

/** 
 * Close general-purpose I/O. 
 * 
 * @param pBase	Virtual address where I/O was mapped. 
 * @param fd	File descriptor previously returned by 'open'. 
 */ 
void Finalize(char *pBase, int fd) 
{
	if (munmap (pBase, LW_BRIDGE_SPAN) != 0)
	{
      cout << "ERROR: munmap() failed..." << endl;
      exit(1);
	}
   close (fd); 	// close memory
}

int main(void) {
  int fd; 
  char *pBase = Initialize(&fd);
  volatile int * video_resolution = (int *)(pBase + PIXEL_BUF_CTRL_BASE - LW_BRIDGE_BASE);
  screen_x = *video_resolution & 0xFFFF;
  screen_y = (*video_resolution >> 16) & 0xFFFF;
  volatile int * rgb_status = (int *)(pBase + RGB_RESAMPLER_BASE - LW_BRIDGE_BASE);
  int db = get_data_bits(*rgb_status & 0x3F);
  // check if resolution is smaller than the standard 320 x 240 
  res_offset = (screen_x == 160) ? 1 : 0;
  // check if number of data bits is less than the standard 16-bits 
  col_offset = (db == 8) ? 1 : 0;
  // create a message to be displayed on the video and LCD displays
  char text_top_row[40] = " EECE 2160 - Summer 1 - 2022\0";
  char text_bottom_row[40] = "Ousmane Toure & Jianning Chen\0";
  char empty[50] = "                                        \0";
  // update color 
  short background_color = resample_rgb(db, YELLOW);
  video_text(20, 29, empty, pBase);
  video_text(20, 30, empty, pBase);
  video_text(25, 29, text_top_row,pBase);
  video_text(25, 30, text_bottom_row,pBase);
  rainbow_box(0, 0, STANDARD_X, STANDARD_Y, pBase,0xFF00); // clear the screen
  video_box(23 * 4, 28 * 4, 56 * 4 - 1, 32 * 4 , background_color,pBase);
  Finalize(pBase, fd); 
}



/*******************************************************************************
* Subroutine to send a string of text to the video monitor
******************************************************************************/
void video_text(int x, int y, char * text_ptr, char *pBase) {
  int offset;
  volatile char * character_buffer = (char *)(pBase + FPGA_CHAR_BASE - LW_BRIDGE_BASE); // video
  offset = (y << 7) + x;
  while (*(text_ptr)) {
    *(character_buffer + offset) = *(text_ptr); // write to the character buffer
    ++text_ptr;
    ++offset;
  }
}
/*******************************************************************************
* Draw a filled rectangle on the video monitor
* Takes in points assuming 320x240 resolution and adjusts based on differences
* in resolution and color bits.
******************************************************************************/
void video_box(int x1, int y1, int x2, int y2, short pixel_color,char *pBase) {
  volatile int pixel_buf_ptr = *(int *)(pBase + PIXEL_BUF_CTRL_BASE  - LW_BRIDGE_BASE);
  int pixel_ptr, row, col;
  int x_factor = 0x1 << (res_offset + col_offset);
  int y_factor = 0x1 << (res_offset);
  x1 = x1 / x_factor;
  x2 = x2 / x_factor;
  y1 = y1 / y_factor;
  y2 = y2 / y_factor;
  /* assume that the box coordinates are valid */
  for (row = y1; row <= y2; row++) {
    for (col = x1; col <= x2; ++col) {
      pixel_ptr = pixel_buf_ptr + (row << (10 - res_offset - col_offset)) + (col << 1);
      *(short *)(pixel_ptr + pBase -LW_BRIDGE_BASE) = pixel_color; // set pixel color
    }
  }
}

void rainbow_box(int x1, int y1, int x2, int y2,char *pBase,short greenOffset){
  volatile int pixel_buf_ptr = *(int *)(pBase + PIXEL_BUF_CTRL_BASE  - LW_BRIDGE_BASE);
  int row, col;
  int x_factor = 0x1 << (res_offset + col_offset);
  int y_factor = 0x1 << (res_offset);
  x1 = x1 / x_factor;
  x2 = x2 / x_factor;
  y1 = y1 / y_factor;
  y2 = y2 / y_factor;
  /* assume that the box coordinates are valid */
  volatile char* pixel_ptr = pBase + pixel_buf_ptr - LW_BRIDGE_BASE;
  for (row = y1; row <= y2; row++) {
    for (col = x1; col <= x2; col++) {
      *(short *)(pixel_ptr + (row << 10) + (col << 1)) = 
      (short)(nextColor(row,cos(abs(col+greenOffset)/1020.0 * 6) * (x2-x1)));
    }
  }
}

int nextColor(int row, int green){
  int color = (31*row/240) + ((31-31*row/240) << 11) + ((int)(63*green/320) << 5);
  return color;
}
/********************************************************************************
* Resamples 24-bit color to 16-bit or 8-bit color
*******************************************************************************/
int resample_rgb(int num_bits, int color) {
  if (num_bits == 8) {
    color = (((color >> 16) & 0x000000E0) | ((color >> 11) & 0x0000001C) |
    ((color >> 6) & 0x00000003));
    color = (color << 8) | color;
  } else if (num_bits == 16) {
    color = (((color >> 8) & 0x0000F800) | ((color >> 5) & 0x000007E0) |
    ((color >> 3) & 0x0000001F)); 
  }
  return color;
}
/********************************************************************************
* Finds the number of data bits from the mode
*******************************************************************************/
int get_data_bits(int mode) {
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
