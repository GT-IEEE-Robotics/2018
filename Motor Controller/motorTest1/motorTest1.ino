
int STBY = 19; //standby

//Motor A
int PWMA = 8; //Speed control 
int AIN1 = 20; //Direction
int AIN2 = 21; //Direction


void setup(){
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

}

void loop(){
  move(1, 255, 1); //motor 1, full speed, left

  delay(5000); //go for 1 second
  stop(); //stop
  delay(250); //hold for 250ms until move again

  move(1, 255, 0); //motor 1, full speed, right

  delay(5000);
  stop();
  delay(250);
}


void move(int motor, int speed, int direction){
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}
