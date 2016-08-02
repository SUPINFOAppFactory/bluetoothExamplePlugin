/****Setup display ***************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/*******************************/


#define LED_PIN  8
int state = 0;
int counter = 0;

void setup() {
 pinMode(LED_PIN, OUTPUT);
 digitalWrite(LED_PIN, LOW);

 Serial.begin(9600); // Default connection rate for my BT module

 // setup display
 display.begin(SSD1306_SWITCHCAPVCC);
 //display.display();
 //delay(3000);
 display.clearDisplay();
 display.setTextSize(2);
 display.setTextColor(BLACK,WHITE);
 display.print(" BuildFire");
 display.display();
 display.setTextColor(WHITE);
}

int runLogic(char state){
   if (state == '0') {
     digitalWrite(LED_PIN, LOW);
     Serial.println(" LED: off");
   }
   else if (state == '1') {
     digitalWrite(LED_PIN, HIGH);
     Serial.println(" LED: on");
     counter++;
   }
   else{
     Serial.print("Sorry I dont understand: ");
     Serial.println(state);
   }

  /// display on OLED Display
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("ON cnt ");
  display.println(counter);
  display.display();

  //. Send to BT
  display.clearDisplay();
  Serial.print("\rTimes turned on: ");
  Serial.println(counter);
  Serial.print("\n"); // this is the terminator for the packet so the app understands the cycle is done
}

void loop() {

 if(Serial.available() > 0){
   state = Serial.read();
   runLogic(state);
 }
}

