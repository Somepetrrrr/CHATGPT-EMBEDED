#include <TimerOne.h>
#define led 8
volatile unsigned long cislo;

volatile unsigned long pocet = 0;
volatile bool stavLED = LOW;

volatile unsigned long  pomoc1 = 0;
volatile unsigned long  pomoc2 = 0;

volatile long frekvence = 0;



void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Timer1.initialize(0);

}
void loop() {
  if (Serial.available() > 0) {
  cislo = Serial.parseInt();
  Serial.println(cislo);
  pocet = cislo;
  
  if (pocet > 0 && pocet < 20) {
    frekvence = pocet;
    pomoc1 = 500000 / frekvence;
  Timer1.attachInterrupt(timer);
    Timer1.setPeriod(pomoc1);
    Serial.print("frekvence se změnila na ");
    Serial.print(frekvence);
    Serial.println(" Hz");
  }

  if(pocet >= 20 && pocet < 2000) {
    pomoc2 = pocet * 1000;
  Timer1.attachInterrupt(timer);
    Timer1.setPeriod(pomoc2);
    Serial.print("perioda se změnila na ");
    Serial.print(pomoc2/1000);
    Serial.println(" ms");

  }
 }

 
}

void timer() {
  stavLED = !stavLED;
  digitalWrite(led, stavLED);
}
