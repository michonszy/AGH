int power = 1;
int power2 = 2;
void setup(){
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  analogWrite(11,50);
  analogWrite(10,50);
  
}

void loop(){
    power=Serial.parseInt() *2,55;
    power2=Serial.parseInt() *2,55;

    analogWrite(11,power);
    analogWrite(10,power2);
    if(power>0){
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(3000);
    }else{
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      delay(3000);
    }
    if(power2>0){
      digitalWrite(6,HIGH);
      digitalWrite(5,LOW);
      delay(3000);
    }else{
      digitalWrite(6,LOW);
      digitalWrite(5,HIGH);
      delay(3000);
    }


}
