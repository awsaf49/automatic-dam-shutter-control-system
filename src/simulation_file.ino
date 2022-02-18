// define constants
const byte echoPin = 2; // attach pin D2 Arduino to pin Echo of HC-SR04
const byte trigPin = 3; //attach pin D3 Arduino to pin Trig of HC-SR04
const byte motorPin1 = 6; //motor pin 1
const byte motorPin2 = 7; //motor pin 2
  
const unsigned long heightDam = 200; //height of the dam in cm
const unsigned long openHeight = 100; //height to open the gate
const unsigned long closeHeight = 50; //height to close the gate

const unsigned long openTime = 500;  //time to open gate in ms
const unsigned long closeTime = 300; //time to close gate in ms

const double windSpeed = 0.034; // speed of wind cm/us

//defines variables
long duration; //variable for the duration of sound wave travel
int distance; //variable for the distance measurement

float openTik = -1;
float openTok = -1;

float closeTik = -1;
float closeTok = -1;

bool isOpen = false; //gate is open or not

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * windSpeed / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  // Motor
  if(distance>=openHeight){
    if (openTik==-1){
      openTik = millis();
    }
    openTok = millis();
    if (openTok - openTik < openTime){
      open();
      isOpen = true;
    }
    else{
      stop();
      openTik = -1;
      openTok = -1;
    }
  }
  else if(distance<=closeHeight && isOpen){
    if (closeTik==-1){
      closeTik = millis();
    }
    closeTok = millis();
    if (closeTok - closeTik < closeTime){
      close();
    }
    else{
      stop();
      closeTik = -1;
      closeTok = -1;
      isOpen = false;
    }
  }
  else{
    stop();
    openTik = -1;
    openTok = -1;
    closeTik = -1;
    closeTok = -1;
  }
}

void open(){
  digitalWrite(motorPin1,HIGH);
  digitalWrite(motorPin2,LOW);
}

void close(){
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,HIGH);
}

void stop(){
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
}
                   
               
