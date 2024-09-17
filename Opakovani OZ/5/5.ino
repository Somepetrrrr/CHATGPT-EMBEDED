/*Pomocí millis() rozblikejte dvě LED připojené na piny D5 a D7 frekvencí 3 a 5 Hz.
Vždy, když se rozsvítí obě LED, vypište do konzole "sviti obe LED". Tuto skutečnost (že svítí obě LED) kontrolujte jen při změnách stavu LED.
Zároveň do vhodných proměnných ukládejte kolikrát se rozsvítila každá LED a jednou za 10 s tyto dvě hodnoty vypište.
*/
#define LED1 7
#define LED2 8 
byte frekvence1 = 1;
byte frekvence2 = 1;
bool StavLed1 = LOW;
bool StavLed2 = LOW;
unsigned long BlinkCounter1;
unsigned long BlinkCounter2;
unsigned long PosledniMillis;
unsigned long PosledniMillis1;
unsigned long PosledniMillis2;
void setup() {
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  if(millis() - PosledniMillis1 >= 1000 / frekvence1 / 2){
    PosledniMillis1 = millis();
    StavLed1 = !StavLed1;
    digitalWrite(LED1,StavLed1);
    if(StavLed1){
      BlinkCounter1 ++;
    }
    
  }
    if(millis() - PosledniMillis2 >= 1000 / frekvence2 / 2){
    PosledniMillis2 = millis();
    StavLed2 = !StavLed2;
    digitalWrite(LED2,StavLed2);
    if(StavLed2){
      BlinkCounter2 ++;
    }
    
  }
  /*uuuuuuuuuif(StavLed1 && StavLed2){
    Serial.println("sviti obe LED");
    delay(50);
  }
  */
  if(millis() - PosledniMillis >= 10000){
    PosledniMillis = millis();
    Serial.println(BlinkCounter1);
    Serial.println(BlinkCounter2);
  }
  

}