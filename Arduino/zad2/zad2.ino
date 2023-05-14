#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define RESET 2

///Poprzednie piny zostały pobrane z PDF z zadaniem gdzie podane są na sztywno stąd mój wcześniejszy błąd
void setup() {
  Serial.begin(9600); 
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  //attachInterrupt(0,reset,LOW); //usunięty interupt z powodu innej metody resetowania 
}
byte licz=0;
void reset(){
  licz=0;
}
unsigned long prev=0;
void loop() {
  
if(millis()-prev>500){
  Serial.println(licz);
  digitalWrite(LED1,bitRead(licz,0));
  digitalWrite(LED2,bitRead(licz,0));
  digitalWrite(LED3,bitRead(licz,0));
  digitalWrite(LED4,bitRead(licz,0));
  prev=millis();
  licz++;
}
if(digitalRead(RESET) == LOW) //nowa metoda resetowania
  {
    licz = 0;
  }

}
