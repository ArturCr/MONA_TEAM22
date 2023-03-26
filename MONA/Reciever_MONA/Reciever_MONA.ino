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
#include "printf.h"


int Motor_right_PWM = 10;  //   0 (min speed) - 255 (max speed) 
int Motor_right_direction = 5;  //   0 Forward - 1 Reverse
int Motor_left_PWM = 9;    //   0 (min speed) - 255 (max speed)  
int Motor_left_direction = 6;   //   0 Forward - 1 Reverse
#define Forward 0
#define Reverse 1

RF24 radio(7, 8); // CE, CSN



bool radioNumber = 1;  // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
float payload = 0.0;



const byte address[6] = "00001";

void setup() {

  pinMode(Motor_left_PWM, OUTPUT);
  pinMode(Motor_right_PWM, OUTPUT);
  //Serial.begin(9600);
  //radio.begin();
  //radio.openReadingPipe(0, address);
  //radio.setPALevel(RF24_PA_MIN);
  //radio.startListening();








  Serial.begin(9600);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }

  // print example's introductory prompt
  Serial.println(F("RF24/examples/GettingStarted"));

  // To set the radioNumber via the Serial monitor on startup
  Serial.println(F("Which radio is this? Enter '0' or '1'. Defaults to '0'"));
  while (!Serial.available()) {
    // wait for user input
  }
  char input = Serial.parseInt();
  radioNumber = input == 1;
  Serial.print(F("radioNumber = "));
  Serial.println((int)radioNumber);

  // role variable is hardcoded to RX behavior, inform the user of this
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_MIN);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload));  // float datatype occupies 4 bytes

  // set the TX address of the RX node into the TX pipe
  //radio.openWritingPipe(00002);  // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(0, 00001);  // using pipe 0

  // additional setup specific to the node's role
  if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening();  // put radio in RX mode
  }

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data    
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);

    if (text == "Hello World"){

      forward();
      
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
