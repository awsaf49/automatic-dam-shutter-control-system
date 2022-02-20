/*
Algorithm:
1) Get distance of water from and convert distance to height.
2) If the height of water is too high (heightWater>heighOpen) start opening the gate (start the motor).
3) Once enough time has passed (openTok - openTik > openTime) stop opening the gate (stop the motor).
4) If the height is neither too high nor too low (heightClose<heightWater<heightOpen) keep the motor off.
5) If gate is open(isOpen=true) and height of the water is too low (heightWater<heightClose) start closing nthe gate (start the motor in oposite direction).
6) Once enough time has passed (closeTok - closeTik > closeTime) stop closing the gate (stop the motor).

Total States: 4
1. Opening
2. Opened
3. Closing
4. Closed

Caution:
1. Keep heightClose & heightOpen value close.
2. Keep heightClose > minimum water height when gate is open.

*/

// define constants
const byte echoPin = 2; // attach pin D2 Arduino to pin Echo of HC-SR04
const byte trigPin = 3; //attach pin D3 Arduino to pin Trig of HC-SR04
const byte motorPin1 = 6; //motor pin 1
const byte motorPin2 = 7; //motor pin 2
  
const unsigned long damHeight = 27; //height of the dam in cm
const unsigned long openHeight = 16; //height to open the gate
const unsigned long closeHeight = 13; //height to close the gate

const unsigned long openTime = 500;  //time to open gate in ms
const unsigned long closeTime = 300; //time to close gate in ms

const double windSpeed = 0.034; // speed of wind cm/us

//defines variables
long duration; //variable for the duration of sound wave travel
int distance; //variable for the distance measurement

float openTik = -1; // Stopwatch for Openening gate
float openTok = -1;

float closeTik = -1; // Stopwatch for Closing gate
float closeTok = -1;

bool isOpen = false; // Flag for gate is open or not

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(motorPin1, OUTPUT); // Sets the motorPin1 as OUTPUT
  pinMode(motorPin2, OUTPUT); // SETS the motorPin2 as OUTPUT
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Automatic Dam Shutter Control:"); // print some text in Serial Monitor
  // Serial.println("with Arduino UNO R3");
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
  
  // Find height of the water from base  
  unsigned long waterHeight = damHeight - distance; // Height of water from base
  // Displays the height on the Serial Monitor
  Serial.print("Height: ");
  Serial.print(waterHeight);
  Serial.println(" cm");
  
  // Motor Control
  if(waterHeight>=openHeight){
    if (openTik==-1){
      openTik = millis(); // Record start of the event
    }
    openTok = millis(); // Record passed time of the event
    if (openTok - openTik < openTime){
      open(); // Keep opening the gate if enough time hasn't passed
      isOpen = true; // Flag to remember if the gate is open or not
    }
    else{
      stop(); // Stop opening the gate
      openTik = -1; // Reset the stopwatch
      openTok = -1; // Reset the stopwatch
    }
  }
  else if(waterHeight<=closeHeight && isOpen){
    if (closeTik==-1){
      closeTik = millis(); // Record start of the event
    }
    closeTok = millis(); // Record passed time of the event
    if (closeTok - closeTik < closeTime){
      close(); // Close the gate if enough time hasn't passed
    }
    else{
      stop();
      closeTik = -1; // Reset the stopwatch
      closeTok = -1; // Reset the stopwatch
      isOpen = false; // Flag to remember that gate is closed
    }
  }
  else{
    stop(); // Stop closing the gate
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
                   
               
