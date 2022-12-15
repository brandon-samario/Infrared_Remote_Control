/*
The purpose of this program is to be able to control the robot car using an IR remote.
Using an IR remote introduces us with different codes for each button.
Each movement is set to a button controlled using movement functions.
*/

#include <arduino.h>
#include <IRremote.h>

#define F 16736925	//FORWARD (PRESS)
#define B 16754775	//BACK (PRESS)
#define L 16720605	//LEFT (PRESS)
#define R 16761405	//RIGHT (PRESS)
#define S 16712445	//STOP (PRESS)
#define UNKNOWN_F 5316027		  //FORWARD (HOLD)
#define UNKNOWN_B 2747854299	//BACK (HOLD)
#define UNKNOWN_L 1386468383	//LEFT (HOLD)
#define UNKNOWN_R 553536955		//RIGHT (HOLD)
#define UNKNOWN_S 3622325019	//STOP (HOLD)

#define RECV_PIN 9 //Pin of IR reciever

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;
unsigned long preMillis;

//MOVEMENT 1
void forward(){
digitalWrite(7,HIGH); //Left motors ON
digitalWrite(8,HIGH); //Right motors ON

analogWrite(5,155); //Set Speed for left motors
analogWrite(6,155); //Set Speed for right motors
Serial.println("forward!"); //Text printed when forward function is in use
}

//MOVEMENT 2
void back(){
digitalWrite(7,LOW); //Left motors OFF
digitalWrite(8,LOW); //Right motors OFF

analogWrite(5,155); //Set speed for left motors
analogWrite(6,155); //Set speed for right motors
Serial.println("back!"); //Text printed when back function is in use
}

//MOVEMENT 3
void left(){
digitalWrite(7,HIGH); //Left motors ON
digitalWrite(8,LOW); //Right motors OFF

analogWrite(5,55); //Set speed for left motors
analogWrite(6,55); //Set speed for right motors
Serial.println("left!"); //Text printed when left function is in use
}

//MOVEMENT 4
void right(){
digitalWrite(7,LOW); //Left motors OFF
digitalWrite(8,HIGH); //Right motors ON

analogWrite(5,55); //Set speed for left motors
analogWrite(6,55); //Set speed for right motors
Serial.println("right!"); //Text printed when right function is in use
}

//MOVEMENT 5
void stop(){
digitalWrite(7,LOW); //Left motors OFF
digitalWrite(8,LOW); //Right motors OFF

analogWrite(5,0); //Set speed for left motors
analogWrite(6,0); //Set speed for right motors
Serial.println("stop!"); //Text printed when stop function is in use
}

void setup(){
Serial.begin(9600); //Initilize serial monitor
pinMode(5,OUTPUT); //Pin 5 set as an output
pinMode(6,OUTPUT); //Pin 6 set as an output
pinMode(7,OUTPUT); //Pin 7 set as an output
pinMode(8,OUTPUT); //Pin 8 set as an output
pinMode(3,OUTPUT); //Pin 3 set as an output
digitalWrite(3,1); //Standby
irrecv.enableIRIn(); //Enable IR reciever 
}

void loop(){ 
  if (irrecv.decode(&results)){ 
    preMillis = millis();
    val = results.value;
    Serial.println(val);
    irrecv.resume();
    switch(val){
      case F: 
      case UNKNOWN_F: forward(); break; //Use forward function
      case B: 
      case UNKNOWN_B: back(); break; //Use back function
      case L: 
      case UNKNOWN_L: left(); break; //Use left function
      case R: 
      case UNKNOWN_R: right();break; //Use right function
      case S: 
      case UNKNOWN_S: stop(); break; //Use stop function
      default: break;
    }
  }
  else{
    if(millis() - preMillis > 500){
      stop();
      preMillis = millis();
    }
  }
}