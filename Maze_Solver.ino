const int trigPin1 = 2;   // front
const int echoPin1 = 3;

const int trigPin2 = 12;   // left
const int echoPin2 = 13;

const int trigPin3 = 4;  // right
const int echoPin3 = 7;

const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;

const int ENA = 5;   // PWM 
const int ENB = 6;   // PWM 

#define DIS          20    // detection distance (cm)
#define DRIVE_SPEED  90   // forward/reverse speed 
#define TURN_SPEED   120   // turning speed 
#define TURN_TIME    440   // ms for 90° turn — tune this


void setup() {

  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);

  stop();
  delay(3000);
}

void loop() {

  long f = FrontSensor(); delay(30);
  long l = LeftSensor();  delay(30);
  long r = RightSensor(); delay(30);

  if (f == 999) f = 100;
  if (l == 999) l = 100;
  if (r == 999) r = 100;

  Serial.print("F: "); Serial.print(f);
  Serial.print("  L: "); Serial.print(l);
  Serial.print("  R: "); Serial.println(r);

  if (f > DIS && r > DIS && l > DIS) {
    forward();
  }

  // ALL BLOCKED → reverse then turn to wider side
  else if (f < DIS && r < DIS && l < DIS) {
    stop();
    delay(250);
    reverse();
    delay(500);
    stop();
    delay(250);
    if (l > r)
      turn_left();
    else
      turn_right();
  }

  // FRONT + RIGHT BLOCKED → turn left
  else if (f < DIS && r < DIS && l > DIS) {
    stop();
    delay(250);
    turn_left();
  }

  // FRONT + LEFT BLOCKED → turn right
  else if (f < DIS && r > DIS && l < DIS) {
    stop();
    delay(250);
    turn_right();
  }

  // FRONT BLOCKED ONLY → turn left (left hand rule)
  else if (f < DIS && r > DIS && l > DIS) {
    stop();
    delay(250);
    turn_left();
    delay(300);
    forward();
  }

  // LEFT BLOCKED ONLY → go straight
  else if (f > DIS && r > DIS && l < DIS) {
    forward();
  }

  // RIGHT BLOCKED ONLY → go straight
  else if (f > DIS && r < DIS && l > DIS) {
    forward();
  }

  else {
    forward();
  }
}



void forward() {
  analogWrite(ENA, DRIVE_SPEED);
  analogWrite(ENB, DRIVE_SPEED);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void reverse() {
  analogWrite(ENA, DRIVE_SPEED);
  analogWrite(ENB, DRIVE_SPEED);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turn_left() {
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(TURN_TIME);
  stop();
  delay(250);
}

void turn_right() {
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(TURN_TIME);
  stop();
  delay(250);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


long FrontSensor() {
  long dur;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  dur = pulseIn(echoPin1, HIGH, 30000);
  if (dur == 0) return 999;
  return (dur / 58);
}

long LeftSensor() {
  long dur;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  dur = pulseIn(echoPin2, HIGH, 30000);
  if (dur == 0) return 999;
  return (dur / 58);
}

long RightSensor() {
  long dur;
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  dur = pulseIn(echoPin3, HIGH, 30000);
  if (dur == 0) return 999;
  return (dur / 58);
}