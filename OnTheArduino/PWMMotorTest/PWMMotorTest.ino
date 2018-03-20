void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(52,OUTPUT);
}

void loop() {
  digitalWrite(46,LOW);
  analogWrite(8, 150);
  delay(500);
  analogWrite(8, 0);
  delay(100);
  digitalWrite(46, HIGH);
  analogWrite(8, 150);
  delay(500);
  analogWrite(8, 0);
  delay(100);


  digitalWrite(48,LOW);
  analogWrite(9, 150);
  delay(500);
  analogWrite(9, 0);
  delay(100);
  digitalWrite(48, HIGH);
  analogWrite(9, 150);
  delay(500);
  analogWrite(9, 0);
  delay(100);


  digitalWrite(50,LOW);
  analogWrite(10, 150);
  delay(500);
  analogWrite(10, 0);
  delay(100);
  digitalWrite(50, HIGH);
  analogWrite(10, 150);
  delay(500);
  analogWrite(10, 0);
  delay(100);


  digitalWrite(52,LOW);
  analogWrite(11, 150);
  delay(500);
  analogWrite(11, 0);
  delay(100);
  digitalWrite(52, HIGH);
  analogWrite(11, 150);
  delay(500);
  analogWrite(11, 0);
  delay(100);
}
