#include <GxEPD2_BW.h> 
#include <Fonts/FreeMonoBold9pt7b.h> 
#define ENABLE_GxEPD2_GFX 0
#define MAX_DISPLAY_BUFFER_SIZE 800 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_154_D67, MAX_HEIGHT(GxEPD2_154_D67)> display(GxEPD2_154_D67(/*CS=10*/ 10, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7)); // GDEH0154D67 200x200
#include "yt1.h"
#include "yt2.h"
#include "subs.h"
#include "iron2.h"
#include "QR137.h"
#include "QRsurvey.h"
int butpin = 2;
int val = 0;
int LEDR = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(butpin, INPUT);
  pinMode(LEDR, OUTPUT);
  display.init();
  delay(1000);
  display.firstPage();
  do{
    display.fillScreen(GxEPD_WHITE);
    delay(100);   
    display.drawRect(10, 10, 190, 190, GxEPD_BLACK);
    display.setCursor(15, 20);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextSize(1);
    display.print("Welcome!Tab&Buy!");
    display.drawBitmap(40, 50, gImage_QRsurvey, 123, 123, GxEPD_BLACK);
    
   
    delay(100);



  }while (display.nextPage());
display.powerOff();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (val == LOW) {         // check if the input is HIGH (button released)
      digitalWrite(LEDR, HIGH);
  }


}
