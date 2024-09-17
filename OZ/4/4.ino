/*Deklarujte prom. "citac" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100000.
Pomocí millis() každých 150 ms zvyšujte hodnotu proměnné "citac" o 1.
Pokud bude hodnota prom. "citac" násobkem 7 nebo 19, vypište do konzole "7 nebo 19". Použijte jeden podmíněný příkaz (if) se složenou podmínkou.
Pokud prom. "citac" nesplní výše uvedenou podmínku, nevypíšete nic.
*/
unsigned long citac;
unsigned long PosledniMillis;


void setup() {
  Serial.begin(9600);

}

void loop() {
if(millis() - PosledniMillis >= 150){
  PosledniMillis = millis();
  citac++;
  if(citac % 7 == 0 || citac % 19 == 0){
    Serial.println("7 nebo 19");
  }
}
}
