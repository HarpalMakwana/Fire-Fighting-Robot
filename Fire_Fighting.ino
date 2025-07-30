/************************************************************************************************
🔷 Project: Smart Fire Fighting Robot                                                            *
👨‍💻 Developer: Harpal Makwana - Future Science Hub                                              *
📞 Contact: +91 9313758130                                                                       *
📺 YouTube: Future Science Hub                                                                   *
📸 Instagram: @future_science_hub                                                                *
*************************************************************************************************/

// ========== PIN DEFINITIONS ==========
#define enA 10     // Right Motor Speed Control (ENA)
#define in1 9      // Right Motor - IN1
#define in2 8      // Right Motor - IN2
#define in3 7      // Left Motor  - IN3
#define in4 6      // Left Motor  - IN4
#define enB 5      // Left Motor Speed Control (ENB)

#define ir_R A0    // Right IR Sensor
#define ir_F A1    // Front IR Sensor
#define ir_L A2    // Left IR Sensor

#define servo A4   // Servo Signal Pin
#define pump A5    // Water Pump Control

int Speed = 160;  // Motor speed (PWM 0–255)
int s1, s2, s3;   // Sensor readings

// ========== SETUP ==========
void setup() {
  Serial.begin(9600);

  pinMode(ir_R, INPUT);
  pinMode(ir_F, INPUT);
  pinMode(ir_L, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(servo, OUTPUT);
  pinMode(pump, OUTPUT);

  // Initial Servo Sweep
  for (int angle = 90; angle <= 140; angle += 5) servoPulse(servo, angle);
  for (int angle = 140; angle >= 40; angle -= 5) servoPulse(servo, angle);
  for (int angle = 40; angle <= 95; angle += 5)  servoPulse(servo, angle);

  // Motor speed setup
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);

  delay(500);
}

// ========== MAIN LOOP ==========
void loop() {
  s1 = analogRead(ir_R);
  s2 = analogRead(ir_F);
  s3 = analogRead(ir_L);

  // Debug Sensor Values
  Serial.print(s1); Serial.print("\t");
  Serial.print(s2); Serial.print("\t");
  Serial.println(s3);
  delay(50);

  // 🔥 Fire Detected on Right
  if (s1 < 250) {
    Stop();
    digitalWrite(pump, HIGH);
    for (int angle = 90; angle >= 40; angle -= 3) servoPulse(servo, angle);
    for (int angle = 40; angle <= 90; angle += 3) servoPulse(servo, angle);
  }

  // 🔥 Fire Detected in Front
  else if (s2 < 350) {
    Stop();
    digitalWrite(pump, HIGH);
    for (int angle = 90; angle <= 140; angle += 3) servoPulse(servo, angle);
    for (int angle = 140; angle >= 40; angle -= 3) servoPulse(servo, angle);
    for (int angle = 40; angle <= 90; angle += 3) servoPulse(servo, angle);
  }

  // 🔥 Fire Detected on Left
  else if (s3 < 250) {
    Stop();
    digitalWrite(pump, HIGH);
    for (int angle = 90; angle <= 140; angle += 3) servoPulse(servo, angle);
    for (int angle = 140; angle >= 90; angle -= 3) servoPulse(servo, angle);
  }

  // 🔁 Navigation Logic
  else if (s1 >= 251 && s1 <= 700) {
    digitalWrite(pump, LOW);
    backword(); delay(100);
    turnRight(); delay(200);
  }
  else if (s2 >= 251 && s2 <= 800) {
    digitalWrite(pump, LOW);
    forword();
  }
  else if (s3 >= 251 && s3 <= 700) {
    digitalWrite(pump, LOW);
    backword(); delay(100);
    turnLeft(); delay(200);
  }
  else {
    digitalWrite(pump, LOW);
    Stop();
  }

  delay(10);
}

// ========== SERVO FUNCTION ==========
void servoPulse(int pin, int angle) {
  int pwm = (angle * 11) + 500;
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50);
}

// ========== MOVEMENT FUNCTIONS ==========
void forword() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
}

void backword() {
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void Stop() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}
