#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#include <Adafruit_TCS34725.h>
#include <Servo.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo miservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  tcs.begin();
  miservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);

  int R = int(red);
  int G = int(green);
  int B = int(blue);

  String color = "";

  if((R-G > 35)&(R-B > 35)){
    color = "RED";
    miservo.write(30);
  }

  if((G-R > 10)&(G-R > 30)){
    color = "GREEN";
    miservo.write(90);
  }

  if((B-G > 20)&(B-R > 40)){
    color = "BLUE";
    miservo.write(150);
  }

    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.print("R: ");
    display.print(int(red));
    display.print(" G: ");
    display.print(int(green));
    display.print(" B: ");
    display.println(int(blue));
    display.print("Color: ");
    display.print(color);
     display.setTextSize(2);  
    display.setCursor(40,10);
    display.display();
  
  Serial.print("R: ");
  Serial.print(int(red));
  Serial.print("  G: ");
  Serial.print(int(green));
  Serial.print("  B: ");
  Serial.print(int(blue));
  Serial.print("  Color: ");
  Serial.print(color);
  Serial.println();
}
