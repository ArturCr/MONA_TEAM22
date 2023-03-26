/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"


int Motor_right_PWM = 10;  //   0 (min speed) - 255 (max speed) 
int Motor_right_direction = 5;  //   0 Forward - 1 Reverse
int Motor_left_PWM = 9;    //   0 (min speed) - 255 (max speed)  
int Motor_left_direction = 6;   //   0 Forward - 1 Reverse
#define Forward 0
#define Reverse 1

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {

  pinMode(Motor_left_PWM, OUTPUT);
  pinMode(Motor_right_PWM, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);

    if (text == "Hello World"){

      forward(1000)
      
    }
    
    
  }

  delay(100);        // delay in between reads for stability
}





void forward(){
  analogWrite(Motor_right_PWM,40); // right motor
  digitalWrite(Motor_right_direction,Forward); //right
  analogWrite(Motor_left_PWM, 40); // left 
  digitalWrite(Motor_left_direction,Forward); //left
}

void reverse(int delay_time){
  analogWrite(Motor_right_PWM,120 ); // right motor
  digitalWrite(Motor_right_direction,Reverse); //right
  analogWrite(Motor_left_PWM, 120); // left 
  digitalWrite(Motor_left_direction,Reverse); //left
  delay(delay_time);
}

void right(int delay_time){
  reverse(50);
  analogWrite(Motor_right_PWM,120 ); // right motor
  digitalWrite(Motor_right_direction,Reverse); //right
  analogWrite(Motor_left_PWM, 40); // left 
  digitalWrite(Motor_left_direction,Forward); //left
  delay(delay_time);
}

void left(int delay_time){
  reverse(50);
  analogWrite(Motor_right_PWM,40 ); // right motor
  digitalWrite(Motor_right_direction,Forward); //right
  analogWrite(Motor_left_PWM, 120); // left 
  digitalWrite(Motor_left_direction,Reverse); //left
  delay(delay_time);
}
