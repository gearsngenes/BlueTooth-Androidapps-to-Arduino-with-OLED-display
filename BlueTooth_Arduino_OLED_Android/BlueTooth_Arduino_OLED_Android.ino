

#define START_CMD_CHAR1 '>'
#define DEBUG 1 // Set to 0 if you don't want serial output of sensor data

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX

// ************** Adafruit MonoChrome Oled Initializations
#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
// ************** Adafruit MonoChrome Oled Initializations Complete

int pin1 = 9; //

bool oldv = 0; // state
 

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("BT Demo");
 
  //******Monochrome OLED Setup

  Wire.begin();
  pinMode (pin1, INPUT);


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(5);
  display.clearDisplay();
  display.display();
  /* end of Adafruit Default Specification */
  /* Basic "hello world!" */

oldv = digitalRead(pin1);
  display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextSize(3);
    display.setCursor(0, 20);
    display.println("BT Demo"); // starting sign
    display.display();
    delay(500);
   display.clearDisplay();
/*    display.setCursor(0,20);
    display.println("Conect?");
    display.display();
*/

  //******Monochrome OLED Setup


}


void loop()
{
  if (!(oldv==digitalRead(pin1))) {display.clearDisplay(); oldv=digitalRead(pin1);}
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  if (digitalRead(pin1)) {
    display.println("Voice BT");
  } else {
    display.println("Ping BT");
  }
  delay(100); display.display();

  
  Serial.flush();    String  inst;
  if ( BTSerial.available() < 1) {
    return;
  }

  else
  {

    BTSerial.println(inst = BTSerial.readString());

    if ( digitalRead(pin1))//Pin1 == HIGH means it is "voice".
    {
      inst = inst.substring(1, inst.length() - 1);
    }
    Print (digitalRead(pin1), inst);

  }
}

void Print(boolean pinv, String s)
{
  Serial.print (pin1); Serial.print("Is  :");  Serial.print(digitalRead(pin1)); Serial.print("In value:"); Serial.println(s );

  display.clearDisplay();
/*  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  if (pinv) {
    display.println("Voice BT");
  } else {
    display.println("Ping BT");
  }
*/
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("In:"); display.println(s);  display.setTextSize(1);
   display.setCursor(0, 50);

  display.print("Len:"); display.println(s.length());
  delay(100); display.display();


}






