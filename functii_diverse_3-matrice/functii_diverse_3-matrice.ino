int tempArray [6]={12, 13, 22, 23, 32, 33 };
//                 0   1   2   3   4   5  - atentie indexul incepe de la 0

void setup() {
  Serial.begin(9600);
  Serial.println(tempArray[2]);  

//  daca dorim sa schimbam valoarea elementului 2 apelam metoda
  tempArray[1] = 25;
  Serial.println(tempArray[1]);

// pentru a afisa toate elementele din matrice o sa folosim "for"
  for(int i=0; i<6; i++){
    Serial.println(tempArray[i]);
  }
}

void loop() {
  

}
