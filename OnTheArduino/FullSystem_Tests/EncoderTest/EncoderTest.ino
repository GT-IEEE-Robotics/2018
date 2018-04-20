////////////////////////////////
// DEFINE ENCODER PINS
////////////////////////////////

#define FL_ENC_A (24)
#define FL_ENC_B (26)

#define FR_ENC_A (48)
#define FR_ENC_B (50)

#define BL_ENC_A (30)
#define BL_ENC_B (32)

#define BR_ENC_A (52)
#define BR_ENC_B (53)

#define FLAG_ENC_A (38)
#define FLAG_ENC_B (40)

#define DRAW_ENC_A (44)
#define DRAW_ENC_B (46)


////////////////////////////////
// GLOBALS FOR ENCODER COUNTS
////////////////////////////////

volatile int FL_count = 0;
volatile int FR_count = 0;

volatile int BL_count = 0;
volatile int BR_count = 0;

volatile int FLAG_count = 0;
volatile int DRAW_count = 0;

// LOOKUP TABLE FOR QUADRATURE ENCODER STATE MACHINE
const int8_t table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

////////////////////////////////
// COUNTS TO DEGREES CONVERSION
////////////////////////////////

// 3200 counts per revolution, 360 degrees per revolution. 360/3200 = 0.1125
#define DRIVE_WHEELS_COUNTS_TO_DEGREES (0.1125)

// I don't actually know these so just set them same until we find out?
#define SOME_WHEELS_COUNTS_TO_DEGREES (0.1125)

////////////////////////////////
// SETUP
////////////////////////////////
void setup() {
  Serial.begin(9600);
  attachInterrupt(FL_ENC_A, FL_isr, CHANGE);
  attachInterrupt(FL_ENC_B, FL_isr, CHANGE);
  attachInterrupt(FR_ENC_A, FR_isr, CHANGE);
  attachInterrupt(FR_ENC_B, FR_isr, CHANGE);
  
  attachInterrupt(BL_ENC_A, BL_isr, CHANGE);
  attachInterrupt(BL_ENC_B, BL_isr, CHANGE);
  attachInterrupt(BR_ENC_A, BR_isr, CHANGE);
  attachInterrupt(BR_ENC_B, BR_isr, CHANGE);

  attachInterrupt(FLAG_ENC_A, FLAG_isr, CHANGE);
  attachInterrupt(FLAG_ENC_B, FLAG_isr, CHANGE);
  attachInterrupt(DRAW_ENC_A, DRAW_isr, CHANGE);
  attachInterrupt(DRAW_ENC_B, DRAW_isr, CHANGE);
  
}

////////////////////////////////
// LOOP
////////////////////////////////
void loop () {
  Serial.print(FL_count*DRIVE_WHEELS_COUNTS_TO_DEGREES); Serial.print(" ");
  Serial.print(FR_count*DRIVE_WHEELS_COUNTS_TO_DEGREES); Serial.print(" ");
  Serial.print(BL_count*DRIVE_WHEELS_COUNTS_TO_DEGREES); Serial.print(" ");
  Serial.print(BR_count*DRIVE_WHEELS_COUNTS_TO_DEGREES); Serial.print(" ");
  Serial.print(FLAG_count*SOME_WHEELS_COUNTS_TO_DEGREES); Serial.print(" ");
  Serial.print(DRAW_count*SOME_WHEELS_COUNTS_TO_DEGREES); Serial.print(" ");
  Serial.println();
  delay(0.1);
}

////////////////////////////////
// ISRs
////////////////////////////////
void FL_isr() {
  static unsigned lastval = 0;
  lastval = (lastval << 2)|(digitalRead(FL_ENC_A)<<1)|(digitalRead(FL_ENC_B));
  FL_count += table[lastval & 15];
}
void FR_isr() {
  static unsigned lastval = 0;
  lastval = (lastval << 2)|(digitalRead(FR_ENC_A)<<1)|(digitalRead(FR_ENC_B));
  FR_count += table[lastval & 15];
}
void BL_isr() {
  static unsigned lastval = 0;
  lastval = (lastval << 2)|(digitalRead(BL_ENC_A)<<1)|(digitalRead(BL_ENC_B));
  BL_count += table[lastval & 15];
}
void BR_isr() {
  static unsigned lastval = 0;
  lastval = (lastval << 2)|(digitalRead(BR_ENC_A)<<1)|(digitalRead(BR_ENC_B));
  BR_count += table[lastval & 15];
}
void FLAG_isr() {
  static unsigned lastval = 0;
  lastval = (lastval << 2)|(digitalRead(FLAG_ENC_A)<<1)|(digitalRead(FLAG_ENC_B));
  FLAG_count += table[lastval & 15];
}
void DRAW_isr() {
  static unsigned lastval = 0;
  lastval = (lastval << 2)|(digitalRead(DRAW_ENC_A)<<1)|(digitalRead(DRAW_ENC_B));
  DRAW_count += table[lastval & 15];
}





