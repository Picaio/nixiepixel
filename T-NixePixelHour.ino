

#include <TFT_eSPI.h>
#include <SPI.h>

#include <WiFi.h>
#include "time.h"


#include "pixel0.h"
#include "pixel1.h"
#include "pixel2.h"
#include "pixel3.h"
#include "pixel4.h"
#include "pixel5.h"
#include "pixel6.h"
#include "pixel7.h"
#include "pixel8.h"
#include "pixel9.h"
#include "pixelp.h"


TFT_eSPI tft = TFT_eSPI();

const char* ssid     = "TU RED";
const char* password = "TU PASSWORD";

const char* ntpServer = "co.pool.ntp.org";//Colombia
const long  gmtOffset_sec = -18000;//gtm -5 (gtm*60*60)
const int   daylightOffset_sec = 0;

char Hour[3];
char Minute[3];
char seconds[3];

const short unsigned int*pixels[10]={pixel0,pixel1,pixel2,pixel3,pixel4,pixel5,pixel6,pixel7,pixel8,pixel9};

void setup() { 
  Serial.begin(115200);
  Serial.println("Start");
  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(1);//Para Pixeles
  tft.fillScreen(TFT_BLACK);
   delay(1000);

WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  initpixel();
   
}

void loop() {

  printLocalTime();
  showtime();
  delay(500);
     
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  strftime(Hour,3, "%H", &timeinfo);
  strftime(Minute,3, "%M", &timeinfo);
  strftime(seconds,3, "%S", &timeinfo);
  Serial.println(Hour[0]);
  Serial.println(Hour[1]);
  Serial.println(Hour[2]);
  Serial.println(Minute);
  Serial.println(seconds);

}
void initpixel(){
  
       tft.pushImage(0, 40,  28, 48, pixel0);
       tft.pushImage(30, 40,  28, 48, pixel0);
       tft.pushImage(60, 40,  28, 48, pixelp);
       tft.pushImage(90, 40,  28, 48, pixel0);
       tft.pushImage(120, 40,  28, 48, pixel0);
       tft.pushImage(150, 40,  28, 48, pixelp);
       tft.pushImage(180, 40,  28, 48, pixel0);
       tft.pushImage(210, 40,  28, 48, pixel0);
    
       
  }
void showtime(){

     tft.pushImage(180, 40,  28, 48,  pixels[String(seconds[0]).toInt()]);
     tft.pushImage(210, 40,  28, 48,  pixels[String(seconds[1]).toInt()]);
     tft.pushImage(90, 40,  28, 48,   pixels[String(Minute[0]).toInt()]);
     tft.pushImage(120, 40,  28, 48,  pixels[String(Minute[1]).toInt()]);
     tft.pushImage(0, 40,  28, 48,    pixels[String(Hour[0]).toInt()]);
     tft.pushImage(30, 40,  28, 48,   pixels[String(Hour[1]).toInt()]);
  
  }

 
