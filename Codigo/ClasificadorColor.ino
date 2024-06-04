//Librerias principales
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Variables para el funcionamiento del OLED
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Variables para probar la pantalla
#define NUMFLAKES     10 
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

//Librerias para el sensor y el servomotor
#include <Adafruit_TCS34725.h>
#include <Servo.h>

//Variables para el sensor y el servomotor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo miservo;

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Para ciclar la comprobacion
  }
  tcs.begin(); // Iniciar el sensor
  miservo.attach(9); // Iniciar el servomotor
}

void loop() {
	//Variables para detectar mediante RGB
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);

  int R = int(red);
  int G = int(green);
  int B = int(blue);

	//Variable para desplegar el color en pantalla
  String color = "";
	
	//Condicional para determinar si un objeto es rojo
  if((R-G > 35)&(R-B > 35)){
    color = "RED";
    miservo.write(30);
  }

	//Condicional para determinar si un objeto es verde
  if((G-R > 10)&(G-R > 30)){
    color = "GREEN";
    miservo.write(90);
  }

	//Condicional para determinar si un objeto es azul
  if((B-G > 20)&(B-R > 40)){
    color = "BLUE";
    miservo.write(150);
  }

	//Se limpia y se configura la pantalla OLED
    display.clearDisplay();
    display.setTextSize(1);            
    display.setTextColor(SSD1306_WHITE);       
    display.setCursor(0,0);             
    
    //Se muestran los datos actuales detectados por el sensor
    display.print("R: ");
    display.print(int(red));
    display.print(" G: ");
    display.print(int(green));
    display.print(" B: ");
    display.println(int(blue));
    
    //Se muestra el color en funcion de las condicionales
    display.print("Color: ");
    display.print(color);
     display.setTextSize(2);  
    display.setCursor(40,10);
    display.display();
  
  //Se muestra lo mismo que desplegamos en pantalla en la consola serial
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
