

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 10
#define TFT_CS 8
#define TFT_RST 9
#define TFT_MISO 10
#define TFT_MOSI 11
#define TFT_CLK 13
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
 Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
#define cambien A0
float U = 220;
float giadienB1 = 1678.0, giadienB2 = 1734.0, giadienB3 = 2014.0,giadienB4 =2536.0,giadienB5 =2834.0,giadienB6 =2461.0;
float bb1=0.0;
float bb2=0.0;
float bb3=0.0;
float bb4=0.0;
float bb5=0.0;
float bb6=0.0;
float p=0.0, w =0.0,old=0.0;
long times =0.0;
long time1 =0.0;
void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
 
  
pinMode(cambien, INPUT);
  // read diagnostics (optional but can help debug problems)
  tft.begin();
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  //x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
 // tft.fillScreen(ILI9341_BLACK);
  delay(1000);
    tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println("KET NOI MACH DO DONG");
  
  tft.setTextColor(ILI9341_GREEN);    tft.setTextSize(2);
  tft.println("  DIEN AP: 220VAC   ");
  tft.setCursor(0, 35);
  tft.setTextColor(ILI9341_GREEN);    tft.setTextSize(2);
  Serial.println(F("Done!"));
  times == millis();
  time1 == millis();
}


void loop(void) {
  float A = analogRead(cambien);
  float I = A/1024.0 * 30.0;
  I = I-20;
  if(I<=0){I=0;}
  w = U*I;
  if(millis() - time1 > 1000){
    w = w/3600.0;
    p = p+w;
    time1 =millis();
  }
  Serial.println(p);
  if(p <= 50.0){//Công suất được tính theo Wat để tối ưu thời gian báo cáo và thửu nghiệm
    bb1 = p;
  }
  if(p > 50.0 && p <= 100.0){
    bb2 = p;
    bb1 = 50.0;
  }
  if(p > 100.0 && p <= 200.0){
    bb3 =p;
    bb2 = 100.0;
    bb1 = 50.0;
  }
  if(p > 200.0 && p <= 300.0){
    bb4 =p;
    bb3 = 200.0;
    bb2 = 100.0;
    bb1 = 50.0;
  }
  if(p > 300.0 && p <= 400.0){
    bb5 =p;
    bb4 = 300.0;
    bb3 = 200.0;
    bb2 = 100.0;
    bb1 = 50.0;
  }
  if(p > 400.0){;
    bb6 = p;
    bb5 = 400.0;
    bb4 = 300.0;
    bb3 = 200.0;
    bb2 = 100.0;
    bb1 = 50.0;
  }
  //tft.setCursor(0, 0);
 /* tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println("KET NOI MACH DO DONG");
  
  tft.setTextColor(ILI9341_GREEN);    tft.setTextSize(2);
  tft.println("  DIEN AP: 220VAC   ");*/
  tft.setCursor(0, 35);
  tft.setTextColor(ILI9341_GREEN);    tft.setTextSize(2);
  tft.print("DONG DIEN: " + String(I));
  tft.println();
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.println(" __________________");
  tft.println("|BAC  (W) |TONG W/h");
  tft.setCursor(0, 85);
  tft.println("|1:0-50   |" + String(bb1));
  tft.println("|2:51-100 |" + String(bb2));
  tft.println("|3:101-200|" + String(bb3));
  tft.println("|4:201-300|" + String(bb4));
  tft.println("|5:301-400|" + String(bb5));
  tft.println("|6:401 -> |" + String(bb6));
  tft.println("|_________|________");
  float tiendien = bb1*giadienB1 + bb2*giadienB2 + bb3*giadienB3 + bb4*giadienB4 + bb5*giadienB5 + bb6*giadienB6;
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(1);
  tft.println(String("TONG TIEN DIEN: ") + String(tiendien) + String(" vnd"));
  tft.setTextSize(1);
  tft.println(String("TONG CONG SUAT: ") + String(p) + String(" W/h"));
  tft.println("1W tuong duong voi 1Kw thuc te, De tiet kiem thoi gian bao cao va thu nghiem");
  tft.setTextColor(ILI9341_WHITE);
  delay(100);
  tft.setCursor(132, 35);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(2);
  tft.print(I);
  tft.setCursor(132, 85);
  tft.print(bb1);
  tft.setCursor(132, 101);
  tft.print(bb2);
  tft.setCursor(132, 117);
  tft.print(bb3);
  tft.setCursor(132, 133);
  tft.print(bb4);
  tft.setCursor(132, 149);
  tft.print(bb5);
  tft.setCursor(132, 165);
  tft.print(bb6);
  tft.setTextSize(1);
  tft.setCursor(96, 197);
  tft.println(tiendien + String(" vnd"));
  tft.setCursor(96, 205);
  tft.println(String(p) + String(" W/h"));
  
}
