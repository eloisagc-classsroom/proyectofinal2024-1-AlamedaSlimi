// Agregamos las librerias necesarias
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define FREQUENCY             50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Pines analogicos para los potenciometros

int controlA = A0;
int controlB = A1;
int controlC = A2;
int controlD = A3;

// Pines para el Driver de servomotores

int motorA = 0;
int motorB = 4;
int motorC = 8;
int motorD = 12;

void setup() 
{
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}


void moveMotor(int controlIn, int motorOut)
{
  int pulse_wide, pulse_width, potVal;
  
  // Leer los valores del potenciometro
  potVal = analogRead(controlIn);
  
  // Convertir el ancho de los pulsos
  pulse_wide = map(potVal, 0, 1023, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  
  //Controlar el motor
  pwm.setPWM(motorOut, 0, pulse_width);

}

void loop() {

  //Control Motor A
  moveMotor(controlA, motorA);
  
  //Control Motor B
  moveMotor(controlB, motorB);
    
  //Control Motor C
  moveMotor(controlC, motorC);
  
  //Control Motor D
  moveMotor(controlD, motorD);
  
}
