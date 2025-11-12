const int MotionPin = 7;
const int MotorPin = 13;
int MotionCount = 0;
int MotionSum = 0;
unsigned long TimeLog;
unsigned long LoopTime = 0;
unsigned long DelayTime;

void setup() {
  Serial.begin(9600);
  pinMode(MotorPin, OUTPUT);
  pinMode(MotionPin, INPUT);

  DelayTime = 1000;
}

void loop() {
  TimeLog = millis();
  MotionSum = MotionSum + digitalRead(MotionPin);
  MotionCount = MotionCount + 1;
  Serial.println(TimeLog);
  Serial.println(LoopTime);
  if (TimeLog >= LoopTime + 500) {
    if (((MotionSum) / (MotionCount)) >= 0.001) {
      digitalWrite(MotorPin, HIGH);
      delay(750);
      digitalWrite(MotorPin, LOW);
      MotionCount = 0;
      MotionSum = 0;
      LoopTime = millis();
    } else {
      LoopTime = millis();
      MotionCount = 0;
      MotionSum = 0;
    }
  }
}