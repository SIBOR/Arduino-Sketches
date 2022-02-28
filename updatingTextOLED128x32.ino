/**************************************************************************
 Displays updating text to an OLED over I2C
 3 pins are required to interface (two I2C and one reset).
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int increment = 0;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  delay(2000);            // Pause for 2 seconds

  display.clearDisplay(); //Clear buffer (will have Arduino Splash in buffer on startup)

  delay(2000);            //Pause for 2 seconds
}

void loop() {
  drawText(); // Draw text That periodically increments each time it is called

  delay(100); // Wait for next iteration
}

void drawText(void){
  display.clearDisplay();
  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0,0);               // Start at top-left corner
  
  display.print(F("Number: "));         //Use print for char by char, or println for a line(automatically adds a newline character at the end.)
  display.print(increment, DEC);
  
  increment++;                          //Change number in a fun and interesting way
  
  display.display();                    // Must be called to show new text
}
