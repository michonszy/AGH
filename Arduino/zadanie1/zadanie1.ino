#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
//LABY 2

void setup() {
  lcd.begin(16,2);
  pinMode(7,OUTPUT); digitalWrite(7,HIGH); //podświetlenie wyświetlacza
  pinMode(A0,INPUT_PULLUP); //ustawianie godzin
  pinMode(A1,INPUT_PULLUP); //ustawianie minut
  pinMode(A2,INPUT_PULLUP); //ustawianie czas lub alarm
  //lcd.print("Systemy");
  //lcd.setCursor(0,1);
  //lcd.print("Wbudowane");

}

byte h=0; byte m=0; byte s=0; byte alarm_h=1; byte alarm_m = 1;
unsigned long prev=millis();
void loop() {
  if(millis() -prev>1000){
    prev=millis();
    s++;
      //tutaj jest dobre miejsce na ustawienie czasu i alarmu
    if (s>=60){
      s=0; m++;
    }
    if (m>=60){
      m=0; h++;
    }
    if (h>=24){
      h=0;
    }

    //obsluga alarmu
    //alarm gdy zbiegnie się wartośc alarmu z wartością na ekranie za pomocą mignięcia digitalWrite 7
    //przycisk A0 do godzin, A1 do minut, A2 jak jest nie wciśnięty do 2 ustawiają godzinę, jak wciśnięty ustawiają alarm

    if(!digitalRead(A2)){
          if(!digitalRead(A0)){ 
              alarm_h++;
          }
          if(!digitalRead(A1)){
            alarm_m++;
          }
    }else{
          if(!digitalRead(A0)){ 
              h++;
          }
          if(!digitalRead(A1)){
            m++;
          }
    }

    if(h==alarm_h && m==alarm_m){
        digitalWrite(7,!digitalRead(7)); //mam nadzieję że o to chodziło analogicznie do ostatnich labów
    }

    lcd.clear(); lcd.print(h);lcd.print(":");lcd.print(m);lcd.print(":");lcd.print(s);
    lcd.setCursor(0,1);
    lcd.print(alarm_h); lcd.print(":"); lcd.print(alarm_m);
  }

}
