#define FL_ENC_A (24)
#define FL_ENC_B (26)

const int8_t table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

volatile int FL_count = 0;

// 3200 counts per revolution, 360 degrees per revolution. 360/3200 = 0.1125
#define DRIVE_WHEELS_COUNTS_TO_DEGREES (0.1125)


void setup() {
  Serial.begin(9600);
  attachInterrupt(FL_ENC_A, FL_isr, CHANGE);
  attachInterrupt(FL_ENC_B, FL_isr, CHANGE);
}
void loop () {
  Serial.println(FL_count*DRIVE_WHEELS_COUNTS_TO_DEGREES);
  delay(0.1);
}


void FL_isr() {
  static unsigned lastval = 0;
  lastval = (lastval << 2)|(digitalRead(FL_ENC_A)<<1)|(digitalRead(FL_ENC_B));
  FL_count += table[lastval & 15];
}

