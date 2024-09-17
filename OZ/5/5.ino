/* Pomocí millis() rozblikejte dvě LED připojené na piny D5 a D7 frekvencí 3 a 5 Hz.
Vždy, když se rozsvítí obě LED, vypište do konzole "sviti obe LED". Tuto skutečnost (že svítí obě LED) kontrolujte jen při změnách stavu LED.
Zároveň do vhodných proměnných ukládejte kolikrát se rozsvítila každá LED a jednou za 10 s tyto dvě hodnoty vypište.
*/
#define LED1 5
#define LED2 7

int frekvence1 = 3;  
int frekvence2 = 5;  

unsigned long predchoziMillis1 = 0;
unsigned long predchoziMillis2 = 0;
unsigned long posledniVypis = 0;

unsigned long interval1 = 1000 / frekvence1 / 2;
unsigned long interval2 = 1000 / frekvence2 / 2;
unsigned long intervalVypis = 10000;

int blik1 = 0;
int blik2 = 0;

bool StavLed1 = LOW;
bool StavLed2 = LOW;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(millis() - predchoziMillis1 >= interval1){
    predchoziMillis1 = millis();
    StavLed1 = !StavLed1;
    digitalWrite(LED1, StavLed1);
    if(StavLed1){
      blik1++;
    }
  }
  if(millis() - predchoziMillis2 >= interval2){
    predchoziMillis2 = millis();
    StavLed2 = !StavLed2;
    digitalWrite(LED2, StavLed2);
    if(StavLed2){
      blik2++;
  }
  }
  if(StavLed1&&StavLed2){
    Serial.println("SVITEJ OBE TY KRIPLE");
  }
  if(millis() - posledniVypis >= intervalVypis ){
    posledniVypis = millis();
    Serial.println(blik1);
    Serial.println(blik2);
  }
}
