//#define DEBUG //definicja debuga
#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11 //definicja podpiętych ledów
void setup() {
  //wysyłanie danych tekstowych
  Serial.begin(9600); //uruchomienie portu szeregowego
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(2,INPUT_PULLUP); //na pin 2 podpinamy podpięty do masy przycisk
  attachInterrupt(0,reset,LOW); //przycisk resetuje na LOW
}
char buf[100];
byte licz=0;

void reset(){
  licz=0;
}
unsigned long prev=0;
void loop() {

  //odczytywanie danych, zawsze upewniamy się że mamy co odczytać
  //if(Serial.avaiable())
  //{
    //Serial.readByte(buf,10); //odczytanie 10 znaków z buf
    //int odczyt=Serial.parseInt(); //zadanie 3
    //#ifdef DEBUG //debugowanie
    licz++;
    //Serial.print("Ilosc odebranych danych: ");
   // Serial.print(licz);
   //Serial.print("Dane: :);
    //#endif //koniec ifa debuga
   // Serial.println(odczyt);
 // }
  //Serial.println("Hello World");
  digitalWrite(LED1,!digitalRead(LED1)); //miganie diody
  digitalWrite(LED1,HIGH);
  delay(1000);
  digitalWrite(LED1,LOW); //alternatywne do pierwszego sposobu migania diody

  //if (Serial.avaiable()){
  //  int k=Serial.parseInt();
  //  Serial.println(k,BIN);
  //  digitalWrite(LED1,bitRead(k,0));
  //  
  //} //świecenie w zależności od podanego bitu
  ////////////////FUNKCJA DO OMINIĘCIA PRZERWANIA////////////////////
if(milis()-prev>1000){
  prev=milis();
  licz++;
  Serial.println(licz);
}
/////////////////////////////////////////////////////////////////////////
  /////////////////licznik////////////////////
  if(!digitalRead(2)){
    reset();
  }
  ////////////////////////////////////////////
  licz++;
  Serial.println(licz);
  
  delay(500);

}
