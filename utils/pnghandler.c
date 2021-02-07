#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <zlib.h>
#include <png.h>
#include <dirent.h>
#include <string.h>

void print2DArray_int_withshape(int **array, int shapeOne, int shapeTwo) {
  printf("start print array with shape: [%d][%d]\n", shapeOne, shapeTwo);
  for (int i = 0 ; i < shapeOne ; i++) {
    printf("\n");
    for (int a = 0 ; a < shapeTwo ; a++) {
      unsigned int value = array[i][a];
      int r = (value >> (8 * 2)) & 0xff;
      int g = (value >> (8 * 1)) & 0xff;
      int b = (value >> (8 * 0)) & 0xff;
      // printf("r: %d, g: %d, b: %d\n", r, g, b);
      // printf("%s\n", "\x1b[31mtest\033[0ming");
      printf("\x1b[38;2;%d;%d;%dm口", r, g, b);
      // printf("[38;2;%d;%d;%dO", r, g, b);
      // printf("[%d][%d]: %x\n", i, a, showValue);
      // int useColor = (showValue == 0) ? 
    }
  }
  printf("\n\x1b[38;2;%d;%d;%dmprint array end\n", 255, 255, 255);
}

/*
void print2DArray_int(int **array, int shapeOne, int shapeTwo) {
  printf("start print array with shape: [%d][%d]\n", shapeOne, shapeTwo);
  for (int i = 0 ; i < shapeOne ; i++) {
    printf("\n");
    for (int a = 0 ; a < shapeTwo ; a++) {
      unsigned int value = array[i][a];
      int r = (value >> (8 * 2)) & 0xff;
      int g = (value >> (8 * 1)) & 0xff;
      int b = (value >> (8 * 0)) & 0xff;
      // printf("r: %d, g: %d, b: %d\n", r, g, b);
      // printf("%s\n", "\x1b[31mtest\033[0ming");
      printf("\x1b[38;2;%d;%d;%dm口", r, g, b);
      // printf("[38;2;%d;%d;%dO", r, g, b);
      // printf("[%d][%d]: %x\n", i, a, showValue);
      // int useColor = (showValue == 0) ? 
    }
  }
  printf("\n\x1b[38;2;%d;%d;%dmprint array end\n", 255, 255, 255);
}

void printArray(int *array, int arrayLength) {
  for (int i = 0 ; i < arrayLength ; i++) {
    printf("[%d]: %d\n", i, array[i]);
  }
}
*/

double useRegulateNum = 127.5;
void getDataFromPng(char *filename, double *xList) {
  int width, height;
  png_byte color_type;
  png_byte bit_depth;
  png_bytep *row_pointers = NULL;
  FILE *fp = fopen(filename, "rb");
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();
  png_infop info = png_create_info_struct(png);
  if(!info) abort();
  if(setjmp(png_jmpbuf(png))) abort();
  png_init_io(png, fp);
  png_read_info(png, info);
  width      = png_get_image_width(png, info);
  height     = png_get_image_height(png, info);
  color_type = png_get_color_type(png, info);
  bit_depth  = png_get_bit_depth(png, info);
  if(bit_depth == 16)
    png_set_strip_16(png);
  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);
  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);
  png_read_update_info(png, info);
  if (row_pointers) abort();
  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for(int y = 0; y < height; y++) {
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }
  png_read_image(png, row_pointers);
  
  int xIndex = 0;
  for (int i = 0 ; i < width ; i++) {
    for (int a = 0 ; a < height ; a++) {
      int value = row_pointers[i][a];
      int lastByteValue = (value >> (8 * 0)) & 0xff;
      double useValue = (double) lastByteValue;
      double regulateValue = (useValue - useRegulateNum) / useRegulateNum;
      xList[xIndex] = regulateValue;
      xIndex += 1;
    }
  }
  for(int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);
  fclose(fp);
  png_destroy_read_struct(&png, &info, NULL);
}

void read_png_file(char *filename) {
  int width, height;
  png_byte color_type;
  png_byte bit_depth;
  png_bytep *row_pointers = NULL;

  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  width      = png_get_image_width(png, info);
  height     = png_get_image_height(png, info);

  printf("width: %d, height: %d\n", width, height);

  color_type = png_get_color_type(png, info);
  bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(bit_depth == 16)
    png_set_strip_16(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  if (row_pointers) abort();

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for(int y = 0; y < height; y++) {
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, row_pointers);

  print2DArray_int(row_pointers, height, width);

  fclose(fp);

  png_destroy_read_struct(&png, &info, NULL);
}

int getTotalPixel(char *filename) {
  int width, height;

  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  width = png_get_image_width(png, info);
  height = png_get_image_height(png, info);

  int totalPixel = width * height;
  return totalPixel;
}

void readpng_version_info() {
  fprintf(stderr, "   Compiled with libpng %s; using libpng %s.\n",
    PNG_LIBPNG_VER_STRING, png_libpng_ver);
  fprintf(stderr, "   Compiled with zlib %s; using zlib %s.\n",
    ZLIB_VERSION, zlib_version);
}

bool checkIfValid(char *fileName) {
  if (strcmp(fileName, ".") == 0) {
    return false;
  } else if (strcmp(fileName, "..") == 0) {
    return false;
  }
  return true;
}
