#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#include <Adafruit_TCS34725.h>
#include <Servo.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo miservo;

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  tcs.begin();
  miservo.attach(9);
}

void loop() {
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
    display.setTextSize(1);            
    display.setTextColor(SSD1306_WHITE);       
    display.setCursor(0,0);             
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
