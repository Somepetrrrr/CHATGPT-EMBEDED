/*/*Vytvořte pole 10 čísel a naplňte jej čísly podle svého uvážení ("náhodná čísla").
Pomocí cyklu for vypište všechna čísla z pole nejprve od 0. po 9., pak od 9. po 0. a nakonec sečtěte všechna čísla v poli a výsledek vypište.
*/

int soucet = 0;
void setup() {
  Serial.begin(9600);
  int pole[10]={3,6,4,1,2,6,9,0,7,5};
  for (int i = 0; i < 10; i++){
    Serial.print(pole[i]);
    Serial.print(" ");
  }
  Serial.println();
   for (int i = 9; i >= 0; i--){
    Serial.print(pole[i]);
    Serial.print(" ");
}
  Serial.println();
    for (int i = 0; i < 10; i++){
      soucet += pole[i];  
    }
    Serial.println(soucet);


}

void loop() {

}
