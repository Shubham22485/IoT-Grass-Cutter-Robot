// ================================================================
//   Automatic Grass Cutter Robot
//   Board  : Arduino UNO R3
//   Shield : HW-130 (L293D) Motor Driver Shield
// ================================================================
//   LIBRARY REQUIRED:
//   Sketch → Include Library → Manage Libraries
//   Search: "AFMotor" by Adafruit → Install
// ================================================================

#include <AFMotor.h>
#include <Servo.h>

// ── DC Motors ────────────────────────────────────────────────────
AF_DCMotor motorFL(1);   // Front-Left  → M1
AF_DCMotor motorFR(2);   // Front-Right → M2
AF_DCMotor motorRL(3);   // Rear-Left   → M3
AF_DCMotor motorRR(4);   // Rear-Right  → M4

// ── Servo (Blade Height Control) ─────────────────────────────────
Servo heightServo;
#define SERVO_PIN     10   // Servo header on shield

// ── Ultrasonic Sensor ─────────────────────────────────────────────
#define TRIG_PIN      2
#define ECHO_PIN      3

// ── Tunable Settings ─────────────────────────────────────────────
#define MOTOR_SPEED     180   // Drive speed (0–255)
#define OBSTACLE_DIST    25   // Stop if obstacle < 25 cm
#define BLADE_DOWN       45   // Servo angle → blade lowered (cutting)
#define BLADE_UP         90   // Servo angle → blade raised (safe)

// =================================================================
//  UTILITY — Read Distance from HC-SR04
// =================================================================
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30 ms
  long cm = duration * 0.034 / 2;
  return cm;
}

// =================================================================
//  MOTOR COMMANDS
// =================================================================
void setSpeed(int spd) {
  motorFL.setSpeed(spd);
  motorFR.setSpeed(spd);
  motorRL.setSpeed(spd);
  motorRR.setSpeed(spd);
}

void moveForward() {
  motorFL.run(FORWARD);
  motorFR.run(FORWARD);
  motorRL.run(FORWARD);
  motorRR.run(FORWARD);
}

void moveBackward() {
  motorFL.run(BACKWARD);
  motorFR.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorRR.run(BACKWARD);
}

void turnRight() {
  // Left wheels forward, right wheels backward
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
  motorFR.run(BACKWARD);
  motorRR.run(BACKWARD);
}

void turnLeft() {
  // Right wheels forward, left wheels backward
  motorFR.run(FORWARD);
  motorRR.run(FORWARD);
  motorFL.run(BACKWARD);
  motorRL.run(BACKWARD);
}

void stopMotors() {
  motorFL.run(RELEASE);
  motorFR.run(RELEASE);
  motorRL.run(RELEASE);
  motorRR.run(RELEASE);
}

// =================================================================
//  SETUP
// =================================================================
void setup() {
  Serial.begin(9600);

  // Ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Servo — raise blade first for safety
  heightServo.attach(SERVO_PIN);
  heightServo.write(BLADE_UP);
  delay(500);

  // Set drive speed
  setSpeed(MOTOR_SPEED);

  Serial.println("=== Grass Cutter Robot Ready ===");
  Serial.println("Starting in 3 seconds...");
  delay(3000);

  // Lower blade — begin cutting
  heightServo.write(BLADE_DOWN);
  delay(500);
  Serial.println("Blade lowered. Moving...");
}

// =================================================================
//  MAIN LOOP
// =================================================================
void loop() {
  long dist = getDistance();

  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  // ── Obstacle Detected ──────────────────────────────────────────
  if (dist > 0 && dist < OBSTACLE_DIST) {
    Serial.println("⚠ Obstacle! Avoiding...");

    // 1. Raise blade immediately for safety
    heightServo.write(BLADE_UP);

    // 2. Stop
    stopMotors();
    delay(300);

    // 3. Reverse
    moveBackward();
    delay(600);
    stopMotors();
    delay(200);

    // 4. Turn right to avoid obstacle
    turnRight();
    delay(500);          // increase this if not turning enough
    stopMotors();
    delay(200);

    // 5. Resume — lower blade and go forward
    heightServo.write(BLADE_DOWN);
    delay(300);
    Serial.println("Obstacle avoided. Resuming...");
  }

  // ── Clear Path — Move & Cut ────────────────────────────────────
  else {
    moveForward();
  }

  delay(100); // loop refresh rate
}