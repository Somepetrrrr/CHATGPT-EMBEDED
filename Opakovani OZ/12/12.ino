/*Pomocí dvou vnořených for cyklů (cyklus uvnitř cyklu) od 1 do 10 vypište malou násobilku jako 10 x 10 čísel. 
První řádek bude tedy obsahovat "1 2 3 ... 9 10", druhý řádek "2 4 6 ... 18 20", ... a 10. řádek "10 20 30 ... 90 100".
*/

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i=1; i<=10; i++){
  for(int j=1; j<=10; j++){
    Serial.print(i*j);
    Serial.print("\t");
  }
  Serial.println();
  }
}
