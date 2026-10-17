#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "lahari407";
char pass[] = "***********";

// Sensor Pins
#define S1_PIN 34
#define S2_PIN 35
#define S3_PIN 32
#define S4_PIN 33

// Pulse counters
volatile int p1 = 0, p2 = 0, p3 = 0, p4 = 0;

// Flow values
float f1, f2, f3, f4;

// Thresholds
float MIN_FLOW = 0.3;     // ignore very small noise
float ABS_THRESHOLD = 1.0; // absolute difference
float PERCENT = 0.2;       // 20%

// Counters for time validation
int c1 = 0, c2 = 0;

// Interrupts
void IRAM_ATTR count1() { p1++; }
void IRAM_ATTR count2() { p2++; }
void IRAM_ATTR count3() { p3++; }
void IRAM_ATTR count4() { p4++; }

void setup() {
  Serial.begin(115200);

  pinMode(S1_PIN, INPUT);
  pinMode(S2_PIN, INPUT);
  pinMode(S3_PIN, INPUT);
  pinMode(S4_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(S1_PIN), count1, RISING);
  attachInterrupt(digitalPinToInterrupt(S2_PIN), count2, RISING);
  attachInterrupt(digitalPinToInterrupt(S3_PIN), count3, RISING);
  attachInterrupt(digitalPinToInterrupt(S4_PIN), count4, RISING);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  delay(1000); // 1 second window

  // Convert pulses → flow (adjust factor if needed)
  f1 = p1 * 0.1;
  f2 = p2 * 0.1;
  f3 = p3 * 0.1;
  f4 = p4 * 0.1;

  // Reset pulses
  p1 = p2 = p3 = p4 = 0;

  // Print values
  Serial.printf("S1: %.2f  S2: %.2f  S3: %.2f  S4: %.2f\n", f1, f2, f3, f4);

  // Send to Blynk
  Blynk.virtualWrite(V0, f1);
  Blynk.virtualWrite(V1, f2);
  Blynk.virtualWrite(V2, f3);
  Blynk.virtualWrite(V3, f4);

  // -------------------------
  // 🚨 LEAK DETECTION LOGIC
  // -------------------------

  // Ignore if no flow
  if (f1 < MIN_FLOW && f2 < MIN_FLOW && f3 < MIN_FLOW && f4 < MIN_FLOW) {
    c1 = c2 = 0;
    Serial.println("No flow - Idle");
    return;
  }

  // Segment 1
  float diff1 = f1 - f2;
  if (diff1 > ABS_THRESHOLD && diff1 > PERCENT * f1) {
    c1++;
  } else {
    c1 = 0;
  }

  // Segment 2
  float diff2 = f3 - f4;
  if (diff2 > ABS_THRESHOLD && diff2 > PERCENT * f3) {
    c2++;
  } else {
    c2 = 0;
  }

  // Confirm leak (after ~5 sec)
  if (c1 > 5) {
    Serial.println("🚨 Leak in Segment 1");
    Blynk.logEvent("leak_seg1", "Leak detected in Segment 1");
  }

  if (c2 > 5) {
    Serial.println("🚨 Leak in Segment 2");
    Blynk.logEvent("leak_seg2", "Leak detected in Segment 2");
  }

  // Normal case
  if (c1 == 0 && c2 == 0) {
    Serial.println("Normal usage");
  }
}