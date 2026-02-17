

const int MotionPin = 7;
const int MotorPin = 13;
//setting names for the pins for activating the motion sensor and the motor
int MotionCount = 0;
//
int MotionSum = 0;
//creating variable for the output from the Motion sensor 
unsigned long TimeLog;
//creating a variable that will log the time at the start of the loop
unsigned long LoopTime = 0;
// creating a variable that logs the time whenever the motor stops moving after having been triggered by the motion sensor


void setup() {
  Serial.begin(9600);
  //setting the baud rate for serial data transmission allowing use of the serial monitor 
  pinMode(MotorPin, OUTPUT);
  //setting the pin for the motor to output mode
  pinMode(MotionPin, INPUT);
  //setting the pin for the motion sensor to input mode
  TimeLog = millis();
}

void loop() {
  // TimeLog = millis();
  //logging the current time to provide a baseline for the time counter 
  MotionSum = MotionSum + digitalRead(MotionPin);
  //adding the value of the MotionSum to the current signal from the motion sensor so then if there was any motion detected over the last 500 seconds then the motor will be triggered 
  MotionCount = MotionCount + 1;
  //setting the value of the motionCount to 1 to enable the if statement for the movement of the motor
  Serial.println(TimeLog);
  Serial.println(LoopTime);
  //printing the time values to the serial monitor for bug checking
  if (TimeLog >= LoopTime + 500) {
    //allowing the following if statment to be run every 500ms
    if (((MotionSum) / (MotionCount)) >= 0.001) {
      //checks if the motion sensor is detecting anything and if it is then proceedes to the following
      digitalWrite(MotorPin, 25);
      delay(750);
      digitalWrite(MotorPin, LOW);
      //powering the motor for 750ms using a pulse width moderation of 25 to slow the motor down before turning the motor off
      MotionCount = 0;
      //re
      MotionSum = 0;
      //resets the MotionSum value to 0 so it can restart the motion signal checking
      LoopTime = millis();
      //updating LoopTime so the process is triggered another 500ms later
    } else {
      LoopTime = millis();
      //updates LoopTime if no motion is detected so it will check if there was movement again in 500ms
      MotionCount = 0;
      //re
      MotionSum = 0;
      //resets the MotionSum value to 0 so it can restart the motion signal checking
    }
  }
}