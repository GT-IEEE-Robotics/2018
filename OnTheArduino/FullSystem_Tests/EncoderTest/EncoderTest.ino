////////////////////////
// DEFINE PINS
////////////////////////

// F = forward, B = backward
// R = right side, L = left side

#define FL_ENC_A (55)
#define FL_ENC_B (57)
#define FR_ENC_A (79)
#define FR_ENC_B (81)

#define BL_ENC_A (61)
#define BL_ENC_B (63)
#define BR_ENC_A (38)
#define BR_ENC_B (36)


#define FLAG_ENC_A (69)
#define FLAG_ENC_B (71)
#define DRAW_ENC_A (75)
#define DRAW_ENC_B (77)


////////////////////////
// ENCODER GLOBALS
////////////////////////
volatile int brCount = 0;
volatile int blCount = 0;
volatile int frCount = 0;
volatile int flCount = 0;
volatile int flagCount = 0;
volatile int drawCount = 0;


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

  attachInterrupt(digitalPinToInterrupt(FLAG_ENC_A), encoder_interrupt_flag, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FLAG_ENC_B), encoder_interrupt_flag, CHANGE);

  attachInterrupt(digitalPinToInterrupt(DRAW_ENC_A), encoder_interrupt_draw, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DRAW_ENC_B), encoder_interrupt_draw, CHANGE);
  
  stop_millis = millis() + TEST_TIME_MILLIS;
}

////////////////////////
// MAIN LOOP
////////////////////////
void loop() {

//  if (millis() <= stop_millis) {
//    Serial.print("br = ");
//    Serial.print(brCount);
//    
//    Serial.print(" bl = ");
//    Serial.print(blCount);
//    
//    Serial.print(" fr = ");
//    Serial.print(frCount);
//    
//    Serial.print(" fl = ");
//    Serial.print(flCount);
//    
//    Serial.print(" flag = ");
//    Serial.print(flagCount);

    Serial.print(" draw = ");
    Serial.print(drawCount);
    
    Serial.print("\n");
    delay(0.1);
//  }

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

// flagwheel motor encoder ISR
void encoder_interrupt_flag() {
  static uint8_t flag_enc_val = 0;
  flag_enc_val = (flag_enc_val << 2) | (digitalRead(FLAG_ENC_A) << 1) | digitalRead(FLAG_ENC_B);
  flagCount += encoder_table[flag_enc_val & 0b1111];
}

// drawbridge motor encoder ISR
void encoder_interrupt_draw() {
  static uint8_t draw_enc_val = 0;
  draw_enc_val = (draw_enc_val << 2) | (digitalRead(DRAW_ENC_A) << 1) | digitalRead(DRAW_ENC_B);
  drawCount += encoder_table[draw_enc_val & 0b1111];
}
