////////////////////////
// DEFINE PINS
////////////////////////

// F = forward, B = backward
// R = right side, L = left side

#define BR (8)
#define BR_CONTROL (52)
#define BL (9)
#define BL_CONTROL (50)
#define FR (10)
#define FR_CONTROL (48)
#define FL (11)
#define FL_CONTROL (46)

#define BR_ENC_A (38)
#define BR_ENC_B (36)
#define BL_ENC_A (32)
#define BL_ENC_B (34)
#define FR_ENC_A (26)
#define FR_ENC_B (28)
#define FL_ENC_A (40)
#define FL_ENC_B (42)


////////////////////////
// ENCODER GLOBALS
////////////////////////
volatile int brCount = 0;
volatile int brCountPrev = 0;
volatile int brRevs = 0;

volatile int blCount = 0;
volatile int blCountPrev = 0;
volatile int blRevs = 0;

volatile int frCount = 0;
volatile int frCountPrev = 0;
volatile int frRevs = 0;

volatile int flCount = 0;
volatile int flCountPrev = 0;
volatile int flRevs = 0;
const int8_t encoder_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

const uint32_t TEST_TIME_MILLIS = 200000;
uint32_t stop_millis = 0;


////////////////////////
// SETUP
////////////////////////
void setup() {
  // setup serial port
  Serial.begin(115200);

  // attach interrupts
  attachInterrupt(digitalPinToInterrupt(FL_ENC_A), encoder_interrupt_fl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FL_ENC_B), encoder_interrupt_fl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FR_ENC_A), encoder_interrupt_fr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FR_ENC_B), encoder_interrupt_fr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BL_ENC_A), encoder_interrupt_bl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BL_ENC_B), encoder_interrupt_bl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BR_ENC_A), encoder_interrupt_br, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BR_ENC_B), encoder_interrupt_br, CHANGE);
  stop_millis = millis() + TEST_TIME_MILLIS;
}

////////////////////////
// MAIN LOOP
////////////////////////
void loop() {

  if (millis() <= stop_millis) {
    Serial.print("br = ");
    Serial.print(brCount);
    Serial.print(" bl = ");
    Serial.print(blCount);
    Serial.print(" fr = ");
    Serial.print(frCount);
    Serial.print(" fl = ");
    Serial.print(flCount);
    Serial.print("\n");
  }

}


////////////////////////
// ENCODER INTERRUPTS
////////////////////////
void encoder_interrupt_br() {
  static uint8_t br_enc_val = 0;
  br_enc_val = (br_enc_val << 2) | (digitalRead(BR_ENC_A) << 1) | digitalRead(BR_ENC_B);
  brCount += encoder_table[br_enc_val & 0b1111];
}

void encoder_interrupt_bl() {
  static uint8_t bl_enc_val = 0;
  bl_enc_val = (bl_enc_val << 2) | (digitalRead(BL_ENC_A) << 1) | digitalRead(BL_ENC_B);
  blCount += encoder_table[bl_enc_val & 0b1111];
}

void encoder_interrupt_fr() {
  static uint8_t fr_enc_val = 0;
  fr_enc_val = (fr_enc_val << 2) | (digitalRead(FR_ENC_A) << 1) | digitalRead(FR_ENC_B);
  frCount += encoder_table[fr_enc_val & 0b1111];
}

void encoder_interrupt_fl() {
  static uint8_t fl_enc_val = 0;
  fl_enc_val = (fl_enc_val << 2) | (digitalRead(FL_ENC_A) << 1) | digitalRead(FL_ENC_B);
  flCount += encoder_table[fl_enc_val & 0b1111];
}
