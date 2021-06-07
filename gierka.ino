#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
class OLEDDisplay{
  public: 
  unsigned char screen[64*16];
  OLEDDisplay()
  {
    memset(screen, 1024, 0x00);
  }
 
  void activatePixel(int x, int y)
  {
    int bitnumber = x % 8;
    int x_byteID = x/8;
    screen[(1008-(y*16))+x_byteID] |= (128>>bitnumber); 
  }
 
  unsigned char* getScreen()
  {
    return screen;
  }
 
};
 
 
OLEDDisplay myDisplay; 
void setup()   
{               
  Serial.begin(115200); 
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
 
  // Clear the buffer.
  display.clearDisplay();
  display.drawBitmap(0, 0,  myDisplay.getScreen(), 128, 64, WHITE);
  display.display();
}
 
void loop() {
 
  for(int i = 0 ; i < 128; i++){
  myDisplay.activatePixel(i,0); 
  display.clearDisplay();
  display.drawBitmap(0, 0,  myDisplay.getScreen(), 128, 64, WHITE);
  display.display();
  delay(50);
  }
 
  for(int i = 0 ; i < 64; i++){
  myDisplay.activatePixel(0,i); 
  display.clearDisplay();
  display.drawBitmap(0, 0,  myDisplay.getScreen(), 128, 64, WHITE);
  display.display();
  delay(50);
  }
 
  for(int i = 127 ; i >= 0; i--){
  myDisplay.activatePixel(i,63); 
  display.clearDisplay();
  display.drawBitmap(0, 0,  myDisplay.getScreen(), 128, 64, WHITE);
  display.display();
  delay(50);
  }
 
  for(int i = 63; i >= 0; i--){
  myDisplay.activatePixel(127,i); 
  display.clearDisplay();
  display.drawBitmap(0, 0,  myDisplay.getScreen(), 128, 64, WHITE);
  display.display();
  delay(50);
  }
}