#include "SoftwareSerial.h"

#define trigPin1 3
#define echoPin1 2

//#define trigPin2 6
//#define echoPin2 7
//
//#define trigPin3 11
//#define echoPin3 10
//
//#define trigPin4 4//number
//#define echoPin4 5//number

#define humanheight 20 //dist in cm

SoftwareSerial mySerial(10, 11);
//boolean isPlaying = false;
long distance = 0;
long distanceOld = 0;

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

int getDistance(int trigger, int echo){
  long duration; //new long type called duration
  long distance; // new long called distance
  long distanceOld;
  
  digitalWrite(trigger, LOW); //trigger OFF
  delayMicroseconds(2); //wait very short time
  digitalWrite(trigger, HIGH); //trigger ON
  delayMicroseconds(10); // keep the trigger on for 10 microseconds
  digitalWrite(trigger, LOW); //turn trigger back off
  duration = pulseIn(echo, HIGH); //pulse in returns a time value of how long it takes to see signal on echo pin
  distance = (duration/2) / 29.1; //duration to distance speed of sound math

  //Serial.println(distance);
  return(distance);
}

//*********mp3 player functions
//void playFirst()
//{
//  execute_CMD(0x3F, 0, 0);
//  delay(500);
//  setVolume(0x30);
//  delay(500);
//  //execute_CMD(0x11,0,0x00);
//  delay(500);
//}

void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}

void pause()
{
  execute_CMD(0x0E,0,0);
  delay(500);
}

void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}

//void setPlayback(int mode)
//{
//  execute_CMD(0x08, 0, mode);
//  delay(500);
//}
//
//void setRepeat()
//{
//  execute_CMD(0x11, 0, 0);
//  delay(500);
//}


//void DFRobotDFPlayerMini::enableLoopAll(){
//
//  sendStack(0x11, 0x01);
//
//}
//
//
//
//void DFRobotDFPlayerMini::disableLoopAll(){
//
//  sendStack(0x11, 0x00);
//
//}

void execute_CMD(byte CMD, byte Par1, byte Par2)
  // Excecute the command and parameters
  {
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
  Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
  //Send the command line to the module
  for (byte k=0; k<10; k++)
  {
    mySerial.write( Command_line[k]);
  }
  }
//*******end mp3 player functions

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
//  pinMode(trigPin2, OUTPUT);
//  pinMode(echoPin2, INPUT);
//  pinMode(trigPin3, OUTPUT);
//  pinMode(echoPin3, INPUT);
//  pinMode(trigPin4, OUTPUT);
//  pinMode(echoPin4,INPUT);


  mySerial.begin (9600);
  delay(500);
  //setPlayback(2);
  //setRepeat();
  //playFirst();
  play();
  //isPlaying = true;
}

void loop() {
  distanceOld = distance;
  
  // put your main code here, to run repeatedly:
  Serial.print("Sensor 1: ");
  distance = getDistance(trigPin1, echoPin1);
  Serial.println(distance);
  delay(100);
//  Serial.print("Sensor 2: ");
//  Serial.println( getDistance(trigPin2, echoPin2) );
//  delay(100);
//  Serial.print("Sensor 3: ");
//  Serial.println( getDistance(trigPin3, echoPin3) );
//  delay(100);
//  Serial.print("Sensor 4: ");
//  Serial.println( getDistance(trigPin4, echoPin4) );
//  delay(100);

  if(distance <= distanceOld - humanheight) //human detected
  {
    //pause();
    Serial.print("Human!");
    play();
    //isPlaying = true;
  }
  //assume not automatically repeating tracks TO TEST
  
}// loop end

    
