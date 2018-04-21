#define FL_DIR (34) 
#define BL_DIR (28)
#define FR_DIR (22)
#define BR_DIR (51)

#define FL_SPD (4)
#define BL_SPD (3)
#define FR_SPD (2)
#define BR_SPD (5)




void setup() {
  Serial.begin(9600);
  
  pinMode(FL_DIR,OUTPUT);
  pinMode(BL_DIR,OUTPUT);
  pinMode(FR_DIR,OUTPUT);
  pinMode(BR_DIR,OUTPUT);

  pinMode(FL_SPD,OUTPUT);
  pinMode(BL_SPD,OUTPUT);
  pinMode(FR_SPD,OUTPUT);
  pinMode(BR_SPD,OUTPUT);
}

void loop() {
  digitalWrite(FL_DIR, LOW);
  //digitalWrite(BL_DIR, LOW);  
  //digitalWrite(FR_DIR, LOW);
  //digitalWrite(BR_DIR, LOW);

  Serial.println("FL"); analogWrite(FL_SPD, 150); delay(500); analogWrite(FL_SPD, 0);delay(1000);   
  digitalWrite(FL_DIR, HIGH);
  Serial.println("FL"); analogWrite(FL_SPD, 150); delay(500); analogWrite(FL_SPD, 0);delay(1000);   
  
  //Serial.println("BL"); analogWrite(BL_SPD, 150); delay(500); analogWrite(BL_SPD, 0);delay(1000);
  //Serial.println("FR"); analogWrite(FR_SPD, 150); delay(500); analogWrite(FR_SPD, 0);delay(1000);
  //Serial.println("BR"); analogWrite(BR_SPD, 150); delay(500); analogWrite(BR_SPD, 0);delay(1000);


  delay(1000);
  
  


}
