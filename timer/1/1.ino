/* Rozblikejte pomocí přerušení od časovače integrovanou LED frekvencí 2 Hz. */
#include <TimerOne.h>
int led = LED_BUILTIN;
int f = 2;
bool stavLed;



void setup() {
  pinMode(led, OUTPUT);
  Timer1.initialize(1000000 / f / 2);
  Timer1.attachInterrupt(blinkLED); 
  Serial.begin(9600);
}

void loop() {

}

void blinkLED(){
  stavLed = digitalRead(led);
  stavLed = !stavLed;
  digitalWrite (led, stavLed);
}
