#include <SmartLEDShieldV4.h>  // comment out this line for if you're not using SmartLED Shield V4 hardware (this line needs to be before #include <SmartMatrix3.h>)
#include <SmartMatrix3.h>

#include "gimpbitmap.h"
#include "wayfinder.c"
#include "knight-head.c"
#include "calvinseal.c"
#include "leroy.c"
#include "ripstone.c"
#include "qman.c"

#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;        // known working: 16, 32, 48, 64
const uint8_t kMatrixHeight = 64;       // known working: 32, 64, 96, 128
const uint8_t kRefreshDepth = 48;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_64ROW_MOD32SCAN; // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels, or use SMARTMATRIX_HUB75_64ROW_MOD32SCAN for common 64x64 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
///// COLORS /////
rgb24 WHITE = {0xff, 0xff, 0xff};
rgb24 GREEN = {0, 0xff, 0};
rgb24 RED = {0xff, 0 ,0};
rgb24 BLUE = {0, 0, 0xff};
rgb24 BLACK = {0,0,0};

/////////////////////////////////////////////////////////////////////
int STRING_DELAY = 5000;
int led = 13;
int bright = 30;

void drawBitmap64(int16_t x, int16_t y, const gimp64x64bitmap* bitmap) {
  for(unsigned int i=0; i < bitmap->height; i++) {
    for(unsigned int j=0; j < bitmap->width; j++) {
      SM_RGB pixel = { bitmap->pixel_data[(i*bitmap->width + j)*3 + 0],
                      bitmap->pixel_data[(i*bitmap->width + j)*3 + 1],
                      bitmap->pixel_data[(i*bitmap->width + j)*3 + 2] };

      backgroundLayer.drawPixel(x + j, y + i, pixel);
    }
  }
}

void setup() {
  matrix.addLayer(&backgroundLayer); 
  matrix.addLayer(&scrollingLayer); 
  matrix.begin();
  matrix.setBrightness((bright*255/100));
  pinMode(led, OUTPUT);
}

void fadeOut(int brightLevel=bright) {
  for (unsigned int i=(bright*255/100); i > 0; i--) {
    delay(10);
    backgroundLayer.setBrightness(i);
  }
}

void fadeIn(int brightLevel=bright) {
    for (unsigned int i=0; i < (unsigned int)(bright*255/100); i++) {
    delay(35);
    backgroundLayer.setBrightness(i);
  }
}

void BLANK_SCREEN() {
  backgroundLayer.fillScreen({0,0,0});
  backgroundLayer.swapBuffers();
}

void showBitmap(const gimp64x64bitmap* bitmap, int waitTime, int brightLevel=bright) {
  showBitmapRAW(bitmap);
  backgroundLayer.swapBuffers();
  fadeIn(brightLevel);
  delay(waitTime);
  backgroundLayer.fillScreen({0,0,0});
  fadeOut(brightLevel);
  backgroundLayer.swapBuffers();
  
}

void showBitmapRAW(const gimp64x64bitmap* bitmap) {
  int x,y;
  backgroundLayer.setBrightness(0);
  backgroundLayer.fillScreen({0,0,0});
  x = (kMatrixWidth / 2) - (bitmap->width/2);
  y = (kMatrixHeight / 2) - (bitmap->height/2);

  drawBitmap64(x,y, bitmap);
}

void writeText(ScrollMode mode, const char* text, rgb24 textColor, int offSet, fontChoices myFont=font8x13) {
  scrollingLayer.setMode(mode);
  scrollingLayer.setColor(textColor);
  scrollingLayer.setSpeed(60);
  scrollingLayer.setFont(myFont);
  scrollingLayer.setOffsetFromTop(offSet);
  scrollingLayer.start(text, 3);
}


void loop() {
  // CS IS THE BEST + Calvin Knight
  writeText(bounceForward, "CS is the BEST!", WHITE, 30);
  //scrollingLayer.stop();
  delay(1000);
  showBitmap((const gimp64x64bitmap*)&calvinknight, STRING_DELAY);
  delay(STRING_DELAY);
  scrollingLayer.stop();

  // HI MOM :D
  writeText(stopped, " Hi Mom!", WHITE, 15);
  backgroundLayer.setBrightness(255);
  backgroundLayer.setFont(font6x10);
  backgroundLayer.drawString(2, matrix.getScreenHeight() / 2, GREEN, {0,0,0}, "    :D");
  backgroundLayer.swapBuffers();
  delay(STRING_DELAY);
  BLANK_SCREEN();

  // (THIS IS QUENTIN)
  backgroundLayer.setBrightness(0);
  writeText(stopped, "", WHITE, 15);
  backgroundLayer.setFont(font8x13);
  backgroundLayer.drawString(3, 15, WHITE, "This is");
  backgroundLayer.drawString(2, matrix.getScreenHeight() - 25 , GREEN, "Quentin");
  backgroundLayer.swapBuffers();
  fadeIn(100);
  delay(STRING_DELAY);
  showBitmap((const gimp64x64bitmap*)&qman, STRING_DELAY, 15);
  delay(500);
  writeText(stopped, "(That was me)",WHITE, 10, font5x7);
  delay(STRING_DELAY);
  scrollingLayer.stop();
  delay(500);
  
  writeText(wrapForward, "RESPECT THE BEARD", GREEN, 35);
  delay(5);
  showBitmap((const gimp64x64bitmap*)&leroy, STRING_DELAY, 15);
  writeText(stopped, "", WHITE, 15);
  delay(500);

  // Rip Calvin College
  showBitmap((const gimp64x64bitmap*)&ripstone, STRING_DELAY*(2/3), 40);
  delay(500);

  writeText(wrapForward, "...AND WELCOME CALVIN UNIVERSITY!", RED, 30);
  delay(1000);
  showBitmap((const gimp64x64bitmap*)&wayfinder, STRING_DELAY);
  delay(STRING_DELAY*3);
}
