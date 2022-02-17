#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define heightDam 200 //height of the dam in cm
#define motorPin1 6 //motor pin 1
#define motorPin2 7 //motor pin 2

const unsigned long openTime = 1000;  //time to open gate in ms
const unsigned long closeTime = 900; //time to close gate in ms

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

unsigned long openTik = 0;
unsigned long openTok = 0;

unsigned long closeTik = 0;
unsigned long closeTok = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
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
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  // Motor
  if(distance>=100.0){
    if (openTik==0){
      openTik = millis();
    }
    openTok = millis();
    if (openTok - openTik < openTime){
      open();
    }
    else{
      stop();
      openTik = 0;
      openTok = 0;
    }
  }
  else if(distance<50.0){
    if (closeTik==0){
      closeTik = millis();
    }
    closeTok = millis();
    if (closeTok - closeTik < closeTime){
      close();
    }
    else{
      stop();
      closeTik = 0;
      closeTok = 0;
    }
  }
  else{
    stop();
    openTik = 0;
    openTok = 0;
    closeTik = 0;
    closeTok = 0;
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
                   
               
